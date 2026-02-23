/**
 * @file test_hello.cpp
 * @brief サンプル1 (hello Module) のユニットテスト
 *
 * sample::say_hello() と sample::get_module_info() を検証します。
 */

#include <gtest/gtest.h>

#include <string>

import hello;

// ============================================================
// say_hello()
// ============================================================

TEST(HelloTest, SayHello_BasicName) {
    EXPECT_EQ(sample::say_hello("World"), "Hello, World from C++20 Modules!");
}

TEST(HelloTest, SayHello_DeveloperName) {
    EXPECT_EQ(sample::say_hello("C++ Developer"), "Hello, C++ Developer from C++20 Modules!");
}

TEST(HelloTest, SayHello_EmptyName) {
    // 空文字列を渡した場合でもクラッシュせず文字列を返す
    const std::string result = sample::say_hello("");
    EXPECT_FALSE(result.empty());
}

TEST(HelloTest, SayHello_JapaneseName) {
    EXPECT_EQ(sample::say_hello("開発者"), "Hello, 開発者 from C++20 Modules!");
}

// ============================================================
// get_module_info()
// ============================================================

TEST(HelloTest, GetModuleInfo_NotEmpty) {
    EXPECT_FALSE(sample::get_module_info().empty());
}

TEST(HelloTest, GetModuleInfo_Content) {
    EXPECT_EQ(sample::get_module_info(), "Module: hello (Basic C++20 Module Example)");
}
