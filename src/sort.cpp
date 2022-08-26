#include "sort.h"

namespace my_sort {

void insertSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int select = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > select) {
            arr[j] = arr[j - 1];
            j--;
        }
        
        arr[j] = select;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivot) high--;
        arr[low] = arr[high];

        while (low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    }

    arr[low] = pivot;
    return low;
}

void _quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int idx = partition(arr, low, high);
        _quickSort(arr, low, idx - 1);
        _quickSort(arr, idx + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    return _quickSort(arr, 0, arr.size() - 1);
}

}   // namespace sort