#include <random>
#include <chrono>
#include "include/sorting_functions.h" 

std::vector<int> GenerateRandomArray(int size, int seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 1000);
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(rng);
    }
    return arr;
}

Stats RandomStats(int size) {
    Stats average_stats;
    size_t count = 100;
    int seed = 42;
    for (size_t i = 0; i < count; ++i) {
        std::vector<int> vec = GenerateRandomArray(size, seed);
        average_stats += QuickSortWrapper(vec);
        seed++;
    }
    average_stats.comparison_count /= count;
    average_stats.copy_count /= count;

    return average_stats;
}

std::vector<int> SortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

std::vector<int> ReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}
