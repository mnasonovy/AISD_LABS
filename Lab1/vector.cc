#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <random>
#include <stdexcept>
#include <complex> 
#include <cmath>

using namespace std;

const double kPi = 3.14159265358979323846;

template <typename T>
class Vector {
public:
    Vector(size_t dim, const T& value = T()) : size_(dim), elements_(new T[dim]) {
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = value;
        }
    }

    Vector(size_t dim, T lower_bound, T upper_bound) : size_(dim), elements_(new T[dim]) {
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (is_integral<T>::value) {
            uniform_int_distribution<T> dist(lower_bound, upper_bound);
            for (size_t i = 0; i < size_; ++i) {
                elements_[i] = dist(gen);
            }
        }
        else if constexpr (is_floating_point<T>::value) {
            uniform_real_distribution<T> dist(lower_bound, upper_bound);
            for (size_t i = 0; i < size_; ++i) {
                elements_[i] = dist(gen);
            }
        }
        else {
            throw invalid_argument("Type not supported");
        }
    }

    Vector(const Vector& other) : size_(other.size_), elements_(new T[other.size_]) {
        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = other.elements_[i];
        }
    }

    ~Vector() { delete[] elements_; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (size_ != other.size_) {
                delete[] elements_;
                size_ = other.size_;
                elements_ = new T[size_];
            }

            for (size_t i = 0; i < size_; ++i) {
                elements_[i] = other.elements_[i];
            }
        }
        return *this;
    }

    size_t GetDimension() const { return size_; }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return elements_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index out of range");
        }
        return elements_[index];
    }

    Vector operator+(const Vector& other) const {
        if (size_ != other.size_) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] + other.elements_[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (size_ != other.size_) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] - other.elements_[i];
        }
        return result;
    }

    T operator*(const Vector& other) const {
        if (size_ != other.size_) {
            throw invalid_argument("Vectors must have the same dimension");
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
            throw invalid_argument("Cannot divide by zero");
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

        for (size_t i = 0; i < size_; ++i) {
            if (elements_[i] != other.elements_[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& os, const Vector& vector) {
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

private:
    T* elements_;
    size_t size_;
};

template <typename T>
double CalculateAngle(const Vector<T>& a, const Vector<T>& b) {
    T dotProduct = a * b;
    T magnitudes = sqrt((a * a) * (b * b));

    if (magnitudes == T()) {
        throw invalid_argument("Cannot calculate the angle with a zero vector");
    }

    double cosine = dotProduct / magnitudes;

    double angleInRadian = acos(cosine);

    double angleInDegree = angleInRadian * (180.0 / kPi);

    return angleInDegree;
}

#endif