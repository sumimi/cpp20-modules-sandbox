/**
 * @file test_string_utils.cpp
 * @brief サンプル4 (string_utils Module) のユニットテスト
 *
 * utils::to_upper / to_lower / trim / split / join /
 * starts_with / ends_with の全関数を検証します。
 */

#include <gtest/gtest.h>

#include <string>
#include <vector>

import string_utils;

// ============================================================
// to_upper()
// ============================================================

TEST(StringUtilsTest, ToUpper_AllLower) {
    EXPECT_EQ(utils::to_upper("hello"), "HELLO");
}

TEST(StringUtilsTest, ToUpper_Mixed) {
    EXPECT_EQ(utils::to_upper("Hello World"), "HELLO WORLD");
}

TEST(StringUtilsTest, ToUpper_AlreadyUpper) {
    EXPECT_EQ(utils::to_upper("HELLO"), "HELLO");
}

TEST(StringUtilsTest, ToUpper_Empty) {
    EXPECT_EQ(utils::to_upper(""), "");
}

TEST(StringUtilsTest, ToUpper_WithNumbers) {
    EXPECT_EQ(utils::to_upper("abc123"), "ABC123");
}

// ============================================================
// to_lower()
// ============================================================

TEST(StringUtilsTest, ToLower_AllUpper) {
    EXPECT_EQ(utils::to_lower("HELLO"), "hello");
}

TEST(StringUtilsTest, ToLower_Mixed) {
    EXPECT_EQ(utils::to_lower("Hello World"), "hello world");
}

TEST(StringUtilsTest, ToLower_AlreadyLower) {
    EXPECT_EQ(utils::to_lower("hello"), "hello");
}

TEST(StringUtilsTest, ToLower_Empty) {
    EXPECT_EQ(utils::to_lower(""), "");
}

// ============================================================
// trim()
// ============================================================

TEST(StringUtilsTest, Trim_Leading) {
    EXPECT_EQ(utils::trim("   hello"), "hello");
}

TEST(StringUtilsTest, Trim_Trailing) {
    EXPECT_EQ(utils::trim("hello   "), "hello");
}

TEST(StringUtilsTest, Trim_Both) {
    EXPECT_EQ(utils::trim("  hello world  "), "hello world");
}

TEST(StringUtilsTest, Trim_NoSpaces) {
    EXPECT_EQ(utils::trim("hello"), "hello");
}

TEST(StringUtilsTest, Trim_Empty) {
    EXPECT_EQ(utils::trim(""), "");
}

TEST(StringUtilsTest, Trim_OnlySpaces) {
    EXPECT_EQ(utils::trim("   "), "");
}

// ============================================================
// split()
// ============================================================

TEST(StringUtilsTest, Split_ThreeParts) {
    auto parts = utils::split("a,b,c", ',');
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(StringUtilsTest, Split_SingleToken) {
    auto parts = utils::split("hello", ',');
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "hello");
}

TEST(StringUtilsTest, Split_FourParts) {
    auto parts = utils::split("apple,banana,cherry,date", ',');
    EXPECT_EQ(parts.size(), 4u);
}

TEST(StringUtilsTest, Split_DifferentDelimiter) {
    auto parts = utils::split("one|two|three", '|');
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[1], "two");
}

// ============================================================
// join()
// ============================================================

TEST(StringUtilsTest, Join_ThreeParts) {
    std::vector<std::string> v = {"a", "b", "c"};
    EXPECT_EQ(utils::join(v, ","), "a,b,c");
}

TEST(StringUtilsTest, Join_MultiCharDelimiter) {
    std::vector<std::string> v = {"apple", "banana", "cherry"};
    EXPECT_EQ(utils::join(v, " | "), "apple | banana | cherry");
}

TEST(StringUtilsTest, Join_SingleElement) {
    std::vector<std::string> v = {"only"};
    EXPECT_EQ(utils::join(v, ","), "only");
}

TEST(StringUtilsTest, Join_Empty) {
    std::vector<std::string> v;
    EXPECT_EQ(utils::join(v, ","), "");
}

TEST(StringUtilsTest, Join_EmptyDelimiter) {
    std::vector<std::string> v = {"a", "b", "c"};
    EXPECT_EQ(utils::join(v, ""), "abc");
}

// ============================================================
// starts_with()
// ============================================================

TEST(StringUtilsTest, StartsWith_True) {
    EXPECT_TRUE(utils::starts_with("document.pdf", "doc"));
}

TEST(StringUtilsTest, StartsWith_False) {
    EXPECT_FALSE(utils::starts_with("readme.md", "doc"));
}

TEST(StringUtilsTest, StartsWith_FullMatch) {
    EXPECT_TRUE(utils::starts_with("hello", "hello"));
}

TEST(StringUtilsTest, StartsWith_EmptyPrefix) {
    EXPECT_TRUE(utils::starts_with("anything", ""));
}

TEST(StringUtilsTest, StartsWith_PrefixLongerThanStr) {
    EXPECT_FALSE(utils::starts_with("hi", "hello"));
}

// ============================================================
// ends_with()
// ============================================================

TEST(StringUtilsTest, EndsWith_True) {
    EXPECT_TRUE(utils::ends_with("document.pdf", ".pdf"));
}

TEST(StringUtilsTest, EndsWith_False) {
    EXPECT_FALSE(utils::ends_with("document.pdf", ".txt"));
}

TEST(StringUtilsTest, EndsWith_FullMatch) {
    EXPECT_TRUE(utils::ends_with("hello", "hello"));
}

TEST(StringUtilsTest, EndsWith_EmptySuffix) {
    EXPECT_TRUE(utils::ends_with("anything", ""));
}

TEST(StringUtilsTest, EndsWith_SuffixLongerThanStr) {
    EXPECT_FALSE(utils::ends_with("hi", "hello"));
}
