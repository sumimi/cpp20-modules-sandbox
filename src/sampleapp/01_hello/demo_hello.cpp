/**
 * @file demo_hello.cpp
 * @brief サンプル1のデモンストレーション
 *
 * hello Moduleをimportして使用する例を示します。
 */

// Moduleをインポート（#includeの代わり）
import hello;

#include <iostream>

/**
 * @brief デモ実行関数
 */
void demo_01_hello() {
    std::cout << "\n=== Sample 1: Basic Module (Hello World) ===\n" << std::endl;

    // hello Moduleからエクスポートされた関数を使用
    std::cout << sample::say_hello("C++ Developer") << std::endl;
    std::cout << sample::get_module_info() << std::endl;

    // sample::internal_helper() はエクスポートされていないため、
    // ここでは使用できません（コンパイルエラーになります）
    // std::cout << sample::internal_helper() << std::endl; // エラー！

    std::cout << "\n✅ Moduleの基本的な使い方を学びました：" << std::endl;
    std::cout << "   - export module でModule宣言" << std::endl;
    std::cout << "   - export で公開する関数を指定" << std::endl;
    std::cout << "   - exportしない関数は内部実装のみで使用" << std::endl;
    std::cout << "   - import でModuleを読み込み" << std::endl;
}
