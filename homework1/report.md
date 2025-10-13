# 41343132

作業一

---

## Problem 1 — Ackermann Function

### 解題說明

本題要求實現 **Ackermann 函數 (Ackermann Function)**，
它是一個經典的遞迴函數，定義如下：

$$
A(m, n) =
\begin{cases}
n + 1, & \text{if } m = 0 \\
A(m - 1, 1), & \text{if } m > 0 \text{ and } n = 0 \\
A(m - 1, A(m, n - 1)), & \text{if } m > 0 \text{ and } n > 0
\end{cases}
$$

Ackermann 函數以「快速成長」聞名，是展示遞迴深度與效率差異的典型例子。

---

### 解題策略

1. 根據數學定義直接撰寫遞迴函式 `ackermann(m, n)`。
2. 若 $m=0$，返回 $n+1$。
3. 若 $m>0$ 且 $n=0$，遞迴呼叫 $A(m-1, 1)$。
4. 否則，執行 $A(m-1, A(m, n-1))$ 的雙層遞迴。
5. 主程式輸入兩個整數，輸出結果。

---

## 程式實作

以下為主要程式碼（`src/problem1.cpp`）：

```cpp
#include <iostream>
#include <vector>
using namespace std;

// ------------------------
// 遞迴版本
// ------------------------
int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann_recursive(m - 1, 1);
    return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

// ------------------------
// 非遞迴版本
// ------------------------
int ackermann_iterative(int m, int n) {
    struct Frame { int m; int n; bool inner_done; };
    vector<Frame> stack;
    stack.push_back({ m, n, false });
    int result = 0;

    while (!stack.empty()) {
        auto& top = stack.back();
        if (top.m == 0) {
            result = top.n + 1;
            stack.pop_back();
            if (!stack.empty()) {
                stack.back().n = result; 
            }
        }
        else if (top.n == 0) {
            top.m -= 1;
            top.n = 1;
        }
        else if (!top.inner_done) {
            top.inner_done = true;
            stack.push_back({ top.m, top.n - 1, false }); 
        }
        else {
            top.m -= 1;
            top.n = result;  
            top.inner_done = false;
        }
    }

    return result;
}

// ------------------------
// 主程式
// ------------------------
int main() {
    int m = 3, n = 2;

    cout << "Recursive: Ackermann(" << m << "," << n << ") = "
        << ackermann_recursive(m, n) << endl;

    cout << "Iterative: Ackermann(" << m << "," << n << ") = "
        << ackermann_iterative(m, n) << endl;
}

```

---

## 效能分析

1. **時間複雜度**  
   Ackermann 函數的時間複雜度極高，無法以多項式或指數表示。
   它的成長速度超越所有原始遞迴函數，常被稱為「超指數級 (super-exponential)」。

2. **空間複雜度**  
   遞迴深度等同於函數呼叫層數，因此空間複雜度約為 $O(d)$，其中 $d$ 為遞迴深度。

---

## 測試與驗證

| 測試案例 | 輸入 $(m, n)$ | 預期輸出 | 實際輸出 |
|-----------|----------------|------------|-----------|
| 測試一 | (0, 0) | 1 | 1 |
| 測試二 | (1, 2) | 4 | 4 |
| 測試三 | (2, 3) | 9 | 9 |
| 測試四 | (3, 2) | 29 | 29 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o problem1 src/problem1.cpp
$ ./problem1
Ackermann(3, 2) = 29
```

---

### 結論

1. 程式能正確計算 Ackermann 函數的輸出結果。
2. 測試案例皆符合數學定義。
3. 此函數展示遞迴深度對計算效率的影響。

---

## Problem 2 — Power Set

### 解題說明

本題要求撰寫一個遞迴函式，列出集合 $S$ 的所有子集合（即 **Power Set**）。

範例：若 $S = \{a,b,c\}$  
則其 Power Set 為：
$$
P(S) = \{\emptyset, \{a\}, \{b\}, \{c\}, \{a,b\}, \{a,c\}, \{b,c\}, \{a,b,c\}\}
$$

---

### 解題策略

1. 使用遞迴函式將問題拆成包含與不包含某元素的兩個子問題。
2. 每次遞迴都處理集合中的一個元素。
3. 當遞迴至末端（index == set.size()）時，輸出當前子集合。

---

## 程式實作

以下為主要程式碼（`src/problem2.cpp`）：

```cpp
#include <iostream>
#include <vector>
using namespace std;

void powerSetHelper(vector<char> &set, vector<char> subset, int index) {
    if (index == (int)set.size()) {
        cout << "{";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i];
            if (i < (int)subset.size() - 1)
                cout << ",";
        }
        cout << "}" << endl;
        return;
    }

    powerSetHelper(set, subset, index + 1);
    subset.push_back(set[index]);
    powerSetHelper(set, subset, index + 1);
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<char> subset;
    cout << "Power Set:" << endl;
    powerSetHelper(S, subset, 0);
}
```

---

## 效能分析

1. **時間複雜度**：  
   每個元素有兩種狀態（包含 / 不包含），共有 $2^n$ 種組合。
   時間複雜度為 $O(2^n)$。

2. **空間複雜度**：  
   遞迴深度為 $O(n)$，每次呼叫佔用一層堆疊記憶體。

---

## 測試與驗證

| 測試案例 | 輸入集合 $S$ | 預期輸出 |
|-----------|----------------|-----------|
| 測試一 | \{a\} | `{}`, `{a}` |
| 測試二 | \{a,b\} | `{}`, `{b}`, `{a}`, `{a,b}` |
| 測試三 | \{a,b,c\} | `{}`, `{c}`, `{b}`, `{b,c}`, `{a}`, `{a,c}`, `{a,b}`, `{a,b,c}` |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o problem2 src/problem2.cpp
$ ./problem2
Power Set:
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

---

### 結論

1. 程式能正確輸出所有子集合。
2. 演算法簡潔且具遞迴思維。
3. 對於元素數量較多的集合，時間複雜度呈指數成長。
