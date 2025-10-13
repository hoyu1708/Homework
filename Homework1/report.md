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
using namespace std;

int ackermann(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann(m - 1, 1);
    else
        return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    int m = 3, n = 2;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << '\n';
}
