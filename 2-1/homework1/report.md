# 41343132

作業一

## 解題說明

本題要求實作多種排序演算法，並分析其在不同輸入大小下的執行時間與效能表現。
需完成以下功能：

1. Insertion Sort
2. Quick Sort（使用 median-of-three 選 pivot）
3. Merge Sort（使用 iterative 方法）
4. Heap Sort
5. Composite Sort（結合多種排序策略）

此外，需針對不同 n 值（500 ~ 5000）進行測試，並比較各排序方法的效能。

---

## 解題策略

1. 使用 `vector<int>` 儲存資料。
2. 每種排序函式皆獨立實作，方便測試與比較。
3. 使用 `chrono` 計算執行時間，並重複多次取平均值。
4. 測試資料採隨機產生（average-case）。
5. Composite Sort：

   * 小資料使用 Insertion Sort
   * 大資料使用 Quick Sort

---

## 程式實作

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// ================= 排序 =================

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort (median-of-three)
int medianOfThree(vector<int>& arr, int l, int r) {
    int m = (l + r) / 2;
    if (arr[l] > arr[m]) swap(arr[l], arr[m]);
    if (arr[l] > arr[r]) swap(arr[l], arr[r]);
    if (arr[m] > arr[r]) swap(arr[m], arr[r]);
    return m;
}

void quickSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = medianOfThree(arr, l, r);
    swap(arr[m], arr[r]);

    int pivot = arr[r];
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);

    quickSort(arr, l, i);
    quickSort(arr, i + 2, r);
}

// Merge Sort (iterative)
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }

    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = 0; k < (int)temp.size(); k++)
        arr[l + k] = temp[k];
}

void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size *= 2) {
        for (int l = 0; l < n - size; l += 2 * size) {
            int m = l + size - 1;
            int r = min(l + 2 * size - 1, n - 1);
            merge(arr, l, m, r);
        }
    }
}

// Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Composite Sort
void compositeSort(vector<int>& arr) {
    if (arr.size() < 1000)
        insertionSort(arr);
    else
        quickSort(arr, 0, arr.size() - 1);
}

// ================= 測試 =================

vector<int> generateRandom(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
    return arr;
}

long long measure(void (*sortFunc)(vector<int>&), vector<int> arr) {
    int repeat = 50;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < repeat; i++) {
        vector<int> tmp = arr;
        sortFunc(tmp);
    }
    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count() / repeat;
}

// Quick wrapper
void quickWrapper(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int main() {
    srand(time(0));

    vector<int> sizes = {500, 1000, 2000, 3000, 4000, 5000};

    for (int i = 0; i < sizes.size(); i++) {
        int n = sizes[i];
        vector<int> data = generateRandom(n);

        cout << "n = " << n << endl;
        cout << "Insertion: " << measure(insertionSort, data) << " us" << endl;
        cout << "Quick: " << measure(quickWrapper, data) << " us" << endl;
        cout << "Merge: " << measure(mergeSortIterative, data) << " us" << endl;
        cout << "Heap: " << measure(heapSort, data) << " us" << endl;
        cout << "Composite: " << measure(compositeSort, data) << " us" << endl;
        cout << "------------------------" << endl;
    }

    return 0;
}
```

---

## 效能分析

## 時間複雜度

* **Insertion Sort**：O(n²)
* **Quick Sort**：平均 O(n log n)，最差 O(n²)
* **Merge Sort**：O(n log n)
* **Heap Sort**：O(n log n)
* **Composite Sort**：依資料大小而定

---

## 空間複雜度

* Insertion Sort：O(1)
* Quick Sort：O(log n)（遞迴堆疊）
* Merge Sort：O(n)
* Heap Sort：O(1)
* Composite Sort：依選用演算法而定

---

## 測試與驗證

使用隨機產生資料進行測試：

| n    | Insertion | Quick | Merge | Heap | Composite |
| ---- | --------- | ----- | ----- | ---- | --------- |
| 500  | (420 us)      | (69 us)  | (277 us)  | (124 us) | (398 us)      |
| 1000 | (1657 us)      | (152 us)  | (628 us)  | (275) | (147 us)      |
| 2000 | (6454 us)      | (345 us)  | (1193 us)  | (636 us) | (350)      |

---

## 效能量測

使用 `chrono` 測量執行時間（microseconds），每個排序函式重複執行 50 次取平均值。

---

## 申論及開發報告

透過本次作業，我學習到不同排序演算法的實作方式與效能差異。
Insertion Sort 雖然簡單，但在資料量大時效率較差；而 Quick Sort、Merge Sort 與 Heap Sort 在大多數情況下表現較佳。

此外，透過實作 Composite Sort，可以根據資料大小選擇最適合的排序方法，提高整體效能。
本次實驗也讓我理解時間複雜度與實際執行時間之間的關係。

---
