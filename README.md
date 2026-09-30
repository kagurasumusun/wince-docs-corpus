# wince-docs-corpus

Windows CE / Windows Embedded CE / Compact / Windows Mobile 公式ドキュメントのコーパス
（Microsoft Learn `previous-versions`、Wayback 上の旧 MSDN、公式 CHM など）。
利用側: `wince-api`（ページは ID 単位で取得）。

| 場所 | 中身 |
|---|---|
| `corpus/learn/<product>/<id>.html` | learn.microsoft.com の previous-versions ページ（製品別） |
| `corpus/wayback/msdn-<yyyy>-<mm>/<id>.html` | web.archive.org 経由の旧 MSDN |
| `corpus/chm-extracted/<product>/` | 公式 CHM から展開したページ |
| `corpus/archives/<product>/` | 原本メディア（CHM/HLP/ZIP）＋ `PROVENANCE.md` |
| `meta/` | カタログ・索引・ギャップ・収集ログ（派生/記述データ） |
| `queues/sources/` ・ `sources/` | 収集範囲の定義と URL キュー（何を集めるか） |
| `tools/` | 収集・発見・索引・検証ツール（全コード） |
| `docs/` | 人間向けドキュメント（LAYOUT / HARVESTING / SOURCES / MIGRATION） |

規則は [docs/LAYOUT.md](docs/LAYOUT.md)、収集の回し方は [docs/HARVESTING.md](docs/HARVESTING.md)、
旧パスとの対応は [docs/MIGRATION.md](docs/MIGRATION.md)。
SQLite 索引は git ではなく Release `index-latest` にある。

ライセンス: 本文は Microsoft Learn（CC BY 4.0）等の元ソースに従う。
