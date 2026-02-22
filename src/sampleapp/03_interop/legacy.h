/**
 * @file legacy.h
 * @brief サンプル3: 従来のヘッダファイル
 *
 * C++20 Modulesと従来のヘッダファイルを共存させる例です。
 * これは既存コードとの互換性を保つために重要です。
 */

#ifndef LEGACY_H
#define LEGACY_H

#include <string>

namespace legacy {

/**
 * @brief 従来のヘッダファイルで定義された関数
 * @return レガシーメッセージ
 */
inline std::string get_legacy_message() {
    return "This is from legacy header file";
}

/**
 * @brief レガシーシステムのクラス
 */
class LegacyClass {
   public:
    LegacyClass(const std::string& data) : data_(data) {}

    std::string get_data() const { return "Legacy: " + data_; }

   private:
    std::string data_;
};

}  // namespace legacy

#endif  // LEGACY_H
