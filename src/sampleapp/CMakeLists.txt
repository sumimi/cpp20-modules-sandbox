#
# @file src/sampleapp/CMakeLists.txt
# @brief C++20 Modules サンプルのビルド構成を定義するファイル
#
# このファイルは、C++20 Modulesを使用したサンプルコードをビルドします。
# GCC 14 の -fmodules-ts フラグを使用して Module をコンパイルします。
#
# 注意: -fmodules-ts 使用時は Module の依存関係順序を保つため、
#       並列ビルド（-j）は使用せず -j1 でビルドしてください。
#

# C++20とModulesのサポートを有効化
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC Modules用のコンパイルフラグ
set(MODULE_COMPILE_FLAGS "-fmodules-ts")

# ファイルを依存関係順で列挙
# GCC 14 でも -fmodules-ts 使用時は import するモジュールの .gcm ファイルが
# コンパイル時に存在していなければならない。CMake が依存関係を自動解決しないため、
# ここで手動でコンパイル順序を保証する必要がある。
# （CMake 3.28+ のネイティブModuleサポートへ移行すれば自動解決可能だが、現在は未対応）
set(ALL_SOURCES
    # Module Interfaces (依存順)
    01_hello/hello.cppm
    02_partitions/math-basic.cppm
    02_partitions/math-advanced.cppm
    02_partitions/math.cppm
    03_interop/modern.cppm
    04_library/string_utils.cppm
    # Module Implementations
    04_library/string_utils-impl.cpp
    # Demo sources
    01_hello/demo_hello.cpp
    02_partitions/demo_math.cpp
    03_interop/demo_interop.cpp
    04_library/demo_library.cpp
)

# sampleapp ライブラリを作成
add_library(sampleapp ${ALL_SOURCES})

# C++20 とModules のコンパイルフラグを設定
# PRIVATE: テスト側は自身の CMakeLists.txt で明示的に追加するため伝播させない
target_compile_features(sampleapp PUBLIC cxx_std_20)
target_compile_options(sampleapp PRIVATE ${MODULE_COMPILE_FLAGS})

# インクルードディレクトリを指定
target_include_directories(sampleapp PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# .cppm ファイルに対して明示的にC++として扱う
set_source_files_properties(
    01_hello/hello.cppm
    02_partitions/math-basic.cppm
    02_partitions/math-advanced.cppm
    02_partitions/math.cppm
    03_interop/modern.cppm
    04_library/string_utils.cppm
    PROPERTIES
    COMPILE_FLAGS "${MODULE_COMPILE_FLAGS} -x c++"
)

# カバレッジ取得のためのビルド拡張（GCC環境かつ ENABLE_COVERAGE オン時）
include(${CMAKE_SOURCE_DIR}/tools/coverage.cmake)
enable_coverage_if_gcc(sampleapp)

