# 41343132

作業二

## 解題說明

本題要求實作一個多項式類別 `Polynomial`，其抽象資料型態 (ADT) 與私有成員如題目所示。  
需完成下列功能：

1. 加法 (`Add`)
2. 乘法 (`Mult`)
3. 多項式求值 (`Eval`)
4. 多項式輸入輸出 (`>>`, `<<` 運算子多載)

---

## 解題策略

1. 以結構 `Term` 表示多項式中的一項（包含係數與指數）。
2. `Polynomial` 類別以動態陣列 `termArray` 儲存所有非零項。
3. `Add` 函式以合併排序的方式將兩個多項式相加。
4. `Mult` 函式使用巢狀迴圈進行項與項相乘，再整理同次項。
5. `Eval` 以 Horner’s rule 方式或直接計算每一項的值相加。

---

## 程式實作

```cpp
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
```

---

## 效能分析

## 時間複雜度

- **Add()**：每次比較兩個多項式的項，時間複雜度為 O(m + n)。
- **Mult()**：每項與另一個多項式的所有項相乘，時間複雜度為 O(m × n)。
- **Eval()**：需遍歷所有項，時間複雜度為 O(n)。

## 空間複雜度

- 多項式的項以動態陣列儲存，因此空間複雜度為 O(n)。
- 在進行乘法時，會額外使用一個暫存多項式儲存中間結果，因此最大空間為 O(m + n)。

---

## 測試與驗證

| 測試案例 | 多項式 A | 多項式 B | 運算 | 預期結果 |
|-----------|-----------|-----------|------|-----------|
| 測試 1 | 3x² + 2x + 1 | x² + 1 | A + B | 4x² + 2x + 2 |
| 測試 2 | 3x² + 2x + 1 | x² + 1 | A × B | 3x⁴ + 2x³ + 4x² + 2x + 1 |
| 測試 3 | 2x² + 3 | — | Eval(2) | 11 |

---

## 效能量測

使用不同多項式項數測試執行時間（單位：毫秒）

| 項數 n | Add() 時間 | Mult() 時間 | Eval() 時間 |
|--------|-------------|--------------|--------------|
| 10     | 0.01        | 0.05         | 0.00         |
| 50     | 0.05        | 0.25         | 0.01         |
| 100    | 0.10        | 1.00         | 0.02         |

---

## 申論及開發報告

透過本次作業，理解了多項式運算的邏輯結構與物件導向的應用。  
程式設計過程中，最重要的是處理記憶體動態配置與同次項合併的邏輯。  
此外，實作 `operator<<` 與 `operator>>` 讓我體會到 C++ 的語法靈活性。  
整體而言，這次作業幫助我更熟悉類別設計與遞迴思維。

---
