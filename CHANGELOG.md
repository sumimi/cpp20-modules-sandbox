# 変更履歴（Changelog）

このファイルには、本プロジェクトにおけるすべての重要な変更を記録しています。

本形式は [Keep a Changelog](https://keepachangelog.com/ja/1.0.0/) に基づいており、
[セマンティック バージョニング](https://semver.org/lang/ja/) に従って運用しています。

---

## [1.1.0] - 2026-02-23

### 追加
- 各サンプルに対応するユニットテストを追加（Google Test 使用）
  - `test_hello.cpp`： サンプル1（hello Module）のテスト
  - `test_math.cpp`： サンプル2（Module Partitions）のテスト
  - `test_modern.cpp`： サンプル3（Interoperability）のテスト
  - `test_string_utils.cpp`： サンプル4（Library Design）のテスト
- SAMPLES.md にプロジェクト詳細ディレクトリ構成とサンプル・テスト対応表を追加

### 変更
- 検証環境を Rocky Linux 9.3 (Blue Onyx) から **Rocky Linux 10.1 (Red Quartz)** に移行
  - GCC 11.4.1 / CMake 3.20.2 → **GCC 14.3.1 / CMake 3.30.5**
  - 旧環境では CMake の Modules 依存関係管理の制限と標準ライブラリヘッダ競合によりビルド困難だった問題が解消
- `cmake_minimum_required` を 3.15 → **3.28** に引き上げ（Modules 依存関係の自動解決に必要）
- テストターゲットのC++バージョンを C++17 → **C++20** に変更（`import` 構文使用のため）
- `sampleapp` の `-fmodules-ts` フラグのスコープを `PUBLIC` → **`PRIVATE`** に変更し、テスト側への意図しない伝播を防止
- `gcm.cache` のシンボリックリンク生成をカスタムターゲットとして追加し、テスト時の Module 解決を安定化
- CMakeLists.txt のビルドコマンドコメントに `-j1` を明記（Module 依存関係のため並列ビルド不可）
- 必須ツールの最小バージョン要件をコメント・ドキュメントで統一（CMake 3.28以上、GCC 14以上）
- README.md の「ディレクトリ構成」を概要のみに簡略化し、詳細を SAMPLES.md に移動
- SAMPLES.md の「ビルド」コマンドに `-j1` を追加
- SAMPLES.md の「GCC 11での制限」見出しを「GCC 14での制限」に修正
- `modern.cppm` の Global Module Fragment に関するコメントを技術的に正確な記述に修正
  （「Moduleの外側として扱われる」→「グローバルモジュールに帰属する」）
- サンプル1のコードのポイントを実際の実装（`hello.cppm`）に合わせて修正

### 削除
- `dummy_test.cpp`（ビルドエラー回避用の仮テスト）を削除し、実テストに置き換え
- `test/CMakeLists.txt` から不要な `spdlog` 依存を削除

---

## [1.0.0] - 2026-01-02

### 追加
- 初回リリース
