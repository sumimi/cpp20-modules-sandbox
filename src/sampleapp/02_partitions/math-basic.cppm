/**
 * @file math-basic.cppm
 * @brief サンプル2: Module Partition - 基本的な数学関数
 *
 * Module Partitionの定義方法を示します。
 * :basic というPartition名で、基本的な算術関数を提供します。
 */

// Partition宣言: module math:basic
// math Moduleの一部（Partition）であることを示す
export module math:basic;

/**
 * @brief 基本的な算術関数を提供する名前空間
 */
export namespace math::basic {

/**
 * @brief 2つの整数を加算
 * @param a 第1オペランド
 * @param b 第2オペランド
 * @return a + b
 */
int add(int a, int b) {
    return a + b;
}

/**
 * @brief 2つの整数を減算
 * @param a 第1オペランド
 * @param b 第2オペランド
 * @return a - b
 */
int subtract(int a, int b) {
    return a - b;
}

/**
 * @brief 2つの整数を乗算
 * @param a 第1オペランド
 * @param b 第2オペランド
 * @return a * b
 */
int multiply(int a, int b) {
    return a * b;
}

/**
 * @brief 2つの整数を除算（ゼロ除算チェックなし）
 * @param a 第1オペランド
 * @param b 第2オペランド
 * @return a / b
 */
int divide(int a, int b) {
    return a / b;
}

}  // namespace math::basic
