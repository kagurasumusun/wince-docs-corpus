# devsurface — Windows CE Development Surface database

Windows CE 1.0〜6.0 / Embedded Compact 7 の**公式公開ドキュメント**(このリポジトリが
保持する `docs/`, `archives/`, `supplementary/`)から、**開発インターフェースの事実だけ**を
機械的に抽出したデータベース。対象は `include` / `def` / `lib` に出てくる API・型・
構造体・列挙・定数・マクロ・エクスポート・ABI・バージョン可用性。
OS 内部・カーネル再実装・BSP/OAK・OEM 実装は対象外。

* 何を根拠に、どう作り、どこが未確認か → **[METHODOLOGY.md](METHODOLOGY.md)**
* 権利・出典表示・収集元ごとの区分 → **[RIGHTS.md](RIGHTS.md)**
* 網羅状況(自動生成) → **[COVERAGE.md](COVERAGE.md)**
* 値が無いフィールドと、それを埋めるのに要る証拠 → **[GAPS.md](GAPS.md)**

## 中身

| パス | 内容 |
|---|---|
| `data/symbols/<header>.jsonl` | シンボルレコード(1 行 1 レコード)。ヘッダ別シャード |
| `data/pages/<book>.tsv` | 抽出対象ページ 1 行ずつの被覆状況(分類・記号・Requirements) |
| `data/abi/abi-facts.jsonl` | ABI に関する文書記述の逐語引用 |
| `data/sources.json` | 出典レジストリ(収集元 / 権利 / 範囲) |
| `data/manifest.json` | 版・抽出方法・圧縮規則 |
| `index/INDEX.md` ほか `index/*.md`, `*.tsv` | 人間向け索引(ヘッダ別・ライブラリ別・差分・穴) |
| `index/devsurface.sqlite3` | 検索用 SQLite(**生成物なので未コミット**) |
| `schema/symbol-record.schema.json` | レコードの契約 (draft-07) |

## 使い方

```bash
# 検索(生成物の SQLite が無ければ先に作る)
python3 tools/devsurface/build_index.py
python3 tools/devsurface/query.py summary
python3 tools/devsurface/query.py symbol GetTickCount
python3 tools/devsurface/query.py unknown calling_convention   # 不明領域の確認

# 再生成と検証
python3 tools/devsurface/extract.py --all          # ページ → レコード
python3 tools/devsurface/collect_abi_facts.py      # ABI 引用
python3 tools/devsurface/build_index.py            # 統合・索引
python3 tools/devsurface/validate.py               # 0 で正常
```

## 原則(短縮版)

1. 値は**文書にあるものだけ**。無い値は `null` + `evidence_status: "unknown"` +
   `uncertainty.unknown_fields` に列挙する。推測で埋めない。
2. 「文書がそう書いている」と「実行時に使える」は別物として記録する。
3. 宣言は逐語で保持し、機械解析の結果は `derived` と明示する。
4. エクスポート名・序数・装飾名などは**スキーマ上つねに `null`**(欠落を値と誤読させない)。
5. 不明領域は隠さず `COVERAGE.md` / `GAPS.md` / `query.py unknown` に出す。
