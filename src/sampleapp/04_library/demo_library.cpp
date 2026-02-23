/**
 * @file demo_library.cpp
 * @brief サンプル4のデモンストレーション
 *
 * 実践的なライブラリ設計の例を示します。
 */

#include <iostream>

import string_utils;

/**
 * @brief デモ実行関数
 */
void demo_04_library() {
    std::cout << "\n=== Sample 4: Practical Library Design ===\n" << std::endl;

    // 1. 大文字・小文字変換
    std::cout << "【大文字・小文字変換】" << std::endl;
    std::string text = "Hello, C++20 Modules!";
    std::cout << "  元の文字列: " << text << std::endl;
    std::cout << "  大文字: " << utils::to_upper(text) << std::endl;
    std::cout << "  小文字: " << utils::to_lower(text) << std::endl;

    // 2. トリム
    std::cout << "\n【トリム（空白除去）】" << std::endl;
    std::string padded = "   スペースを削除   ";
    std::cout << "  元の文字列: '" << padded << "'" << std::endl;
    std::cout << "  トリム後: '" << utils::trim(padded) << "'" << std::endl;

    // 3. 分割と結合
    std::cout << "\n【文字列の分割と結合】" << std::endl;
    std::string csv = "apple,banana,cherry,date";
    std::cout << "  元の文字列: " << csv << std::endl;

    auto parts = utils::split(csv, ',');
    std::cout << "  分割結果: ";
    for (const auto& part : parts) {
        std::cout << "[" << part << "] ";
    }
    std::cout << std::endl;

    std::string joined = utils::join(parts, " | ");
    std::cout << "  結合結果: " << joined << std::endl;

    // 4. 接頭辞・接尾辞チェック
    std::cout << "\n【接頭辞・接尾辞チェック】" << std::endl;
    std::string filename = "document.pdf";
    std::cout << "  ファイル名: " << filename << std::endl;
    std::cout << "  'doc'で始まる？ " << (utils::starts_with(filename, "doc") ? "はい" : "いいえ") << std::endl;
    std::cout << "  '.pdf'で終わる？ " << (utils::ends_with(filename, ".pdf") ? "はい" : "いいえ") << std::endl;
    std::cout << "  '.txt'で終わる？ " << (utils::ends_with(filename, ".txt") ? "はい" : "いいえ") << std::endl;

    std::cout << "\n✅ 実践的なライブラリ設計を学びました：" << std::endl;
    std::cout << "   - .cppmファイルで公開APIを定義" << std::endl;
    std::cout << "   - .cppファイルで実装を分離" << std::endl;
    std::cout << "   - 従来の.h/.cppの分離に近い構造" << std::endl;
    std::cout << "   - コンパイル時間の最適化" << std::endl;
}
