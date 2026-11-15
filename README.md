# cp-library

C++17対応・ヘッダオンリーの競技プログラミングライブラリです。
独自に実装したコードをパブリックドメインとして公開しています。
名前空間は `cp`、依存先は標準ライブラリのみです。
ライセンスは [CC0-1.0](LICENSE) です。

```cpp
#include "cp/math/add.hpp"
static_assert(cp::add(2, 3) == 5);
```

`-std=c++17 -Iinclude` を指定してコンパイルしてください。
`cp::add` の和は `std::int64_t` の範囲内である必要があります。
[DSU（Union Find）](docs/data_structure/dsu.md) は、ならし O(α(n)) 時間で
`merge`・`same`・`size` を提供します。

- `include/cp/{math,data_structure,graph,string,geometry,utility}/`：公開ヘッダ
- `verify/yosupo/`：Library Checker用の検証プログラム
- `tests/unit/`：外部ライブラリに依存しない単体テスト
- [ビルド・検証・GitHub Pagesの設定](docs/development.md)
- [コントリビューションガイド](CONTRIBUTING.md)

GitHub ActionsでGCC・Clangによるテストを行い、competitive-verifierで
Yosupoの公式テストケースを検証します。
