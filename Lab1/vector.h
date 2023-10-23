template<typename T>
class Vector {
private:
    T* elements_;
    size_t size_;
public:
    const double kEqualityEpsilon = 1e-9;

    explicit Vector(size_t dim, const T& value = T());
    Vector(size_t dim, T lower_bound, T upper_bound);
    Vector(const Vector& other);
    ~Vector();
    Vector& operator=(const Vector& other);
    size_t GetDimension() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    T operator*(const Vector& other) const;
    Vector operator*(const T& scalar) const;
    Vector operator/(const T& scalar) const;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector);


};