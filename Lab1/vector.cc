#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>

template<typename T>
class Vector {

private:
    T* elements_;
    size_t size_;

public:
    const double kEqualityEpsilon = 1e-9;

    explicit Vector(size_t dim, const T& value = T()) {
        if (dim > std::numeric_limits<std::size_t>::max()) {
            throw std::invalid_argument("Dimension size is too large");
        }
        size_ = dim;
        elements_ = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = value;
        }
    }

    Vector(size_t dim, T lower_bound, T upper_bound) {
        if (dim > std::numeric_limits<std::size_t>::max()) {
            throw std::invalid_argument("Dimension size is too large");
        }
        size_ = dim;
        elements_ = new T[size_];


        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral<T>::value) {
            std::uniform_int_distribution<T> dist(lower_bound, upper_bound);
            for (size_t i = 0; i < size_; ++i) {
                elements_[i] = dist(gen);
            }
        }
        else if constexpr (std::is_floating_point<T>::value) {
            std::uniform_real_distribution<T> dist(lower_bound, upper_bound);
            for (size_t i = 0; i < size_; ++i) {
                elements_[i] = dist(gen);
            }
        }
        else {
            throw std::invalid_argument("Type not supported");
        }
    }

    Vector(const Vector& other) : Vector(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = other.elements_[i];
        }
    }

    ~Vector() { delete[] elements_; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements_;
            size_ = other.size_;
            elements_ = new T[size_];
            std::copy_n(other.elements_, size_, elements_);
        }
        return *this;
    }

    size_t GetDimension() const { return size_; }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return elements_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return elements_[index];
    }

    Vector operator+(const Vector& other) const {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] + other.elements_[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] - other.elements_[i];
        }
        return result;
    }

    T operator*(const Vector& other) const {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vectors must have the same dimension");
        }
        T result = T();
        for (size_t i = 0; i < size_; ++i) {
            result += elements_[i] * other.elements_[i];
        }
        return result;
    }

    Vector operator*(const T& scalar) const {
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] * scalar;
        }
        return result;
    }

    Vector operator/(const T& scalar) const {
        if (scalar == T()) {
            throw std::invalid_argument("Cannot divide by zero");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] / scalar;
        }
        return result;
    }

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        return std::equal(elements_, elements_ + size_, other.elements_, [=](const auto& lhs, const auto& rhs) {
            if constexpr (std::is_integral<T>::value) {
                return lhs == rhs;
            }
            else {
                return std::abs(lhs - rhs) < kEqualityEpsilon;
            }
            });
    }

    bool operator!=(const Vector& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "(";
        for (size_t i = 0; i < vector.size_; ++i) {
            os << vector.elements_[i];
            if (i != vector.size_ - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};