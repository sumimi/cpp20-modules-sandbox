#
# @file test/sampleapp/CMakeLists.txt
# @brief sampleapp モジュールのユニットテストを定義する CMake ファイルです。
#
# このファイルでは、GoogleTest を用いた sampleapp モジュールのテストをビルド・実行し、
# カバレッジ取得などの補助処理を含めた構成を定義します。
#

# sampleapp モジュールのテスト対象ソースを収集
file(GLOB SAMPLEAPP_TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

# テスト用実行バイナリを作成
add_executable(sampleapp_tests ${SAMPLEAPP_TEST_SOURCES})

# C++20 を有効化（C++20 Modules の import に必要）
target_compile_features(sampleapp_tests PRIVATE cxx_std_20)

# -fmodules-ts: Module の import 構文を有効化
target_compile_options(sampleapp_tests PRIVATE -fmodules-ts)

# GCC は CWD 配下の gcm.cache/ で .gcm ファイルを探索する。
# sampleapp_tests の CWD は build/test/unit/sampleapp/ なので、
# build/test/unit/sampleapp/gcm.cache -> build/src/sampleapp/gcm.cache のシンボリックリンクを作成する
add_custom_target(create_gcm_symlink_for_sampleapp_tests
    COMMAND ln -sfn
        ${CMAKE_BINARY_DIR}/src/sampleapp/gcm.cache
        ${CMAKE_CURRENT_BINARY_DIR}/gcm.cache
    DEPENDS sampleapp
    COMMENT "Linking gcm.cache for sampleapp module imports"
    VERBATIM
)
add_dependencies(sampleapp_tests create_gcm_symlink_for_sampleapp_tests)

# インクルードパスの設定（本体ヘッダ + テスト用モック）
target_include_directories(sampleapp_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test/sampleapp/mock
)

# ライブラリ探索パスを明示（環境依存で必要なケースに対応）
link_directories(/usr/lib64)

# テスト実行ファイルが依存するライブラリ群をリンク
# GoogleTest + 本体モジュール（logger, pgdb, sampleapp）
target_link_libraries(sampleapp_tests
    PRIVATE
        sampleapp
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

# GoogleTest の検出と統合
include(GoogleTest)
gtest_discover_tests(sampleapp_tests DISCOVERY_TIMEOUT 30)

# カバレッジ取得のためのビルド拡張（GCC環境かつ ENABLE_COVERAGE オン時）
include(${CMAKE_SOURCE_DIR}/tools/coverage.cmake)
enable_coverage_if_gcc(sampleapp_tests)
