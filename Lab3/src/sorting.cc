#include "../include/sorting_functions.h"

void PrintVector(const std::vector<int>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::vector<int> data = { 12, 7, 3, 9, 2, 15, 11 };

    std::cout << "Исходный массив:" << std::endl;
    PrintVector(data);

    Stats selection_stats = SelectionSort(data);
    std::cout << "\nРезультат сортировки выбором:" << std::endl;
    PrintVector(data);
    std::cout << "Статистика сортировки выбором:" << std::endl;
    std::cout << selection_stats;

    std::vector<int> data_quick = { 12, 7, 3, 9, 2, 15, 11 };
    Stats quick_stats = QuickSortWrapper(data_quick);
    std::cout << "\nРезультат быстрой сортировки:" << std::endl;
    PrintVector(data_quick);
    std::cout << "Статистика быстрой сортировки:" << std::endl;
    std::cout << quick_stats;

    std::vector<int> data_merge = { 12, 7, 3, 9, 2, 15, 11 };
    Stats merge_stats = NaturalMergeSortWrapper(data_merge);
    std::cout << "\nРезультат сортировки естественным двухпутевым слиянием:" << std::endl;
    PrintVector(data_merge);
    std::cout << "Статистика сортировки естественным двухпутевым слиянием:" << std::endl;
    std::cout << merge_stats;

    return 0;
}
