#include "../include/stats.h"


Stats selectionSort(std::vector<int>& arr) {
    Stats statistics;
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; ++j) {
            ++statistics.comparison_count;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
            ++statistics.copy_count;
        }
    }
    return statistics;
}