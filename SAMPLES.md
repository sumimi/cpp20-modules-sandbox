# C++20 Modules サンプル実装ガイド

このドキュメントでは、各サンプルの詳細な説明とコードの解説を提供します。

---

## 📂 サンプル構成

```
src/sampleapp/
├── 01_hello/              # サンプル1: 基本的なModule
├── 02_partitions/         # サンプル2: Module Partitions
├── 03_interop/            # サンプル3: ヘッダファイルとの共存
└── 04_library/            # サンプル4: 実践的なライブラリ設計
```

---

## 🎓 サンプル1: 基本的なModule（Hello World）

**ディレクトリ:** `src/sampleapp/01_hello/`

### 学習ポイント

- `export module` によるModule宣言
- `export` キーワードで関数を公開
- `import` でModuleを読み込み
- exportしない関数は内部実装のみで使用可能

### ファイル構成

- **hello.cppm**: Module定義ファイル
- **demo_hello.cpp**: Moduleを使用するデモ

### コードのポイント

```cpp
// hello.cppm
export module hello;  // Module名を宣言

export namespace sample {
    // exportすると外部から使用可能
    export std::string say_hello(const std::string& name);
    
    // exportしないと内部のみで使用可能
    std::string internal_helper();
}
```

```cpp
// demo_hello.cpp
import hello;  // Moduleをインポート

void demo_01_hello() {
    sample::say_hello("World");  // OK
    // sample::internal_helper(); // エラー！exportされていない
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

## 🔀 サンプル2: Module Partitions

**ディレクトリ:** `src/sampleapp/02_partitions/`

### 学習ポイント

- 大きなModuleを複数のファイルに分割
- Interface Partitionの使い方
- Partitionのエクスポートと再利用

### ファイル構成

- **math.cppm**: メインModule（Partitionをまとめる）
- **math-basic.cppm**: 基本算術のPartition
- **math-advanced.cppm**: 高度な数学関数のPartition
- **demo_math.cpp**: デモ

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

- **コードの整理**: 機能ごとにファイルを分割できる
- **コンパイル時間**: 変更された部分だけ再コンパイル
- **可読性**: 役割が明確になる
- **保守性**: 大規模プロジェクトでの管理が容易

---

## 🔄 サンプル3: Moduleとヘッダファイルの共存

**ディレクトリ:** `src/sampleapp/03_interop/`

### 学習ポイント

- Global Module Fragmentの使い方
- 既存のヘッダファイルをModuleから使用
- 段階的な移行戦略

### ファイル構成

- **legacy.h**: 従来のヘッダファイル
- **modern.cppm**: Module（ヘッダと共存）
- **demo_interop.cpp**: デモ

### コードのポイント

```cpp
// modern.cppm
module;  // Global Module Fragment開始

// この領域でincludeされたヘッダはModuleの外側として扱われる
#include "legacy.h"
#include <string>

export module modern;  // Module宣言

export namespace modern {
    // レガシー機能を使用した新しい関数
    std::string use_legacy_from_module() {
        return legacy::get_legacy_message();
    }
}
```

### Global Module Fragmentとは？

Module宣言（`export module xxx;`）の前に `module;` を書くと、その領域は「Global Module Fragment」となります。ここで `#include` したヘッダは、従来通りの動作をします。

### 移行戦略

1. **段階1**: 既存コードはそのまま、新規コードをModuleで書く
2. **段階2**: Global Module Fragmentで既存ヘッダを使いながらModule化
3. **段階3**: 最終的にすべてModuleに移行

---

## 📦 サンプル4: 実践的なライブラリ設計

**ディレクトリ:** `src/sampleapp/04_library/`

### 学習ポイント

- Module InterfaceとImplementationの分離
- 実用的なライブラリ構造
- ヘッダ/ソース分離に近い設計

### ファイル構成

- **string_utils.cppm**: Module Interface（公開API）
- **string_utils-impl.cpp**: Module Implementation（実装部）
- **demo_library.cpp**: デモ

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

- **コンパイル高速化**: Module Interfaceは一度だけコンパイル
- **依存関係の明確化**: exportされたAPIのみが見える
- **リンクエラーの削減**: ODRが保証される
- **保守性**: インターフェースと実装が明確に分離

---

## 🚀 実行方法

### ビルド

```bash
# プロジェクトルートで実行
cmake -S . -B build
cmake --build build
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

---

## 📝 重要な注意事項

### GCC 11での制限

1. **標準ライブラリのimport不可**
   ```cpp
   // ❌ GCC 11ではまだサポートされていない
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
   - Module Interface: `.cppm` または `.ixx`
   - Module Implementation: `.cpp`

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

**エラー: `module xxx not found`**
```
解決方法: 
- Module Interfaceファイルが先にコンパイルされているか確認
- CMakeLists.txtでファイルの順序を確認
```

**エラー: `fatal error: header file xxx not found`**
```
解決方法:
- Global Module Fragmentでincludeしているか確認
- インクルードパスが正しく設定されているか確認
```

**キャッシュの問題**
```bash
# Module cacheをクリア
rm -rf build/
cmake -S . -B build
cmake --build build
```

---

## 📚 参考資料

- [C++20 Modules - cppreference](https://en.cppreference.com/w/cpp/language/modules)
- [GCC C++20 Modules](https://gcc.gnu.org/wiki/cxx-modules)
- [A Practical Guide to C++ Modules](https://vector-of-bool.github.io/2019/03/10/modules-1.html)

---

**次のステップ**: 実際にコードをビルドして動かしてみましょう！ 🚀
