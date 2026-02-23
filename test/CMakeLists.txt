#
# @file test/CMakeLists.txt
# @brief プロジェクト全体のユニットテスト・統合テスト構成を定義する CMake ファイルです。
#
# このファイルでは、GoogleTest ベースのテスト構築、モジュールごとの追加、
# sampleappをリンクした一貫したテストビルドを提供します。
#

# GoogleTest の検出（gmock含む場合も同様）
set(CMAKE_PREFIX_PATH "/opt/gtest/gtest-1.14")
find_package(GTest REQUIRED)

# カバレッジ用スクリプトの読み込み（GCC + ENABLE_COVERAGE 用）
include(${CMAKE_SOURCE_DIR}/tools/coverage.cmake)

# GoogleTest 統合モジュール
include(GoogleTest)

# =============================================================================
# ユニットテストターゲットの定義
# 各モジュールの単体テストコード（unit/ 配下）を対象とする
# =============================================================================
file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS unit/*.cpp)

# ユニットテスト用の実行ファイルを作成
add_executable(unit_tests ${UNIT_TEST_SOURCES})

# C++20 を有効化（C++20 Modules の import に必要）
target_compile_features(unit_tests PRIVATE cxx_std_20)

# -fmodules-ts: Module の import 構文を有効化
target_compile_options(unit_tests PRIVATE -fmodules-ts)

# GCC は CWD 配下の gcm.cache/ で .gcm ファイルを探索する。
# unit_tests の CWD は build/test/ なので、
# build/test/gcm.cache -> build/src/sampleapp/gcm.cache のシンボリックリンクを作成する
add_custom_target(create_gcm_symlink_for_tests
    COMMAND ln -sfn
        ${CMAKE_BINARY_DIR}/src/sampleapp/gcm.cache
        ${CMAKE_CURRENT_BINARY_DIR}/gcm.cache
    DEPENDS sampleapp
    COMMENT "Linking gcm.cache for module imports"
    VERBATIM
)
add_dependencies(unit_tests create_gcm_symlink_for_tests)

# ヘッダファイルの探索パスを指定
# 各モジュールの include を使用するためトップレベルを追加
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(unit_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    sampleapp
)

enable_coverage_if_gcc(unit_tests)
gtest_discover_tests(unit_tests DISCOVERY_TIMEOUT 30 TEST_PREFIX "UnitTests.")

# =============================================================================
# 各モジュールの CMakeLists を明示的に登録
# =============================================================================
add_subdirectory(unit/sampleapp)
