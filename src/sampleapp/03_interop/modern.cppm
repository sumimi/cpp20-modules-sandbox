/**
 * @file modern.cppm
 * @brief サンプル3: ModuleとヘッダファイルのInteroperability
 *
 * C++20 Moduleから従来のヘッダファイルを使用する方法を示します。
 * Global Module Fragmentを使用します。
 */

// Global Module Fragment: Module宣言の前に#includeを配置
// この領域でincludeされたヘッダは、Moduleの外側として扱われる
module;

// 従来のヘッダファイルをインクルード
#include <string>

#include "legacy.h"

// Module宣言
export module modern;

/**
 * @brief モダンなModule機能と従来のヘッダを組み合わせる
 */
export namespace modern {

/**
 * @brief Moduleから従来のヘッダファイルの機能を使用
 * @return 組み合わせたメッセージ
 */
std::string use_legacy_from_module() {
    // legacy.h で定義された関数を使用
    std::string legacy_msg = legacy::get_legacy_message();
    return "Modern Module says: " + legacy_msg;
}

/**
 * @brief レガシークラスをラップした新しいクラス
 */
class ModernWrapper {
   public:
    ModernWrapper(const std::string& data) : legacy_obj_(data) {}

    std::string process() const {
        // レガシークラスを内部で使用
        return "ModernWrapper -> " + legacy_obj_.get_data();
    }

   private:
    legacy::LegacyClass legacy_obj_;
};

/**
 * @brief Module情報
 */
const char* get_info() {
    return "Modern Module with Legacy Interoperability";
}

}  // namespace modern
