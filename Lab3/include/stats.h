#include <iostream>
#include <vector>

struct Stats {
    size_t comparison_count;
    size_t copy_count;

    Stats() : comparison_count(0), copy_count(0) {}

    Stats(const Stats& other)
        : comparison_count(other.comparison_count), copy_count(other.copy_count) {}

    Stats& operator=(const Stats& other) {
        if (this != &other) {
            comparison_count = other.comparison_count;
            copy_count = other.copy_count;
        }
        return *this;
    }

    Stats& operator+=(const Stats& other) {
        comparison_count += other.comparison_count;
        copy_count += other.copy_count;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& stream, const Stats& stats) {
    stream << "Comparison count: " << stats.comparison_count << std::endl;
    stream << "Copy count: " << stats.copy_count << std::endl;
    stream << std::endl;
    return stream;
}
