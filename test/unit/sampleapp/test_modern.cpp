/**
 * @file test_modern.cpp
 * @brief サンプル3 (modern Module / Interoperability) のユニットテスト
 *
 * modern::use_legacy_from_module()、modern::ModernWrapper、
 * modern::get_info() を検証します。
 */

#include <gtest/gtest.h>

#include <string>

import modern;

// ============================================================
// get_info()
// ============================================================

TEST(ModernTest, GetInfo_NotEmpty) {
    EXPECT_FALSE(std::string(modern::get_info()).empty());
}

TEST(ModernTest, GetInfo_Content) {
    EXPECT_STREQ(modern::get_info(), "Modern Module with Legacy Interoperability");
}

// ============================================================
// use_legacy_from_module()
// ============================================================

TEST(ModernTest, UseLegacy_NotEmpty) {
    EXPECT_FALSE(modern::use_legacy_from_module().empty());
}

TEST(ModernTest, UseLegacy_ContainsLegacyMessage) {
    const std::string result = modern::use_legacy_from_module();
    // legacy::get_legacy_message() の内容が含まれていること
    EXPECT_NE(result.find("legacy header file"), std::string::npos);
}

TEST(ModernTest, UseLegacy_HasModernPrefix) {
    const std::string result = modern::use_legacy_from_module();
    EXPECT_EQ(result.find("Modern Module says:"), 0u);
}

// ============================================================
// ModernWrapper
// ============================================================

TEST(ModernWrapperTest, Process_NotEmpty) {
    modern::ModernWrapper wrapper("TestData");
    EXPECT_FALSE(wrapper.process().empty());
}

TEST(ModernWrapperTest, Process_ContainsInputData) {
    modern::ModernWrapper wrapper("HelloWorld");
    EXPECT_NE(wrapper.process().find("HelloWorld"), std::string::npos);
}

TEST(ModernWrapperTest, Process_ContainsLegacyPrefix) {
    modern::ModernWrapper wrapper("SomeData");
    // LegacyClass::get_data() が "Legacy: " プレフィックスを付ける
    EXPECT_NE(wrapper.process().find("Legacy"), std::string::npos);
}

TEST(ModernWrapperTest, Process_ContainsWrapperPrefix) {
    modern::ModernWrapper wrapper("data");
    EXPECT_NE(wrapper.process().find("ModernWrapper"), std::string::npos);
}
