#include "../include/stats.h"

void naturalMerge(std::vector<int>& arr, size_t left, size_t middle, size_t right, Stats& statistics) {
    size_t left_size = middle - left + 1;
    size_t right_size = right - middle;

    std::vector<int> left_arr(left_size);
    std::vector<int> right_arr(right_size);

    for (size_t i = 0; i < left_size; ++i) {
        left_arr[i] = arr[left + i];
        ++statistics.copy_count;
    }
    for (size_t j = 0; j < right_size; ++j) {
        right_arr[j] = arr[middle + 1 + j];
        ++statistics.copy_count;
    }

    size_t i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        ++statistics.comparison_count;
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            ++i;
        }
        else {
            arr[k] = right_arr[j];
            ++j;
        }
        ++statistics.copy_count;
        ++k;
    }

    while (i < left_size) {
        arr[k] = left_arr[i];
        ++i;
        ++k;
        ++statistics.copy_count;
    }

    while (j < right_size) {
        arr[k] = right_arr[j];
        ++j;
        ++k;
        ++statistics.copy_count;
    }
}

void naturalMergeSort(std::vector<int>& arr, size_t left, size_t right, Stats& statistics) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;

        naturalMergeSort(arr, left, middle, statistics);
        naturalMergeSort(arr, middle + 1, right, statistics);

        naturalMerge(arr, left, middle, right, statistics);
    }
}

Stats naturalMergeSortWrapper(std::vector<int>& arr) {
    Stats statistics;
    naturalMergeSort(arr, 0, arr.size() - 1, statistics);
    return statistics;
}