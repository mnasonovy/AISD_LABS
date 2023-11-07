#include <gtest/gtest.h>
#include "vector.cc"
#include <complex>


TEST(VectorTest, Constructors) {
    Vector<int> a(4, 6);
    EXPECT_EQ(a.GetDimension(), 4);
    for (size_t i = 0; i < a.GetDimension(); ++i) {
        EXPECT_EQ(a[i], 6);
    }

    Vector<int> b(a);
    EXPECT_EQ(b.GetDimension(), 4);
    for (size_t i = 0; i < b.GetDimension(); ++i) {
        EXPECT_EQ(b[i], a[i]);
    }
}

TEST(VectorTest, AssignmentOperator) {
    Vector<int> a(3, 2);
    Vector<int> b(2, 1);
    b = a;
    EXPECT_EQ(b.GetDimension(), a.GetDimension());
    for (size_t i = 0; i < b.GetDimension(); ++i) {
        EXPECT_EQ(b[i], a[i]);
    }
}

TEST(VectorTest, PlusOperator) {
    Vector<int> a(3, 2);
    Vector<int> b(3, 1);
    Vector<int> c = a + b;
    EXPECT_EQ(c.GetDimension(), 3);
    for (size_t i = 0; i < c.GetDimension(); ++i) {
        EXPECT_EQ(c[i], 3);
    }
}

TEST(VectorTest, MinusOperator) {
    Vector<int> a(3, 2);
    Vector<int> b(3, 1);
    Vector<int> c = a - b;
    EXPECT_EQ(c.GetDimension(), 3);
    for (size_t i = 0; i < c.GetDimension(); ++i) {
        EXPECT_EQ(c[i], 1);
    }
}

TEST(VectorTest, MultiplicationOperator) {
    Vector<int> a(3, 2);
    Vector<int> b = a * 3;
    EXPECT_EQ(b.GetDimension(), 3);
    for (size_t i = 0; i < b.GetDimension(); ++i) {
        EXPECT_EQ(b[i], 6);
    }

    Vector<int> c(3, 3);
    int dot = a * c;
    EXPECT_EQ(dot, 18);
}

TEST(VectorTest, ComplexVectorScalarProduct) {
    Vector<complex<double>> vector1(3);
    vector1[0] = complex<double>(1.0, 2.0);
    vector1[1] = complex<double>(3.0, 4.0);
    vector1[2] = complex<double>(5.0, 6.0);

    Vector<complex<double>> vector2(3);
    vector2[0] = complex<double>(7.0, 8.0);
    vector2[1] = complex<double>(9.0, 10.0);
    vector2[2] = complex<double>(11.0, 12.0);

    // ќжидаемый результат: (1+2i) * (7+8i) + (3+4i) * (9+10i) + (5+6i) * (11+12i)
    complex<double> expected_result = complex<double>(-39.0, 214.0);
    complex<double> result = vector1 * vector2;
    EXPECT_EQ(result, expected_result);
}

TEST(VectorTest, DivisionOperator) {
    Vector<int> a(3, 6);
    Vector<int> b = a / 3;
    EXPECT_EQ(b.GetDimension(), 3);
    for (size_t i = 0; i < b.GetDimension(); ++i) {
        EXPECT_EQ(b[i], 2);
    }
}

TEST(CalculateAngleTest, NonZeroVectors) {
    Vector<double> vec1(4, 0);
    Vector<double> vec2(4, 0);
    vec1[0] = 17;
    vec1[1] = 35;
    vec1[2] = -13;
    vec1[3] = 7;

    vec2[0] = 1;
    vec2[1] = 14;
    vec2[2] = -5;
    vec2[3] = 9;

    double result = CalculateAngle(vec1, vec2);
    EXPECT_NEAR(28.7706, result, 1e-4);
}

TEST(CalculateAngleTest, ZeroVector) {
    Vector<double> vec1(4,0);
    Vector<double> vec2(4,7);

    ASSERT_THROW(CalculateAngle(vec1, vec2), std::invalid_argument);
}

TEST(VectorComparison, EqualVectors) {
    Vector <std::complex<double>> vector1(3, std::complex<double>(1.0, 2.0));
    Vector <std::complex<double>> vector2(3, std::complex<double>(1.0, 2.0));

    EXPECT_TRUE(vector1 == vector2);
}

TEST(VectorComparison, UnequalVectors) {
    Vector < std::complex<double>> vector1(3, std::complex<double>(1.0, 2.0));
    Vector < std::complex<double>> vector2(3, std::complex<double>(3.0, 4.0));

    EXPECT_FALSE(vector1 == vector2);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
