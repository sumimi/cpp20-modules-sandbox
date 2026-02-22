/**
 * @file main.cpp
 * @brief C++20 Modules サンプルアプリケーションのエントリーポイント
 *
 * このアプリケーションは、C++20 Modulesの段階的な学習サンプルを実行します。
 */

#include <iostream>
#include <string>

// 各デモ関数の宣言
void demo_01_hello();
void demo_02_partitions();
void demo_03_interop();
void demo_04_library();

/**
 * @brief メニューを表示
 */
void show_menu() {
    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  C++20 Modules Learning Samples               ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n実行するサンプルを選択してください：\n" << std::endl;
    std::cout << "  1. 基本的なModule (Hello World)" << std::endl;
    std::cout << "  2. Module Partitions (分割Module)" << std::endl;
    std::cout << "  3. Moduleとヘッダファイルの共存" << std::endl;
    std::cout << "  4. 実践的なライブラリ設計" << std::endl;
    std::cout << "  0. すべて実行" << std::endl;
    std::cout << "  q. 終了" << std::endl;
    std::cout << "\n選択 > ";
}

/**
 * @brief アプリケーションのエントリーポイント
 *
 * @param argc 引数の数
 * @param argv 引数配列
 * @return int 成功時は0、失敗時は1を返す
 */
int main(int argc, char* argv[]) {
    std::cout << "\n🚀 C++20 Modules Sandbox へようこそ！\n" << std::endl;

    // コマンドライン引数でサンプル番号が指定された場合
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "1") {
            demo_01_hello();
        } else if (arg == "2") {
            demo_02_partitions();
        } else if (arg == "3") {
            demo_03_interop();
        } else if (arg == "4") {
            demo_04_library();
        } else if (arg == "0" || arg == "all") {
            demo_01_hello();
            demo_02_partitions();
            demo_03_interop();
            demo_04_library();
        } else {
            std::cerr << "エラー: 無効なサンプル番号です: " << arg << std::endl;
            std::cerr << "使用方法: " << argv[0] << " [0-4]" << std::endl;
            return 1;
        }

        std::cout << "\n✨ サンプル実行が完了しました！\n" << std::endl;
        return 0;
    }

    // インタラクティブモード
    while (true) {
        show_menu();

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) continue;

        if (input == "q" || input == "Q") {
            std::cout << "\nさようなら！ 👋\n" << std::endl;
            break;
        }

        if (input == "1") {
            demo_01_hello();
        } else if (input == "2") {
            demo_02_partitions();
        } else if (input == "3") {
            demo_03_interop();
        } else if (input == "4") {
            demo_04_library();
        } else if (input == "0") {
            demo_01_hello();
            demo_02_partitions();
            demo_03_interop();
            demo_04_library();
        } else {
            std::cout << "\n⚠️  無効な選択です。もう一度選んでください。\n" << std::endl;
        }
    }

    return 0;
}
