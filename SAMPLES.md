# C++20 Modules サンプル実装ガイド

このドキュメントでは、各サンプルの詳細な説明とコードの解説を提供します。

---

## 📂 プロジェクト詳細ディレクトリ構成

```
cpp20-modules-sandbox/
├── src/
│   ├── main.cpp                       # エントリーポイント（サンプル選択・実行）
│   ├── CMakeLists.txt
│   └── sampleapp/
│       ├── CMakeLists.txt
│       ├── 01_hello/                  # サンプル1： 基本的なModule
│       │   ├── hello.cppm             # Module定義（exportあり/なしの使い分け）
│       │   └── demo_hello.cpp         # デモ実装
│       ├── 02_partitions/             # サンプル2： Module Partitions
│       │   ├── math.cppm              # メインModule（Partitionをまとめる）
│       │   ├── math-basic.cppm        # Partition： 基本算術
│       │   ├── math-advanced.cppm     # Partition： 高度な数学関数
│       │   └── demo_math.cpp          # デモ実装
│       ├── 03_interop/                # サンプル3： ヘッダファイルとの共存
│       │   ├── legacy.h               # 従来のヘッダファイル
│       │   ├── modern.cppm            # Module（Global Module Fragment使用）
│       │   └── demo_interop.cpp       # デモ実装
│       └── 04_library/                # サンプル4： 実践的なライブラリ設計
│           ├── string_utils.cppm      # Module Interface（公開API宣言）
│           ├── string_utils-impl.cpp  # Module Implementation（実装部）
│           └── demo_library.cpp       # デモ実装
└── test/
    ├── CMakeLists.txt
    └── unit/
        └── sampleapp/
            ├── CMakeLists.txt
            ├── test_hello.cpp         # サンプル1のユニットテスト
            ├── test_math.cpp          # サンプル2のユニットテスト
            ├── test_modern.cpp        # サンプル3のユニットテスト
            └── test_string_utils.cpp  # サンプル4のユニットテスト
```

### サンプルとテストの対応

| サンプル | 実装ディレクトリ | テストファイル |
|---------|----------------|--------------|
| 01_hello | `src/sampleapp/01_hello/` | `test/unit/sampleapp/test_hello.cpp` |
| 02_partitions | `src/sampleapp/02_partitions/` | `test/unit/sampleapp/test_math.cpp` |
| 03_interop | `src/sampleapp/03_interop/` | `test/unit/sampleapp/test_modern.cpp` |
| 04_library | `src/sampleapp/04_library/` | `test/unit/sampleapp/test_string_utils.cpp` |

テストは Google Test (GTest) を使用しています。実行方法は後述の「[実行方法](#-実行方法)」を参照してください。

---

## 🎓 サンプル1： 基本的なModule（Hello World）

**ディレクトリ：** `src/sampleapp/01_hello/`

### 学習ポイント

- `export module` によるModule宣言
- `export` キーワードで関数を公開
- `import` でModuleを読み込み
- exportしない関数は内部実装のみで使用可能

### ファイル構成

- **hello.cppm**： Module定義ファイル
- **demo_hello.cpp**： Moduleを使用するデモ

### コードのポイント

```cpp
// hello.cppm
module;          // Global Module Fragment
#include <string>

export module hello;  // Module名を宣言

// export namespace で名前空間全体を公開する方法
export namespace sample {
    // 名前空間内の全メンバーが外部から使用可能になる
    std::string say_hello(const std::string& name);
    std::string get_module_info();
}
```

> **補足**： `export namespace { ... }` の代わりに、名前空間なしで個々の関数に `export` を付ける方法もあります。
> ```cpp
> export module hello;
> export std::string say_hello(const std::string& name);  // 個別にexport
>        std::string internal_helper();                   // exportなし→外部から不可
> ```

```cpp
// demo_hello.cpp
import hello;  // Moduleをインポート

void demo_01_hello() {
    sample::say_hello("C++ Developer");  // OK
    sample::get_module_info();           // OK
}
```

### ヘッダファイルとの違い

| 項目 | ヘッダファイル | Module |
|------|---------------|--------|
| 多重定義防止 | `#ifndef` / `#pragma once` 必要 | 不要 |
| 公開範囲 | すべて公開 | `export` で明示的に指定 |
| コンパイル | 毎回パース | 一度だけコンパイル、バイナリキャッシュ |
| マクロ | グローバルに影響 | Module内に隔離 |

---

## 🔀 サンプル2： Module Partitions

**ディレクトリ：** `src/sampleapp/02_partitions/`

### 学習ポイント

- 大きなModuleを複数のファイルに分割
- Interface Partitionの使い方
- Partitionのエクスポートと再利用

### ファイル構成

- **math.cppm**： メインModule（Partitionをまとめる）
- **math-basic.cppm**： 基本算術のPartition
- **math-advanced.cppm**： 高度な数学関数のPartition
- **demo_math.cpp**： デモ

### コードのポイント

```cpp
// math-basic.cppm
export module math:basic;  // Partition名は :basic

export namespace math::basic {
    int add(int a, int b);
    int subtract(int a, int b);
}
```

```cpp
// math.cppm
export module math;  // メインModule

// Partitionをインポートして再エクスポート
export import :basic;
export import :advanced;
```

```cpp
// demo_math.cpp
import math;  // メインModuleをインポートするだけ

void demo_02_partitions() {
    math::basic::add(10, 5);      // :basic Partitionの関数
    math::advanced::power(2, 8);  // :advanced Partitionの関数
}
```

### Partitionsの利点

- **コードの整理**： 機能ごとにファイルを分割できる
- **コンパイル時間**： 変更された部分だけ再コンパイル
- **可読性**： 役割が明確になる
- **保守性**： 大規模プロジェクトでの管理が容易

---

## 🔄 サンプル3： Moduleとヘッダファイルの共存

**ディレクトリ：** `src/sampleapp/03_interop/`

### 学習ポイント

- Global Module Fragmentの使い方
- 既存のヘッダファイルをModuleから使用
- 段階的な移行戦略

### ファイル構成

- **legacy.h**： 従来のヘッダファイル
- **modern.cppm**： Module（ヘッダと共存）
- **demo_interop.cpp**： デモ

### コードのポイント

```cpp
// modern.cppm
module;  // Global Module Fragment開始（ここから export module xxx; までの領域）

// この領域でincludeされたヘッダの宣言は「グローバルモジュール」に帰属する
// → 名前付きModule（modern）には属さないが、Module実装内から利用可能
#include "legacy.h"
#include <string>

export module modern;  // Module宣言（ここから先が名前付きModuleの領域）

export namespace modern {
    // レガシー機能を使用した新しい関数
    std::string use_legacy_from_module() {
        return legacy::get_legacy_message();  // GMF でincludeした legacy.h を利用可能
    }
}
```

### Global Module Fragmentとは？

Module宣言（`export module xxx;`）の前に `module;` を書くと、その領域は「Global Module Fragment（GMF）」となります。

GMF 内で `#include` した宣言は、**グローバルモジュール**（名前のない暗黙のモジュール）に帰属します。これは「名前付きモジュールの外側」とは異なります：

| 特性 | GMFのinclude |  
|------|-------------|
| 翻訳単位への帰属 | 同じ翻訳単位の一部（`modern.cppm`内）|
| Module帰属先 | グローバルモジュール（名前付きModuleではない）|
| Module実装からの利用 | **可能**（`legacy::get_legacy_message()` を呼べる）|
| exportされるか | **されない**（Module外部からはアクセス不可）|

### 移行戦略

1. **段階1**： 既存コードはそのまま、新規コードをModuleで書く
2. **段階2**： Global Module Fragmentで既存ヘッダを使いながらModule化
3. **段階3**： 最終的にすべてModuleに移行

---

## 📦 サンプル4： 実践的なライブラリ設計

**ディレクトリ：** `src/sampleapp/04_library/`

### 学習ポイント

- Module InterfaceとImplementationの分離
- 実用的なライブラリ構造
- ヘッダ/ソース分離に近い設計

### ファイル構成

- **string_utils.cppm**： Module Interface（公開API）
- **string_utils-impl.cpp**： Module Implementation（実装部）
- **demo_library.cpp**： デモ

### コードのポイント

```cpp
// string_utils.cppm (Interface)
export module string_utils;

export namespace utils {
    // 関数宣言のみ（ヘッダファイルのような役割）
    std::string to_upper(const std::string& str);
    std::string to_lower(const std::string& str);
    std::string trim(const std::string& str);
}
```

```cpp
// string_utils-impl.cpp (Implementation)
module string_utils;  // 実装であることを宣言

namespace utils {
    // 実装を記述（ソースファイルのような役割）
    std::string to_upper(const std::string& str) {
        // 実装
    }
}
```

### 従来の .h/.cpp との比較

| 従来の方法 | Module方式 |
|-----------|-----------|
| header.h<br>（宣言） | module_name.cppm<br>（Module Interface） |
| source.cpp<br>（実装） | module_name-impl.cpp<br>（Module Implementation） |
| `#include "header.h"` | `import module_name;` |

### 利点

- **コンパイル高速化**： Module Interfaceは一度だけコンパイル
- **依存関係の明確化**： exportされたAPIのみが見える
- **リンクエラーの削減**： ODRが保証される
- **保守性**： インターフェースと実装が明確に分離

---

## 🚀 実行方法

### ビルド

```bash
# プロジェクトルートで実行
cmake -S . -B build
cmake --build build -j1  # Module依存関係のため並列ビルド不可
```

### 実行

```bash
# すべてのサンプルを実行
./build/bin/main 0

# 個別のサンプルを実行
./build/bin/main 1  # サンプル1
./build/bin/main 2  # サンプル2
./build/bin/main 3  # サンプル3
./build/bin/main 4  # サンプル4

# インタラクティブモード
./build/bin/main
```

### テスト実行

```bash
# ユニットテストをビルド＆実行
cmake --build build -j1 --target run_tests

# テストバイナリを直接実行
./build/bin/unit_tests

# 特定のテストのみ実行（例： サンプル1のテスト）
./build/bin/unit_tests --gtest_filter="HelloTest.*"
```

---

## 📝 重要な注意事項

### GCC 14での制限

1. **標準ライブラリのimport不可**
   ```cpp
   // ❌ GCC 14ではまだサポートされていない
   import std;
   
   // ✅ 代わりにincludeを使用
   #include <string>
   #include <vector>
   ```

2. **-fmodules-ts フラグが必須**
   ```bash
   g++ -std=c++20 -fmodules-ts -x c++ module.cppm -c
   ```

3. **Module cache**
   - `gcm.cache/` ディレクトリにModuleキャッシュが生成される
   - 問題が発生したら削除してリビルド

### ベストプラクティス

1. **ファイル拡張子**
   - Module Interface： `.cppm` または `.ixx`
   - Module Implementation： `.cpp`

2. **名前空間**
   - Moduleとは別に、C++の名前空間も適切に使用する

3. **エクスポート範囲**
   - 必要最小限のシンボルのみexport
   - 内部実装の詳細は隠蔽

4. **ビルドシステム**
   - Module間の依存関係に注意
   - Partitionは親Moduleより先にコンパイル

---

## 🔍 トラブルシューティング

### よくあるエラー

**エラー： `module xxx not found`**
```
解決方法： 
- Module Interfaceファイルが先にコンパイルされているか確認
- CMakeLists.txtでファイルの順序を確認
```

**エラー： `fatal error: header file xxx not found`**
```
解決方法：
- Global Module Fragmentでincludeしているか確認
- インクルードパスが正しく設定されているか確認
```

**キャッシュの問題**
```bash
# Module cacheをクリア
rm -rf build/
cmake -S . -B build
cmake --build build -j1
```

---

## 📚 参考資料

- [C++20 Modules - cppreference](https://en.cppreference.com/w/cpp/language/modules)
- [GCC C++20 Modules](https://gcc.gnu.org/wiki/cxx-modules)
- [A Practical Guide to C++ Modules](https://vector-of-bool.github.io/2019/03/10/modules-1.html)

---

**次のステップ**： 実際にコードをビルドして動かしてみましょう！ 🚀
