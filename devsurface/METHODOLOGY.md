# Development Surface database — 方法論 (METHODOLOGY)

この文書は `devsurface/` にある **Windows CE Development Surface database** が
「何を根拠に、どう作られ、どこまで分かっていて、どこからが未確認か」を
第三者が再現・検査できる形で記録する。

* 対象: `include` / `def` / `lib` に出てくる **開発インターフェース**
  (API、データ型、構造体、列挙、定数、マクロ、DLL/エクスポート、
  インポートライブラリ、ABI、呼び出し規約、プロトタイプ、
  CE 世代・バージョンでの可用性)。
* 対象外: OS/カーネル再実装、BSP/OAK、SDK 全体の再実装、OEM 固有実装、
  互換 OS そのもの。**OS 内部は扱わない。外部から観測できる開発インターフェースだけ**を扱う。
* 本文書は方針と手順の記述であり、値の一覧ではない。値は
  `devsurface/data/` と `devsurface/index/` にある。

---

## 1. 証拠モデルと確度 (certainty)

すべての値には「どこから来たか」が付く。確度は次の語彙だけを使う
(`tools/devsurface/vocab.py` の `EVIDENCE_STATUS`)。

| 値 | 意味 | この DB での扱い |
|---|---|---|
| `documented` | 公式 Microsoft ドキュメントの本文が述べている | 値を持つ唯一の基本確度 |
| `observed` | 成果物(ヘッダ/バイナリ等)を直接見て得た | **現時点で 0 件**。収集対象外のソースを使わない限り増えない |
| `reproduced` | ツールチェーンを実行して再現した | **現時点で 0 件** |
| `derived` | documented/observed から機械的規則で計算した | 解析結果(戻り値型・引数など)に付く。決して `documented` に昇格させない |
| `inferred` | 推測 | **記録しない**。`inferred` は「確認済みとして扱えない」ことを示す語として予約されている |
| `unknown` | どの証拠でも確定していない | フィールドに `null` を入れ、名前を `uncertainty.unknown_fields` に列挙する |

`evidence_status` が `documented` 以外の値であるフィールドは、
利用側が「確認済み」として扱ってはならない。

**「文書にある」と「実行時に使える」は別**である。この DB が記録するのは
あくまで「そのコレクションのそのトピックがそう書いている」という事実である。

---

## 2. 推測禁止規則 (no-guess rules) とその実装

禁止事項と、それを機械的に防いでいる実装箇所を対応させる。

| 禁止 | 実装 |
|---|---|
| API 名からプロトタイプを推測する | 宣言はページ本文のコードブロックからのみ取る。取れなければ `declaration: null` + `parse.status: no_declaration_documented`。名前に似た既知の API を当てない |
| 他の Windows (NT 系/デスクトップ) 仕様を CE に流用する | `tools/devsurface/` は他 OS のデータを持たない。`vocab.py` には CE 以外の API 知識が 1 つも無い |
| CE 世代間で推測する | 可用性はページの記述文の引用としてのみ持つ。他世代の値で補完しない |
| 一般 ABI 論から CE の ABI を推測する | `abi.*` はページが述べた時だけ値が入る。既定は `null` + `evidence_status: unknown` |
| エクスポート/インポートを推測する | `export.name` / `export.ordinal` / `export.decorated_name` はスキーマ上 **常に `null`**(`const: null`)。欠落を値と誤認しないよう明示的に保持する |
| 構造体レイアウトを推測する | メンバは `members[]` に原文のまま。オフセットは記録しない(ドキュメントが述べていない) |
| 存在期間を推測する | 可用性は `OS Versions` 等の引用。`and later` 等の語もそのまま保持する |
| 不明を「おそらく/一般に」で埋める | 不明は `unknown`。`GAPS.md` に件数が出る |

補助規則:

* **R1** 値はソース文書からのコピーか、`vocab.py` の対応表による写像のみ。
* **R2** 宣言テキストは逐語(空白正規化のみ)で保持し、それが正典。
  解析フィールドは `derived` と明示する。
* **R3** シンボルレコードは「ページが宣言(またはラベル付きの表)を示している」場合のみ作る。
  宣言が無いのにシンボルらしいページは、穴として記録する(`gap-pages.tsv`)。
* **R4** バージョンは引用文 + 正規化結果。語彙に無い書き方は `unmapped` のまま残す
  (例: Windows CE 3.0 の `BITMAP` トピックは原文が "1.9 and later"。これは原文のまま保持し、
  推測で 1.0 に直さない)。
* **R5** ABI フィールドは、ページが述べない限り `unknown`。
  宣言中に出てくる `WINAPI` 等のマクロトークンは「宣言にその文字列がある」事実として
  `declaration_calling_convention_tokens` に入れるだけで、ABI の結論にはしない。

---

## 3. パイプライン

```
docs/, archives/, supplementary/        (このリポジトリが保持する公式ドキュメント)
        │
        ├─ tools/devsurface/extract.py       ページ → レコード (機械的抽出)
        │      → devsurface/data/_work/symbols-<book>.ndjson
        │      → devsurface/data/pages/<book>.tsv        (全ページの被覆状況)
        │
        ├─ tools/devsurface/collect_abi_facts.py   ABI 記述の引用収集
        │      → devsurface/data/abi/abi-facts.jsonl
        │
        └─ tools/devsurface/build_index.py    統合・索引生成
               → devsurface/data/symbols/<header>.jsonl   (ヘッダ別シャード)
               → devsurface/data/sources.json             (出典レジストリ)
               → devsurface/data/manifest.json            (版・圧縮規則)
               → devsurface/index/*.tsv, *.md, devsurface.sqlite3
               → devsurface/COVERAGE.md, devsurface/GAPS.md

tools/devsurface/validate.py           検証(構造・整合・逐語一致)
tools/devsurface/query.py              検索 CLI
```

コマンド(すべてリポジトリ直下で実行):

```bash
python3 tools/devsurface/extract.py --all                 # 全収集元を抽出
python3 tools/devsurface/extract.py --book mslearn-windows-ce-5.0 --force
python3 tools/devsurface/collect_abi_facts.py             # ABI 引用を収集
python3 tools/devsurface/build_index.py                   # 索引と SQLite を作る
python3 tools/devsurface/validate.py                      # 整合検証(0 で正常)
python3 tools/devsurface/validate.py --verify-declarations all   # 逐語一致の全件検証
python3 tools/devsurface/query.py summary                 # 検索例
```

* 依存: Python 3.11+、`beautifulsoup4`(lxml があれば併用)。
  `query.py` / `build_index.py` / `vocab.py` は標準ライブラリのみ。
* `--force` は再抽出。抽出元ページを変えたら必ず付け直す。
* `devsurface/data/_work/` は抽出中間物(`.gitignore` 済み)。`build_index.py` はこれを入力に
  `data/symbols/` を作る。**中間物を消した状態で `build_index.py` だけを実行すると失敗する**
  (誤って `data/symbols/` を作り直さないための安全装置)。その場合は先に
  `extract.py --all` を実行する。中間物はビルド後に削除してよい。
* `devsurface/index/devsurface.sqlite3` は生成物なのでコミットしない
  (100 MB を超えるため。`build_index.py` で約 30 秒で再生成できる)。

---

## 4. レコードの構造

1 レコード = 1 ページが扱っている 1 シンボル。
スキーマは `devsurface/schema/symbol-record.schema.json`。

| フィールド | 内容 | 確度 |
|---|---|---|
| `id` | `sym-` + sha1(`source_id\|page_id\|symbol\|declaration`)[0:16]。安定 ID | derived |
| `symbol` / `kind` / `scope` | 文書が示す名前・種別。`scope` は `Interface::Member` 形式のときの所属 | documented / derived |
| `kind_evidence.basis` | `declaration` / `source_label`(本文が "This macro …" 等と述べる) / `title_form` / `unknown` | — |
| `declaration` / `declaration_origin` | 逐語の宣言と、どのブロックから読んだか(`syntax_section`, `chm_syntax_pre`, `first_code_block`, `code_block_N`, `+glued_identifier` / `+split_identifier`) | documented |
| `documentation_role` | そのブロックがページ上でどう提示されているか。`declaration_section` / `unlabelled_block_symbol_topic` / `example_code_fragment` / `declaration_not_documented` | derived |
| `return_type` / `parameters[]` / `members[]` / `enumerators[]` / `macro_form` / `macro_value_raw` / `tag_name` | 宣言の機械解析結果 | derived |
| `parameters[].direction` / `parameters[].description` / `parameters[].documented_values[]` | ページの引数表から対応付けたもの | documented |
| `header` / `include` / `libraries[]` | `Requirements` の見出し語(Header / Defined in / Declared in / Include / Link Library / Link to …)と値。原文ラベルを `label_raw` に保持 | documented |
| `module` | `DLL` / `Module` と明記された場合のみ | documented |
| `export` | 常に `null`(squema 上 `const: null`) | unknown |
| `calling_convention` | ページが明記した場合のみ。宣言中の `WINAPI` 等はここに入れない | documented / unknown |
| `abi` | `architecture` / `data_model` / `structure_layout` / `packing` / `name_decoration`。ページが述べた時のみ | documented / unknown |
| `version_availability.statements[]` | `OS Versions:` / `Versions:` / `Runs on:` 等の引用(`label_raw`, `value_raw`)と正規化(`normalized`) | documented(正規化は derived) |
| `version_availability.status` | `documented_statement` か `unknown` | — |
| `deprecation_statements[]` | 廃止・削除・非サポートを述べた文の引用 | documented |
| `source` | `source_id`, `page_path`(このリポジトリ内のパス), `page_id`, `source_url`, `document_last_updated` | — |
| `evidence[]` | どの位置の記述を使ったか(`locator`, `detail`) | — |
| `uncertainty.unknown_fields[]` | 値が無いフィールド名。`unknown` の一覧 | — |
| `uncertainty.notes[]` | 解析上の注意(例:「宣言が別トークンに分割されており名前はタイトルから採った」) | — |
| `extraction` | `tool_version`, `extracted_on`, `corpus_revision` | — |
| `page_class` | ページ分類(§6) | derived |

読み方の要点:

* **`null` は「不明」であり「無い」ではない。** 「無い」と文書が述べた場合は
  `stated_absent: true` が付く(例: `Link Library: none`)。
* 宣言は逐語なので、解析が誤っていても原文から検証できる。
  検証は `python3 tools/devsurface/validate.py --verify-declarations all`。

### データ量を抑えるための圧縮 (compaction v1)

`build_index.py` は shard 書き出し時に、定数や他ファイルと重複するフィールドを落とす。
規則は `devsurface/data/manifest.json` に列挙され、`validate.py` は圧縮後の契約で検査する。
主なもの:

* `source.book_path` / `source.page_title` → `data/pages/*.tsv` と `data/sources.json` にある
* `evidence[].source_id` / `.page_path` → レコード直下の `source` と同一
* `extraction.tool` / `.method` / `.verbatim_declaration` → `manifest.json` に定数として記載
* version statement の `derived` と `normalized.raw` / `.normalized_text` → `value_raw` と重複
* `parse.derived_fields` → 常に同じ
* `uncertainty.declaration_parse_is_mechanical` → 常に真

---

## 5. 出典 (provenance) と追跡

* 出典レジストリ `devsurface/data/sources.json` は収集元ごとに
  `id` / `kind` / `publisher` / `collection` / `book_path` / `version_scope` /
  `locator_template` / `rights_status` を持つ。権利の扱いは `devsurface/RIGHTS.md`。
* 各レコードは `source.page_path` でこのリポジトリ内の実ファイルを指す。
  ここから元ページを直接開いて照合できる。
* ネット上の元 URL は `source.source_url`、またはアーカイブ媒体なら
  `locator_template`(`archives/...zip::<page_id>`)で示す。
* 同一シンボルが複数の収集元にある場合は
  `devsurface/index/symbols-across-books.tsv` に 1 行でまとまる。

---

## 6. ページ分類と網羅状況

`devsurface/data/pages/<book>.tsv` は **抽出対象ページを 1 行も落とさず**記録する。
列は `page_id / source_id / path / title / page_class / symbol_count / kind / symbol /
declaration_origin / header / library / os_versions_raw / declaration_status /
duplicate_of / source_url`。

| `page_class` | 意味 |
|---|---|
| `symbol_page` | シンボルレコードを作ったページ |
| `prose_page_code_fragment` | タイトルがシンボル名でない解説ページのコード片から記録を作った (役割 `example_code_fragment`) |
| `concept_or_overview` | 概説・手順・ガイド。シンボル宣言なし |
| `duplicate_page` | 同じページの重複ファイル(`duplicate_of` に正規ファイル名) |
| `identifier_title_no_requirements` | タイトルは識別子風だが Requirements が無い |
| `identifier_title_no_declaration` | 識別子風タイトル + Requirements はあるが宣言が見つからない |
| `declaration_candidate_mismatch` | 宣言らしきブロックはあるが識別子がタイトルと一致しない(穴として保持) |
| `example_code_page` | コンパイラ/リンカ/メイクのエラートピック。コードは例であり宣言ではない |
| `out_of_scope_managed_surface` | マネージド(.NET)向け。include/def/lib の対象外 |
| `deprecation_notice` | タイトル自体が廃止を示すページ |

`COVERAGE.md`(自動生成)に件数、`GAPS.md` に「値が無いフィールドの件数と、
それを埋めるには何の証拠が要るか」が出る。

---

## 7. 検索 (query surface)

```bash
python3 tools/devsurface/query.py summary                       # 全体像
python3 tools/devsurface/query.py symbol GetTickCount           # 名前で(部分一致も)
python3 tools/devsurface/query.py header winbase --kind function --limit 20
python3 tools/devsurface/query.py library coredll
python3 tools/devsurface/query.py version windows-ce-1.0
python3 tools/devsurface/query.py kind struct
python3 tools/devsurface/query.py params CreateFileW
python3 tools/devsurface/query.py members SYSTEMTIME
python3 tools/devsurface/query.py unknown calling_convention    # 不明な領域を明示的に見る
python3 tools/devsurface/query.py abi packing                   # ABI 引用
python3 tools/devsurface/query.py gaps identifier_title_no_requirements
python3 tools/devsurface/query.py sql "SELECT symbol, header, library FROM symbols WHERE kind='callback' LIMIT 10"
```

ファイル索引:

| ファイル | 内容 |
|---|---|
| `index/INDEX.md` | 収集元・シャード・件数の入口 |
| `index/by-header.md`, `by-library.md`, `by-book.md` | 見出し別 / ライブラリ別 / 収集元別の一覧 |
| `index/shards.tsv` | `data/symbols/<header>.jsonl` と件数 |
| `index/gap-pages.tsv` | 宣言が見つからなかったページ等の穴 |
| `index/symbols-across-books.tsv` | シンボル × 収集元 |
| `index/version-differences-normalized.tsv` | 正規化した version id が収集元間で異なるもの(主リスト) |
| `index/version-differences.tsv` | 句読点・大小文字を揃えた上で原文が異なるもの |
| `index/version-differences-text-only.tsv` | version id は一致するが文言だけ違うもの(世代差ではない) |

差分の読み方: 主リスト (`-normalized.tsv`) が「収集元同士が別のバージョンだと述べている」
ケース。`-text-only.tsv` は「`1.0 and later` と `Windows CE 1.0 and later.` のように
書き方が違うだけ」で、世代差の証拠ではない。

### シャードの分割

1 つのヘッダのシャードが 20 MB を超える場合、`<header>.part-01.jsonl` … に分割して書き出す
(`build_index.py` の `SHARD_SPLIT_BYTES`)。レコード自身の `shard` フィールドは分割前の名前を
保つので、分割はファイル配置だけの都合であり、検索や検証の意味は変わらない。

SQLite (`index/devsurface.sqlite3`) の表:
`symbols` / `parameters` / `members` / `enumerators` / `version_statements` /
`pages` / `sources` / `abi_facts`。

---

## 8. 検証 (`validate.py` が検査する内容)

1. 構造: 必須フィールド、語彙(`kind`, `parse.status`, `documentation_role`)、
   `id` の式、`uncertainty.unknown_fields` と実値の整合
   (「不明」と書いてあるフィールドに値が入っていないか)。
2. 参照: `page_path` の実在、`source_id` が `sources.json` にあるか、
   version statement の正規化結果が語彙に解決するか、
   シャード配置が `vocab.record_shard()` と一致するか、
   ページ TSV の列数、ABI 引用のページ実在と逐語性。
3. 逐語: `--verify-declarations N|all` で、保存された宣言が今も元ページに見つかるか。

「OK」は**内部整合がとれている**ことだけを意味する。ドキュメントが完全であることは意味しない。
未確認領域は `COVERAGE.md` / `GAPS.md` / `query.py unknown` に出る。

---

### 検証の実施記録 (2026-09-25, corpus_revision bbe085281)

| 実行 | 結果 |
|---|---|
| `validate.py` | 44,888 レコード / 15 収集元 / 25 ABI 引用 — **0 error, 0 warning** |
| `validate.py --verify-declarations all` | 34,109 件の宣言を元ページと逐語照合 — **不一致 0** |
| `collect_abi_facts.py --check` | 25 件すべてアンカー一致 |
| 追加サンプル照合 | `version-differences-normalized.tsv`(1,087 件)から無作為 3 件を抽出し、引用文が各ページに逐語で存在することを確認 |

宣言が無い 10,779 レコードは照合対象外(そもそも宣言が無いことが記録されている)。
上記は「内部整合と逐語性」の確認であり、**ドキュメントの完全性や API の実在を保証するものではない**。

---

## 9. 現時点の到達点と未確認領域 (継続管理)

* 抽出済み: `docs/` と `supplementary/` の 8 収集元(下表)。行数は `COVERAGE.md` を参照。
* 未着手: `pagesgap/INDEX.tsv` の未取得ページ(3,642 件)はコーパス自体が未収集。
  Windows CE 1.0 / 2.0 の媒体はプロビナンスのみで、API リファレンス本文は未解析。
  `.NET Compact Framework` は対象外(マネージド)。
* `abi.architecture` / `abi.data_model` / `export.*` / `module` は全件 `unknown`。
  これらを埋めるには「観測」(ヘッダやバイナリの直接検査)が必要で、
  現行の収集範囲では得られない。**文書から推測して埋めることはしない。**
* 呼び出し規約も同じ。`WINAPI` 等のトークンが宣言にある事実だけを保持している。
* 遺伝的な限界: 宣言が HTML 上で連結・分割されている場合(例: `DWORDGetTickCount(void);`)、
  元の空白位置は復元できない。その場合は名前をタイトルから採り、`parse.status: partial` と
  注記を付ける(値は捏造しない)。
* 抽出が拾わなかったものは `page_class` と `declaration_status` に残る。
  これは「見なかったことにする」ための仕組みではなく、次に調べる対象の一覧である。

---

## 10. 拡張の手順

**収集元を足す**
1. `tools/devsurface/vocab.py` の `SOURCES` に ID・権利(`rights`)・`locator_template` を追加。
2. `EXTRACT_BOOKS` に加える(または `CATALOG_ONLY_BOOKS` にカタログのみとして加える)。
3. `python3 tools/devsurface/extract.py --book <id>` → `build_index.py` → `validate.py`。

**ABI 記述を足す**
1. `tools/devsurface/collect_abi_facts.py` の `FACTS` に「アンカー文字列 + 抽出モード」を追加。
   文面は書かない(ページから取る)。
2. 実行。アンカーが見つからなければ**失敗する**(検証できない事実は書かない)。

**語彙を足す**
* バージョン表記は `vocab.VERSION_VOCAB`、ラベルは `vocab.REQUIREMENT_LABELS`。
  足すのは「文書に現れる表記」とその写像だけ。推測した API 知識は入れない。

**レビューの観点(変更時に必ず確認)**
* `validate.py` が 0 で終わるか。`--verify-declarations` を回したか。
* 新しい `page_class` / `documentation_role` / `kind` を増やしたなら、
  `build_index.py` の説明文と本方法論の表を更新したか。
* 新しいフィールドは `schema/symbol-record.schema.json` と `validate.py` の `REQUIRED` に入れたか。
* 「不明を値で埋めていないか」。埋めたくなったら `GAPS.md` に行を足す。
