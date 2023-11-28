#include "../include/stats.h"



Stats quickSort(std::vector<int>& arr, int low, int high) {
    Stats statistics;
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; ++j) {
            ++statistics.comparison_count;
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
                ++statistics.copy_count;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        ++statistics.copy_count;

        int partition_index = i + 1;

        Stats left_stats = quickSort(arr, low, partition_index - 1);
        Stats right_stats = quickSort(arr, partition_index + 1, high);

        statistics.comparison_count += left_stats.comparison_count + right_stats.comparison_count;
        statistics.copy_count += left_stats.copy_count + right_stats.copy_count;
    }
    return statistics;
}

Stats quickSortWrapper(std::vector<int>& arr) {
    return quickSort(arr, 0, arr.size() - 1);
}
