<!--
---
number: 002
id: cpp20-modules-sandbox
slug: cpp20-modules-sandbox

title: "C++20 Modules Sandbox"

subtitle_ja: "ヘッダファイルに別れを告げる新時代のC++"
subtitle_en: "Say goodbye to header files - Modern C++ with Modules"

description_ja: "C++20で導入されたModulesの基礎から実践まで学ぶサンプルプロジェクト。ヘッダファイルの問題点を解決する新しいコード管理手法を体系的に習得できます。"
description_en: "A sample project to learn C++20 Modules from basics to practice, mastering the new code management approach that solves header file problems."

category_ja:
  - C++
  - 言語機能
category_en:
  - C++
  - Language Features

difficulty: 2

tags:
  - cpp20
  - modules
  - modern-cpp

repo_url: "https://github.com/sumimi/cpp20-modules-sandbox"
demo_url: ""

hub: true
---
-->

# C++20 Modules Sandbox

![GitHub Repo stars](https://img.shields.io/github/stars/sumimi/cpp20-modules-sandbox?style=social)
![GitHub forks](https://img.shields.io/github/forks/sumimi/cpp20-modules-sandbox?style=social)
![GitHub last commit](https://img.shields.io/github/last-commit/sumimi/cpp20-modules-sandbox)
![GitHub license](https://img.shields.io/github/license/sumimi/cpp20-modules-sandbox)

**ヘッダファイルに別れを告げる時が来た。**

C++20で導入されたModulesは、長年C++開発者を悩ませてきたヘッダファイルの問題を根本から解決する革新的な機能です。

このリポジトリは、Modulesの基礎から実践的な使い方までを、実際のサンプルコードを通じて学習するためのプロジェクトです。

---

## 🎯 目的

このプロジェクトの目的は以下の通りです：

- **C++20 Modulesの理解と習得**： 新しいコード管理手法を体系的に学ぶ
- **ヘッダファイルの問題点の整理**： なぜModulesが必要なのかを明確にする
- **実践的なサンプル実装**： 実際に動作するコードを通じて学ぶ
- **注意点と制約の把握**： 現実的な導入判断ができるようにする

---

## 👥 対象ユーザー

- ヘッダファイルに辟易としているC++開発者
- C++20の新機能に興味がある方
- 大規模C++プロジェクトのコンパイル時間短縮に興味がある方

---

## 💡 なぜModulesなのか

### ヘッダファイルの問題点

C++の従来のヘッダファイルには、以下のような課題がありました：

1. **コンパイル時間の肥大化**
   - ヘッダファイルは各翻訳単位ごとにテキスト展開される
   - 同じヘッダを100回includeすれば、100回パースされる
   - 大規模プロジェクトでは膨大な時間の無駄

2. **includeガード/pragma onceの煩わしさ**
   - 多重includeを防ぐための定型文
   - 記述漏れや名前衝突のリスク

3. **マクロによる名前空間汚染**
   - ヘッダでdefineしたマクロがグローバルに影響
   - 予期しない動作やバグの温床

4. **依存関係の複雑化**
   - ヘッダの順序に依存する問題
   - 不要なヘッダのincludeが蓄積
   - リファクタリングを困難にする

5. **ODR（One Definition Rule）違反のリスク**
   - 異なる翻訳単位で定義が不一致になる可能性
   - デバッグが困難なリンクエラー

### Modulesがもたらす利点

C++20のModulesは、これらの問題を以下の方法で解決します：

- **高速コンパイル**： Moduleは一度だけコンパイルされ、バイナリ形式でキャッシュされる
- **明示的なエクスポート**： 公開したいシンボルだけを明示的にexport
- **マクロの隔離**： Moduleファイル内のマクロは外部に漏れない（意図的にexportしない限り）
- **順序に依存しない**： importの順序は基本的に問わない
- **ODRの保証**： Moduleは定義の一意性を保証する仕組み

---

## ⚠️ Modulesの注意点と懸念

期待が大きい一方で、現時点では以下の注意点があります：

### コンパイラサポート

- **GCC**： GCC 11以降で実験的サポート（完全サポートはGCC 14以降）

### ビルドシステムの対応状況

- **CMake**： 3.28以降で実験的サポート改善中
- **Make/Ninja**： 手動での依存関係管理が必要
- 従来のビルドシステムとの互換性に課題あり

### 移行コスト

- 既存の大規模プロジェクトをModules化するのは容易ではない
- ヘッダファイルとModulesの混在期間が長くなる可能性
- サードパーティライブラリの対応待ちになることがある

### エコシステムの成熟度

- ツール（デバッガ、プロファイラ、静的解析ツール）の対応が進行中
- ベストプラクティスがまだ確立されていない
- 情報やサンプルが少ない

**課題は多いが、それでも Modules は学ぶ価値があります。これが C++ の未来を担う仕組みになることを期待しています🙂**

---

## 🧪 サンプル実装と構成紹介

このプロジェクトでは、以下のサンプルを段階的に実装していきます：

### 1. 基本的なModule（Hello World）
- 最小限のModule定義とimport
- exportの基本的な使い方

### 2. Module Partitions
- Moduleを複数のファイルに分割する方法
- Interface PartitionとImplementation Partition

### 3. Moduleとヘッダファイルの共存
- 既存コードとの互換性を保つ方法
- Global Module Fragment

### 4. 実践的なライブラリ設計
- Moduleを使った実用的なライブラリ構造
- パブリックAPIとプライベート実装の分離

### 5. ビルドシステムとの統合
- CMakeでのModulesサポート
- 依存関係の管理

各サンプルのコード解説・学習ポイント・トラブルシューティングは **[SAMPLES.md](SAMPLES.md)** に詳しくまとめています。

---

## 🛠️ 開発環境

### 本プロジェクトの検証環境

このプロジェクトは以下の環境で開発・検証を行っています：

| 項目 | バージョン |
|------|-----------|
| **OS** | Rocky Linux 10.1 (Red Quartz) |
| **GCC** | 14.3.1 20250617 (Red Hat 14.3.1-2) |
| **G++** | 14.3.1 20250617 (Red Hat 14.3.1-2) |
| **CMake** | 3.30.5 |
| **Make** | GNU Make 4.4.1 |

> **Note**： Rocky Linux 9.3 (Blue Onyx)（GCC 11.4.1 / CMake 3.20.2）では、CMake の Modules 依存関係管理の制限と標準ライブラリヘッダとの競合が原因でビルドが困難でした。Rocky Linux 10.1 (Red Quartz) への移行により、これらの問題が解消されています。

### 必須要件

- **C++20対応コンパイラ**：
  - GCC **14以降**（GCC 11〜13はModule内外の標準ライブラリヘッダ競合により動作不安定）
- **CMake**： **3.28以降**（それ以前は Modules の依存関係を自動解決できず手動管理が必要）
- **ビルドツール**： Make または Ninja

> **Warning**： `-fmodules-ts` フラグを使用する場合、`import` 文は必ず同一ファイル内の `#include` より**後**に記述してください。逆順にすると標準ライブラリとの競合エラーが発生します。また、Module の依存関係順序を保つため、並列ビルド（`-j` オプション）は使用せず **`-j1`** でビルドしてください。

### ビルド方法

```bash
# 設定（Makeを使用）
cmake -S . -B build

# ビルド（Module依存関係のため -j1 で順次ビルド）
cmake --build build -j1

# 実行
./build/bin/main

# テスト実行
cmake --build build --target run_tests
```

> **Note**： `-fmodules-ts` を使用したModulesビルドでは並列ビルドによる `gcm.cache` の競合が発生するため、`-j1` を指定してください。

---

## 📂 ディレクトリ構成

```
cpp20-modules-sandbox/
├── src/               # アプリケーションソースコード
│   ├── main.cpp       # エントリーポイント（サンプル選択・実行）
│   └── sampleapp/     # サンプル実装（01_hello 〜 04_library）
├── test/              # テストコード
│   └── unit/
│       └── sampleapp/ # 各サンプルに対応するユニットテスト（Google Test）
├── include/           # 従来のヘッダファイル（移行期、現在は空）
├── docs/              # Doxygen設定・カスタムスタイル
├── tools/             # ビルド・解析・カバレッジスクリプト
├── .github/           # GitHub設定・Copilot指示
├── .vscode/           # VS Code設定（IntelliSense等）
├── CMakeLists.txt     # ルートCMake設定
├── SAMPLES.md         # サンプル詳細ガイド（ファイル構成・コード解説）
└── CHANGELOG.md
```

ファイルレベルの詳細な構成・テスト対応表は [SAMPLES.md](SAMPLES.md) を参照してください。

---

## 📘 関連資料

### 公式ドキュメント

- [C++20 Standard (ISO/IEC 14882:2020)](https://www.iso.org/standard/79358.html)
- [cppreference - Modules](https://en.cppreference.com/w/cpp/language/modules)

### コンパイラドキュメント

- [GCC C++20 Modules](https://gcc.gnu.org/wiki/cxx-modules)

### 日本語ドキュメント

- [cpprefjp - C++日本語リファレンス - モジュール](https://cpprefjp.github.io/lang/cpp20/modules.html)
---

## 📝 学習の進め方

1. **まずは動かしてみる**： サンプルコードをビルド・実行
2. **コードを読む**： Moduleの構文と仕組みを理解
3. **自分で書いてみる**： 既存のヘッダファイルをModule化
4. **問題に直面する**： エラーメッセージと戦い、理解を深める
5. **ベストプラクティスを探る**： 実用的な設計パターンを考える

---

## 📄 ライセンス

MIT License – 詳細は [LICENSE](LICENSE) を参照してください。

本プロジェクトは自由に利用・改変・再配布が可能です。学習目的だけでなく、商用プロジェクトでも無償で使用できます。

---

**Let's embrace the future of C++! 🚀**
