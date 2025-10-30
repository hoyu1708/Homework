#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

public:
    Polynomial() {
        capacity = 10;
        terms = 0;
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    void newTerm(float c, int e) {
        if (c == 0) return;
        if (terms >= capacity) {
            capacity *= 2;
            Term* tmp = new Term[capacity];
            memcpy(tmp, termArray, sizeof(Term) * terms);
            delete[] termArray;
            termArray = tmp;
        }
        termArray[terms].coef = c;
        termArray[terms].exp = e;
        terms++;
    }

    Polynomial Add(const Polynomial& b) const {
        Polynomial result;
        int i = 0, j = 0;
        while (i < terms && j < b.terms) {
            if (termArray[i].exp == b.termArray[j].exp) {
                float sum = termArray[i].coef + b.termArray[j].coef;
                if (sum != 0) result.newTerm(sum, termArray[i].exp);
                i++; j++;
            } else if (termArray[i].exp > b.termArray[j].exp) {
                result.newTerm(termArray[i].coef, termArray[i].exp);
                i++;
            } else {
                result.newTerm(b.termArray[j].coef, b.termArray[j].exp);
                j++;
            }
        }
        while (i < terms) result.newTerm(termArray[i].coef, termArray[i++].exp);
        while (j < b.terms) result.newTerm(b.termArray[j].coef, b.termArray[j++].exp);
        return result;
    }

    Polynomial Mult(const Polynomial& b) const {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < b.terms; j++) {
                float newC = termArray[i].coef * b.termArray[j].coef;
                int newE = termArray[i].exp + b.termArray[j].exp;

                bool merged = false;
                for (int k = 0; k < result.terms; k++) {
                    if (result.termArray[k].exp == newE) {
                        result.termArray[k].coef += newC;
                        merged = true;
                        break;
                    }
                }
                if (!merged) result.newTerm(newC, newE);
            }
        }

        sort(result.termArray, result.termArray + result.terms,
            [](const Term& a, const Term& b) { return a.exp > b.exp; });
        return result;
    }

    float Eval(float x) const {
        float sum = 0;
        for (int i = 0; i < terms; i++) {
            sum += termArray[i].coef * pow(x, termArray[i].exp);
        }
        return sum;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        for (int i = 0; i < p.terms; i++) {
            if (i > 0 && p.termArray[i].coef > 0)
                os << "+";
            os << p.termArray[i].coef;
            if (p.termArray[i].exp != 0)
                os << "x^" << p.termArray[i].exp;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Polynomial& p) {
        int n;
        is >> n;
        for (int i = 0; i < n; i++) {
            float c; int e;
            is >> c >> e;
            p.newTerm(c, e);
        }
        return is;
    }
};

int main() {
    Polynomial A, B;
    cout << "輸入 A 的項數、係數、指數: ";
    cin >> A;
    cout << "輸入 B 的項數、係數、指數: ";
    cin >> B;

    cout << "A(x) = " << A << endl;
    cout << "B(x) = " << B << endl;

    Polynomial C = A.Add(B);
    cout << "A + B = " << C << endl;

    Polynomial D = A.Mult(B);
    cout << "A * B = " << D << endl;

    float x = 2;
    cout << "A(2) = " << A.Eval(x) << endl;
}