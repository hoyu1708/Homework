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
