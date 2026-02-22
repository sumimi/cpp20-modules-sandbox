/**
 * @file string_utils.cppm
 * @brief サンプル4: 実践的なライブラリ設計
 *
 * Module InterfaceとImplementationを分離した設計を示します。
 * このファイルはModule Interface（公開API）を定義します。
 */

// Global Module Fragment
module;

#include <string>
#include <vector>

export module string_utils;

/**
 * @brief 文字列操作ユーティリティ
 */
export namespace utils {

/**
 * @brief 文字列を大文字に変換
 * @param str 入力文字列
 * @return 大文字に変換された文字列
 */
std::string to_upper(const std::string& str);

/**
 * @brief 文字列を小文字に変換
 * @param str 入力文字列
 * @return 小文字に変換された文字列
 */
std::string to_lower(const std::string& str);

/**
 * @brief 文字列をトリム（前後の空白を削除）
 * @param str 入力文字列
 * @return トリムされた文字列
 */
std::string trim(const std::string& str);

/**
 * @brief 文字列を指定の区切り文字で分割
 * @param str 入力文字列
 * @param delimiter 区切り文字
 * @return 分割された文字列のベクター
 */
std::vector<std::string> split(const std::string& str, char delimiter);

/**
 * @brief 文字列ベクターを指定の区切り文字で結合
 * @param parts 文字列ベクター
 * @param delimiter 区切り文字列
 * @return 結合された文字列
 */
std::string join(const std::vector<std::string>& parts, const std::string& delimiter);

/**
 * @brief 文字列が指定の接頭辞で始まるかチェック
 * @param str 入力文字列
 * @param prefix 接頭辞
 * @return 接頭辞で始まる場合true
 */
bool starts_with(const std::string& str, const std::string& prefix);

/**
 * @brief 文字列が指定の接尾辞で終わるかチェック
 * @param str 入力文字列
 * @param suffix 接尾辞
 * @return 接尾辞で終わる場合true
 */
bool ends_with(const std::string& str, const std::string& suffix);

}  // namespace utils
