/**
 * @file test_math.cpp
 * @brief サンプル2 (math Module / Partitions) のユニットテスト
 *
 * math:basic Partition と math:advanced Partition の全関数を検証します。
 */

#include <gtest/gtest.h>

import math;

// ============================================================
// math:basic Partition
// ============================================================

TEST(MathBasicTest, Add_Positive) {
    EXPECT_EQ(math::basic::add(3, 4), 7);
}

TEST(MathBasicTest, Add_Zero) {
    EXPECT_EQ(math::basic::add(0, 0), 0);
}

TEST(MathBasicTest, Add_Negative) {
    EXPECT_EQ(math::basic::add(-3, -4), -7);
}

TEST(MathBasicTest, Add_Mixed) {
    EXPECT_EQ(math::basic::add(-3, 4), 1);
}

TEST(MathBasicTest, Subtract_Basic) {
    EXPECT_EQ(math::basic::subtract(10, 5), 5);
}

TEST(MathBasicTest, Subtract_NegativeResult) {
    EXPECT_EQ(math::basic::subtract(5, 10), -5);
}

TEST(MathBasicTest, Subtract_Zero) {
    EXPECT_EQ(math::basic::subtract(7, 7), 0);
}

TEST(MathBasicTest, Multiply_Basic) {
    EXPECT_EQ(math::basic::multiply(3, 4), 12);
}

TEST(MathBasicTest, Multiply_Zero) {
    EXPECT_EQ(math::basic::multiply(5, 0), 0);
}

TEST(MathBasicTest, Multiply_Negative) {
    EXPECT_EQ(math::basic::multiply(-3, 4), -12);
}

TEST(MathBasicTest, Divide_Exact) {
    EXPECT_EQ(math::basic::divide(10, 2), 5);
}

TEST(MathBasicTest, Divide_One) {
    EXPECT_EQ(math::basic::divide(9, 1), 9);
}

// ============================================================
// math:advanced Partition
// ============================================================

TEST(MathAdvancedTest, Power_Integer) {
    EXPECT_DOUBLE_EQ(math::advanced::power(2.0, 8.0), 256.0);
}

TEST(MathAdvancedTest, Power_Zero_Exponent) {
    EXPECT_DOUBLE_EQ(math::advanced::power(5.0, 0.0), 1.0);
}

TEST(MathAdvancedTest, Power_One_Base) {
    EXPECT_DOUBLE_EQ(math::advanced::power(1.0, 100.0), 1.0);
}

TEST(MathAdvancedTest, SquareRoot_PerfectSquare) {
    EXPECT_DOUBLE_EQ(math::advanced::square_root(16.0), 4.0);
}

TEST(MathAdvancedTest, SquareRoot_One) {
    EXPECT_DOUBLE_EQ(math::advanced::square_root(1.0), 1.0);
}

TEST(MathAdvancedTest, SquareRoot_NonPerfect) {
    EXPECT_NEAR(math::advanced::square_root(2.0), 1.41421, 1e-5);
}

TEST(MathAdvancedTest, Factorial_Zero) {
    EXPECT_EQ(math::advanced::factorial(0), 1LL);
}

TEST(MathAdvancedTest, Factorial_One) {
    EXPECT_EQ(math::advanced::factorial(1), 1LL);
}

TEST(MathAdvancedTest, Factorial_Five) {
    EXPECT_EQ(math::advanced::factorial(5), 120LL);
}

TEST(MathAdvancedTest, Factorial_Ten) {
    EXPECT_EQ(math::advanced::factorial(10), 3628800LL);
}

TEST(MathAdvancedTest, CircleArea_Radius5) {
    EXPECT_NEAR(math::advanced::circle_area(5.0), 78.5398, 1e-3);
}

TEST(MathAdvancedTest, CircleArea_ZeroRadius) {
    EXPECT_DOUBLE_EQ(math::advanced::circle_area(0.0), 0.0);
}

TEST(MathAdvancedTest, CircleArea_UnitRadius) {
    EXPECT_NEAR(math::advanced::circle_area(1.0), 3.14159, 1e-5);
}
