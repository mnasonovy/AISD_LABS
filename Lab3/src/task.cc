#include "../include/task_functions.h"

void runExperiment() {
    std::vector<int> sizes = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000};

    for (int size : sizes) {
        std::cout << "Размер массива: " << size << std::endl;


        Stats randomStats = RandomStats(size);
        std::cout << "Случайно заполненный массив:" << randomStats << std::endl;
    }
}


int main() {
    setlocale(LC_ALL, "Russian");

    runExperiment();
    return 0;
}
