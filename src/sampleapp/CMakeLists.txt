#
# @file src/sampleapp/CMakeLists.txt
# @brief C++20 Modules サンプルのビルド構成を定義するファイル
#
# このファイルは、C++20 Modulesを使用したサンプルコードをビルドします。
# GCC 11+ の -fmodules-ts フラグを使用して Module をコンパイルします。
#
# 注意: CMake 3.20とGCC 11の組み合わせでは、Moduleの依存関係管理に
#       制限があるため、手動でファイル順序を管理します。
#

# C++20とModulesのサポートを有効化
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC Modules用のコンパイルフラグ
set(MODULE_COMPILE_FLAGS "-fmodules-ts")

# 正しい順序でファイルを列挙（依存関係順）
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
target_compile_features(sampleapp PUBLIC cxx_std_20)
target_compile_options(sampleapp PUBLIC ${MODULE_COMPILE_FLAGS})

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



