# DSU（Union Find）

`cp::dsu` は、頂点番号 `0` から `n - 1` の互いに素な集合を管理します。
`cp/data_structure/dsu.hpp` をインクルードしてください。
C++17対応の独自実装で、ヘッダ単体で利用でき、複数の翻訳単位から安全にインクルードできます。
標準ヘッダのみを使用し、CC0-1.0で公開しています（[LICENSE](../../LICENSE)を参照）。

```cpp
#include "cp/data_structure/dsu.hpp"

int main() {
    cp::dsu uf(5);
    bool joined = uf.merge(0, 3);  // true
    bool again = uf.merge(3, 0);  // false
    bool connected = uf.same(0, 3);  // true
    int count = uf.size(3);  // 2
    return joined && !again && connected && count == 2 ? 0 : 1;
}
```

`g++ -std=c++17 -Iinclude example.cpp` でコンパイルできます。
`g++` の代わりに `clang++` も使用できます。

| API | 動作・返り値 | 時間計算量 |
| --- | --- | --- |
| `explicit dsu(int n = 0)` | 各頂点を独立した集合とする、`n` 頂点のDSUを構築 | O(n) |
| `bool merge(int a, int b)` | 2頂点の属する集合を併合し、異なる集合を併合した場合のみtrueを返す | ならし O(α(n)) |
| `bool same(int a, int b)` | 2頂点が同じ集合に属するかを返す | ならし O(α(n)) |
| `int size(int a)` | 頂点 `a` が属する集合の要素数を返す | ならし O(α(n)) |

構築時には `0 <= n <= INT_MAX` と、`n` 個の整数を格納できるメモリが必要です。
空のDSUも構築できますが、空のDSUに対する頂点操作はできません。
各頂点引数は `0 <= vertex < n` を満たす必要があります。
これらの前提条件はデバッグ時のアサーションで検査します。
アサーションを無効にした場合も、前提条件に違反する使い方はサポートしません。
メモリ確保に失敗した場合は、`std::vector` の例外がそのまま伝播します。

Union by Sizeにより、要素数の小さい木を大きい木に接続します。
反復処理による完全な経路圧縮（Path Compression）で、
探索中に通過したすべての頂点の親を根に付け替えます。
操作列全体で見ると1操作あたりの時間計算量はならし O(α(n)) です。
単一の操作では O(log n) 時間かかる場合があります。
記憶領域は O(n)、各操作の追加領域は O(1) です。
問い合わせでも経路圧縮を行うため、`same` と `size` は非constです。
自己併合や同じ集合の再併合はfalseを返し、集合の要素数を変更しません。
削除やロールバックには対応していません。

根には集合の要素数の符号を反転した値を `int` で格納し、
それ以外の頂点には親の頂点番号を格納します。
集合の要素数は最大でも `n <= INT_MAX` なので、
要素数の加算と符号反転は `int` の範囲内に収まります。
`INT_MAX` を超える頂点数には対応せず、
計算途中で `n` を超える要素数が生じることもありません。

`verify/yosupo/dsu.test.cpp` とcompetitive-verifierを使用して、
[Library CheckerのUnionfind問題](https://judge.yosupo.jp/problem/unionfind)で検証します。
単体テストでは、空集合・1頂点・端点・自己併合・重複併合・逆順の併合・
要素数の異なる集合の併合・平衡木・20万頂点・繰り返しの経路圧縮・
二重インクルード・複数翻訳単位を確認します。
5種類の固定シードを使用し、`n = 1..64` に対して計32万回の操作を行います。
独立した O(n) のラベル置換による愚直実装と、
連結性・集合の要素数・併合の返り値を比較し、定期的に全頂点対も比較します。
テストは明示的に失敗を判定するため、`NDEBUG` を定義しても実行されます。

リポジトリのルートで次のコマンドを実行してください。

```sh
CXX=g++ bash scripts/test-unit.sh
CXX=clang++ bash scripts/test-unit.sh
CXX=clang++ CXXFLAGS='-O1 -g -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer' bash scripts/test-unit.sh
# 開発用の仮想環境を有効にし、追加したヘッダと検証プログラムを先にgit addしてください。
bash scripts/verify.sh
python3 scripts/build-docs.py
```

PRのCI実行で、コンパイラ別のテスト・Sanitizer・公式テストケースの結果を確認できます。
`verification-results` アーティファクトには、検証対象一覧と結果のJSONが含まれます。
上記のコマンドは検証手順の説明であり、未実行の検証が成功したことを示すものではありません。
