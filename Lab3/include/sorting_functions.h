#include "../include/stats.h"

Stats SelectionSort(std::vector<int>& arr) {
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

struct Partition {
    int low;
    int high;
};

Stats QuickSort(std::vector<int>& arr, int low, int high) {
    Stats statistics;
    std::vector<Partition> partitions;
    partitions.push_back({ low, high });

    while (!partitions.empty()) {
        low = partitions.back().low;
        high = partitions.back().high;
        partitions.pop_back();

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

            partitions.push_back({ low, partition_index - 1 });
            partitions.push_back({ partition_index + 1, high });
        }
    }

    return statistics;
}

Stats QuickSortWrapper(std::vector<int>& arr) {
    return QuickSort(arr, 0, arr.size() - 1);
}

void NaturalMerge(std::vector<int>& arr, size_t left, size_t middle, size_t right, Stats& statistics) {
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

void NaturalMergeSort(std::vector<int>& arr, size_t left, size_t right, Stats& statistics) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;

        NaturalMergeSort(arr, left, middle, statistics);
        NaturalMergeSort(arr, middle + 1, right, statistics);

        NaturalMerge(arr, left, middle, right, statistics);
    }
}

Stats NaturalMergeSortWrapper(std::vector<int>& arr) {
    Stats statistics;
    NaturalMergeSort(arr, 0, arr.size() - 1, statistics);
    return statistics;
}
