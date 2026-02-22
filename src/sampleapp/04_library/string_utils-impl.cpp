/**
 * @file string_utils-impl.cpp
 * @brief サンプル4: Module Implementation（実装部）
 *
 * このファイルは、string_utils Moduleの実装を提供します。
 * Module InterfaceとImplementationを分離することで、
 * ヘッダファイルとソースファイルの分離に近い構造を実現できます。
 */

// Global Module Fragment
module;

#include <algorithm>
#include <cctype>
#include <sstream>

// Module実装であることを宣言
module string_utils;

namespace utils {

// to_upperの実装
std::string to_upper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
    return result;
}

// to_lowerの実装
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

// trimの実装
std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return std::isspace(c); }).base();

    return (start < end) ? std::string(start, end) : std::string();
}

// splitの実装
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

// joinの実装
std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
    if (parts.empty()) return "";

    std::string result = parts[0];
    for (size_t i = 1; i < parts.size(); ++i) {
        result += delimiter + parts[i];
    }

    return result;
}

// starts_withの実装
bool starts_with(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) return false;
    return str.compare(0, prefix.length(), prefix) == 0;
}

// ends_withの実装
bool ends_with(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

}  // namespace utils
