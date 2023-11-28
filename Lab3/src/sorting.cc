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

    std::cout << "�������� ������:" << std::endl;
    PrintVector(data);

    Stats selection_stats = SelectionSort(data);
    std::cout << "\n��������� ���������� �������:" << std::endl;
    PrintVector(data);
    std::cout << "���������� ���������� �������:" << std::endl;
    std::cout << selection_stats;

    std::vector<int> data_quick = { 12, 7, 3, 9, 2, 15, 11 };
    Stats quick_stats = QuickSortWrapper(data_quick);
    std::cout << "\n��������� ������� ����������:" << std::endl;
    PrintVector(data_quick);
    std::cout << "���������� ������� ����������:" << std::endl;
    std::cout << quick_stats;

    std::vector<int> data_merge = { 12, 7, 3, 9, 2, 15, 11 };
    Stats merge_stats = NaturalMergeSortWrapper(data_merge);
    std::cout << "\n��������� ���������� ������������ ����������� ��������:" << std::endl;
    PrintVector(data_merge);
    std::cout << "���������� ���������� ������������ ����������� ��������:" << std::endl;
    std::cout << merge_stats;

    return 0;
}
