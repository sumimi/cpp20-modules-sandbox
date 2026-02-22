/**
 * @file math-advanced.cppm
 * @brief サンプル2: Module Partition - 高度な数学関数
 *
 * より高度な数学関数を提供するPartitionです。
 * :advanced というPartition名を使用します。
 */

// Global Module Fragment
module;

#include <cmath>

// Partition宣言: module math:advanced
export module math:advanced;

/**
 * @brief 高度な数学関数を提供する名前空間
 */
export namespace math::advanced {

/**
 * @brief 累乗計算
 * @param base 基数
 * @param exponent 指数
 * @return base^exponent
 */
double power(double base, double exponent) {
    return std::pow(base, exponent);
}

/**
 * @brief 平方根計算
 * @param value 値
 * @return √value
 */
double square_root(double value) {
    return std::sqrt(value);
}

/**
 * @brief 階乗計算（再帰）
 * @param n 非負整数
 * @return n!
 */
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

/**
 * @brief 円周率の近似値
 */
constexpr double PI = 3.14159265358979323846;

/**
 * @brief 円の面積を計算
 * @param radius 半径
 * @return πr²
 */
double circle_area(double radius) {
    return PI * radius * radius;
}

}  // namespace math::advanced
