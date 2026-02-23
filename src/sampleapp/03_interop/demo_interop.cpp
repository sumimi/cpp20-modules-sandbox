/**
 * @file demo_interop.cpp
 * @brief サンプル3のデモンストレーション
 *
 * ModuleとヘッダファイルのInteroperability（相互運用性）を示します。
 */

// 従来のヘッダファイルも直接includeできる
#include <iostream>

#include "legacy.h"

// Moduleをインポート
import modern;

/**
 * @brief デモ実行関数
 */
void demo_03_interop() {
    std::cout << "\n=== Sample 3: Module and Header Interoperability ===\n" << std::endl;

    std::cout << modern::get_info() << "\n" << std::endl;

    // 1. Moduleから従来のヘッダファイルを使用
    std::cout << "【Moduleから従来のヘッダを使用】" << std::endl;
    std::cout << "  " << modern::use_legacy_from_module() << std::endl;

    // 2. ModernWrapperでレガシークラスをラップ
    std::cout << "\n【レガシークラスのラップ】" << std::endl;
    modern::ModernWrapper wrapper("Test Data");
    std::cout << "  " << wrapper.process() << std::endl;

    // 3. 従来のヘッダファイルを直接使用
    std::cout << "\n【従来のヘッダを直接使用】" << std::endl;
    std::cout << "  " << legacy::get_legacy_message() << std::endl;
    legacy::LegacyClass legacy_obj("Direct Access");
    std::cout << "  " << legacy_obj.get_data() << std::endl;

    std::cout << "\n✅ Interoperabilityを学びました：" << std::endl;
    std::cout << "   - Global Module Fragment (module;) で既存ヘッダをinclude" << std::endl;
    std::cout << "   - Moduleと従来のコードを混在させられる" << std::endl;
    std::cout << "   - 段階的な移行が可能" << std::endl;
    std::cout << "   - 既存のライブラリをそのまま利用できる" << std::endl;
}
