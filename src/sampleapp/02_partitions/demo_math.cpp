/**
 * @file demo_math.cpp
 * @brief サンプル2のデモンストレーション
 *
 * Module Partitionsの使用例を示します。
 */

// math Moduleをインポート（Partitionは自動的に含まれる）
import math;

#include <iomanip>
#include <iostream>

/**
 * @brief デモ実行関数
 */
void demo_02_partitions() {
    std::cout << "\n=== Sample 2: Module Partitions ===\n" << std::endl;

    std::cout << math::get_version() << "\n" << std::endl;

    // 基本的な算術関数の使用
    std::cout << "【基本算術 (math:basic Partition)】" << std::endl;
    std::cout << "  10 + 5 = " << math::basic::add(10, 5) << std::endl;
    std::cout << "  10 - 5 = " << math::basic::subtract(10, 5) << std::endl;
    std::cout << "  10 * 5 = " << math::basic::multiply(10, 5) << std::endl;
    std::cout << "  10 / 5 = " << math::basic::divide(10, 5) << std::endl;

    std::cout << "\n【高度な数学関数 (math:advanced Partition)】" << std::endl;
    std::cout << "  2^8 = " << math::advanced::power(2, 8) << std::endl;
    std::cout << "  √16 = " << math::advanced::square_root(16) << std::endl;
    std::cout << "  5! = " << math::advanced::factorial(5) << std::endl;
    std::cout << "  円の面積 (r=5) = " << std::fixed << std::setprecision(2) << math::advanced::circle_area(5.0)
              << std::endl;

    std::cout << "\n✅ Module Partitionsを学びました：" << std::endl;
    std::cout << "   - module name:partition でPartitionを定義" << std::endl;
    std::cout << "   - 大きなModuleを機能ごとに分割できる" << std::endl;
    std::cout << "   - メインModuleでPartitionをまとめる" << std::endl;
    std::cout << "   - import時はメインModuleのみ指定すればOK" << std::endl;
}
