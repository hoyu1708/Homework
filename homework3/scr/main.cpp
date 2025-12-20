#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Term {
    float c;
    int e;
    bool operator!=(const Term& t) const { return c != t.c || e != t.e; }
};

template <class T> class Chain;
template <class T> class ChainIter;
template <class T> class Avail;
class Poly;

template <class T>
class Node {
    friend class Chain<T>;
    friend class ChainIter<T>;
    friend class Avail<T>;
    friend class Poly;
private:
    T d;
    Node<T>* n;
public:
    Node(T e = {}, Node<T>* next = nullptr) : d(e), n(next) {}
};

template <class T>
class Avail {
public:
    static Node<T>* av;
    static Node<T>* get() {
        if (!av) return new Node<T>();
        Node<T>* t = av;
        av = av->n;
        return t;
    }
    static void ret(Node<T>* p) {
        p->n = av;
        av = p;
    }
    static void retChain(Node<T>* first) {
        if (!first) return;
        Node<T>* last = first;
        while (last->n) last = last->n;
        last->n = av;
        av = first;
    }
};
template <class T> Node<T>* Avail<T>::av = nullptr;

template <class T>
class ChainIter {
    friend class Chain<T>;
    friend class Poly;
private:
    Node<T>* p;
public:
    ChainIter(Node<T>* n = nullptr) : p(n) {}
    T& operator*() const { return p->d; }
    ChainIter& operator++() { p = p->n; return *this; }
    bool operator!=(const ChainIter& r) const { return p != r.p; }
};

template <class T>
class Chain {
    friend class Poly;
private:
    Node<T>* h;
public:
    Chain() {
        h = new Node<T>();
        h->n = h;
    }
    ~Chain() {
        if (h->n != h) {
            Node<T>* first = h->n;
            Node<T>* last = first;
            while (last->n != h) last = last->n;
            last->n = nullptr;
            Avail<T>::retChain(first);
        }
        delete h;
    }
    ChainIter<T> begin() const { return ChainIter<T>(h->n); }
    ChainIter<T> end() const { return ChainIter<T>(h); }
    void ins(T val) {
        Node<T>* p = h;
        while (p->n != h && p->n->d.e > val.e) p = p->n;
        if (p->n != h && p->n->d.e == val.e) {
            p->n->d.c += val.c;
            if (abs(p->n->d.c) < 1e-6) {
                Node<T>* del = p->n;
                p->n = del->n;
                Avail<T>::ret(del);
            }
        } else {
            Node<T>* t = Avail<T>::get();
            t->d = val;
            t->n = p->n;
            p->n = t;
        }
    }
};

class Poly {
    friend istream& operator>>(istream& is, Poly& p);
    friend ostream& operator<<(ostream& os, Poly& p);
private:
    Chain<Term> t;
public:
    Poly() {}
    Poly(const Poly& a) {
        ChainIter<Term> i = a.t.begin();
        while (i != a.t.end()) {
            t.ins(*i);
            ++i;
        }
    }
    Poly& operator=(const Poly& a) {
        if (this == &a) return *this;
        if (t.h->n != t.h) {
             Node<Term>* f = t.h->n;
             Node<Term>* l = f;
             while (l->n != t.h) l = l->n;
             l->n = nullptr;
             Avail<Term>::retChain(f);
             t.h->n = t.h;
        }
        ChainIter<Term> i = a.t.begin();
        while (i != a.t.end()) {
            t.ins(*i);
            ++i;
        }
        return *this;
    }
    ~Poly() {} 

    Poly operator+(const Poly& b) const {
        Poly r;
        ChainIter<Term> i1 = t.begin();
        ChainIter<Term> i2 = b.t.begin();
        while (i1 != t.end()) { r.t.ins(*i1); ++i1; }
        while (i2 != b.t.end()) { r.t.ins(*i2); ++i2; }
        return r;
    }
    Poly operator-(const Poly& b) const {
        Poly r;
        ChainIter<Term> i1 = t.begin();
        ChainIter<Term> i2 = b.t.begin();
        while (i1 != t.end()) { r.t.ins(*i1); ++i1; }
        while (i2 != b.t.end()) {
            Term tmp = *i2; tmp.c = -tmp.c;
            r.t.ins(tmp); 
            ++i2; 
        }
        return r;
    }
    Poly operator*(const Poly& b) const {
        Poly r;
        ChainIter<Term> i1 = t.begin();
        while (i1 != t.end()) {
            ChainIter<Term> i2 = b.t.begin();
            while (i2 != b.t.end()) {
                Term tmp;
                tmp.c = (*i1).c * (*i2).c;
                tmp.e = (*i1).e + (*i2).e;
                r.t.ins(tmp);
                ++i2;
            }
            ++i1;
        }
        return r;
    }
    float Evaluate(float x) const {
        float s = 0;
        ChainIter<Term> i = t.begin();
        while (i != t.end()) {
            s += (*i).c * pow(x, (*i).e);
            ++i;
        }
        return s;
    }
};

istream& operator>>(istream& is, Poly& p) {
    int n, e; float c;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> c >> e;
        Term t; t.c = c; t.e = e;
        p.t.ins(t);
    }
    return is;
}

ostream& operator<<(ostream& os, Poly& p) {
    ChainIter<Term> i = p.t.begin();
    bool f = true;
    while (i != p.t.end()) {
        if (!f && (*i).c > 0) os << "+";
        os << (*i).c << "x^" << (*i).e;
        f = false;
        ++i;
    }
    if (f) os << "0";
    return os;
}

int main() {
    Poly a, b, c, d, e;
    cout << "Input A (n c1 e1...): "; cin >> a;
    cout << "Input B (n c1 e1...): "; cin >> b;
    
    cout << "A: " << a << endl;
    cout << "B: " << b << endl;

    c = a + b; cout << "A+B: " << c << endl;
    d = a - b; cout << "A-B: " << d << endl;
    e = a * b; cout << "A*B: " << e << endl;

    float x = 2.0;
    cout << "Eval A at " << x << ": " << a.Evaluate(x) << endl;
    
    return 0;
}
