/**
 * @file math.cppm
 * @brief サンプル2: Module Partitionsのメインファイル
 *
 * Module Partitionsは、大きなModuleを複数のファイルに分割する仕組みです。
 * このファイルは、分割されたPartitionをまとめる役割を果たします。
 */

// Module宣言
export module math;

// Partitionをインポートして再エクスポート
// :basic はModule内での相対的なPartition名
export import :basic;
export import :advanced;

/**
 * @brief Module全体の情報を返す
 * @return Module情報
 */
export namespace math {
inline const char* get_version() {
    return "Math Module v1.0 (with Partitions)";
}
}  // namespace math
