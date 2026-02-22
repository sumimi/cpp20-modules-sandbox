/**
 * @file hello.cppm
 * @brief サンプル1: 最も基本的なC++20 Module
 *
 * このファイルは、C++20 Modulesの最小限の例を示します。
 * - export module 宣言でModuleを定義
 * - export で関数を公開
 * - ヘッダファイルのincludeガードは不要
 */

// Global Module Fragment: Module宣言の前に標準ライブラリをinclude
module;

#include <string>

// Module宣言: この行でModuleの名前を定義
export module hello;

// 名前空間全体をexport
export namespace sample {

/**
 * @brief 挨拶メッセージを返す関数
 * @param name 名前
 * @return 挨拶メッセージ
 *
 * 名前空間全体がexportされているため、この関数は外部から使用可能です。
 */
std::string say_hello(const std::string& name) {
    return "Hello, " + name + " from C++20 Modules!";
}

/**
 * @brief Module情報を返す
 * @return Module情報文字列
 */
std::string get_module_info() {
    return "Module: hello (Basic C++20 Module Example)";
}

}  // namespace sample
