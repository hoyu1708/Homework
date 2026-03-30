# Data Structures HW1 Report

## 1. Introduction

本次作業實作五種排序演算法，並分析其在不同輸入大小下的執行時間。

---

## 2. Sorting Algorithms

### 2.1 Insertion Sort

* Time Complexity: O(n²)
* 特點：簡單但效率較低

### 2.2 Quick Sort

* Time Complexity: O(n log n)
* 使用 median-of-three 選 pivot

### 2.3 Merge Sort

* Time Complexity: O(n log n)
* 使用 iterative 方法

### 2.4 Heap Sort

* Time Complexity: O(n log n)
* 使用 binary heap

### 2.5 Composite Sort

* 小資料用 Insertion Sort
* 大資料用 Quick Sort

---

## 3. Experimental Setup

* n = 500 ~ 5000
* 使用 random data (average-case)
* 每個測試重複 50 次取平均

---

## 4. Results

（把你跑出來的結果貼這）

---

## 5. Analysis

* Insertion Sort 隨 n 增加成長很快 → 符合 O(n²)
* Quick / Merge / Heap 表現接近 → O(n log n)
* Composite Sort 在小資料較快

---

## 6. Conclusion

* Quick Sort 整體表現最佳
* Insertion Sort 只適合小資料
* Composite Sort 能提升效能
