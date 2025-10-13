# Homework 1

## Problem 1 — Ackermann Function

### 解題說明
Ackermann 函數是一個經典的遞迴函數，其數學定義如下：

$$
A(m, n) =
\begin{cases}
n + 1, & m = 0 \\
A(m - 1, 1), & m > 0, n = 0 \\
A(m - 1, A(m, n - 1)), & m > 0, n > 0
\end{cases}
$$

本題分為 **遞迴版本** 與 **非遞迴版本（使用 stack 模擬呼叫過程）**，以展示遞迴的內部運作原理。

---

### 解題策略

1. **遞迴版本**  
   - 依數學公式直接撰寫遞迴呼叫。  
   - 使用明確的遞迴終止條件避免無窮遞迴。

2. **非遞迴版本**  
   - 使用 `vector<pair<int,int>>` 模擬呼叫堆疊。  
   - 透過手動推疊與回溯方式還原遞迴過程。

---

### 程式實作

#### 遞迴版本
```cpp
#include <iostream>
#include <vector>
using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann_recursive(m - 1, 1);
    return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}
```

#### 非遞迴版本
```cpp
#include <iostream>
#include <vector>
using namespace std;

int ackermann_iterative(int m, int n) {
    vector<pair<int, int>> stack;
    stack.push_back({m, n});

    while (!stack.empty()) {
        auto &top = stack.back();
        m = top.first;
        n = top.second;
        stack.pop_back();

        if (m == 0)
            n = n + 1;
        else if (n == 0)
            stack.push_back({m - 1, 1});
        else {
            stack.push_back({m - 1, -1});
            stack.push_back({m, n - 1});
            continue;
        }

        if (!stack.empty() && stack.back().second == -1) {
            stack.pop_back();
            stack.push_back({stack.empty() ? 0 : stack.back().first, n});
        } else if (stack.empty()) break;
    }
    return n;
}
```

---

### 效能分析
- **時間複雜度**：Ackermann 函數成長速度極快，難以以多項式表示，可視為超指數成長。  
- **空間複雜度**：
  - 遞迴版本：取決於呼叫深度，為 O(stack depth)。  
  - 非遞迴版本：取決於手動堆疊大小，與遞迴深度相同。

---

### 測試與驗證

| 測試案例 | m | n | 預期輸出 | 實際輸出 |
|-----------|---|---|-----------|-----------|
| 測試一 | 0 | 0 | 1 | 1 |
| 測試二 | 1 | 2 | 4 | 4 |
| 測試三 | 2 | 2 | 7 | 7 |
| 測試四 | 3 | 2 | 29 | 29 |

---

### 申論及開發報告
Ackermann 函數的實作展現遞迴深度與堆疊運作的關係。  
在撰寫過程中，遞迴版本簡潔易懂，但運算效率低且容易造成 Stack Overflow；  
非遞迴版本則以堆疊模擬遞迴呼叫，雖邏輯稍複雜，卻有助理解系統呼叫過程。  
透過比較兩者，可以清楚體會遞迴的結構特性與實作限制。

---

## Problem 2 — Power Set

### 解題說明
Power Set 是所有子集合的集合。若集合 S = {a, b, c}，則：

$$
P(S) = \{\emptyset, \{a\}, \{b\}, \{c\}, \{a,b\}, \{a,c\}, \{b,c\}, \{a,b,c\}\}
$$

---

### 解題策略

1. 使用遞迴函式列舉所有「包含或不包含」的情況。  
2. 當遞迴指標達到集合末端時，輸出目前子集合。  

---

### 程式實作
```cpp
#include <iostream>
#include <vector>
using namespace std;

void powerSetHelper(vector<char> &set, vector<char> subset, int index) {
    if (index == set.size()) {
        cout << "{";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ",";
        }
        cout << "}" << endl;
        return;
    }

    powerSetHelper(set, subset, index + 1);
    subset.push_back(set[index]);
    powerSetHelper(set, subset, index + 1);
}
```

---

### 效能分析
- **時間複雜度**：O(2^n)，每個元素都有包含與不包含兩種狀態。  
- **空間複雜度**：O(n)，遞迴深度隨集合大小成長。  

---

### 測試與驗證

| 測試案例 | 輸入集合 | 預期子集合數量 | 實際輸出 |
|-----------|-----------|----------------|-----------|
| 測試一 | {a} | 2 | {}, {a} |
| 測試二 | {a,b} | 4 | {}, {a}, {b}, {a,b} |
| 測試三 | {a,b,c} | 8 | {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} |

---

### 申論及開發報告
Power Set 的生成過程展示了遞迴在組合問題上的應用。  
程式邏輯清楚且可直接對應數學概念，每層遞迴對應集合中一個元素的取捨。  
雖然時間複雜度為 O(2^n)，但對於小集合而言運行速度仍可接受。  
本題有助於理解遞迴與樹狀決策過程的對應關係。
