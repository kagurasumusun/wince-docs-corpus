# AGENTS.md — wince-docs-corpus 収集・整理ポリシー

このリポジトリは **Windows CE 1.0〜6.0 に関する Microsoft 公式公開ドキュメント**
を収集・保存するコーパスである。利用先は
[Akari-dev](https://github.com/kagurasumusun/Akari-dev)
(Windows CE API サーフェス: headers / .def / import libraries /
startup・toolchain integration) の資料照合である。

## 収集対象(完全収集)

* MSDN(ライブおよびアーカイブ)
* Microsoft Learn(`learn.microsoft.com/en-us/previous-versions/windows/embedded`)
* Wayback Machine(web.archive.org)に保存された MSDN スナップショット
* Microsoft Download Center の公式ドキュメントアーカイブ(CHM/HLP/ZIP)
* Microsoft ignite
* その他大手の信用できる公開情報サイト
* cegcc/gnuce/pascal/cegcc-w32api/cegcc-mingwrt

収集対象となる情報は**根こそぎすべて収集する**こと。
収集したデータは上記 README の階層にきれいに整理し、
`data/index/INDEX.tsv` を最新に保つこと。


## 注意
Win32/Win64/ReactOS/Wine等はWindows CEではなくてWindows NT系であるため構造やapiの書き方の理解として参考にするがWindowsCE自体の情報の根拠としては扱わないこと。
mingwについてもcegcc版と通常盤との違いに注意すること。
WindowsCEは、Win32のapiサブセットであるためWin32の一部に互換がある。
そのため扱う情報の内容に十分注意すること。

## 収集対象外(絶対に行わない)

* Shared Source、Platform Builder のソース、Visual Studio のソース
  (Microsoft 公式「公開資料」に該当しない)
* 許可されていない非公開情報、入手経路不明・出所不明の資料、非合法な入手

大手の信頼できる公開情報も**優先的な対象**として扱えるが、上記の
除外事項に該当する情報を含む場合は収集範囲に含めない。

## 収集方法の制約

* サイトへの多並列・大量同時アクセスは行わない。
  収集はサイトごとに逐次(1 リクエストずつ)、固定ディレイ
  (learn.microsoft.com: 0.4 秒 / web.archive.org: 1.5 秒)、
  HTTP 429/503 では指数バックオフ。
* 収集は `tools/harvest.py` を使う(再開可能、既存ページはスキップ)。
* **こまめに push する**(harvester は `--batch` ページごとに
  commit & push)。

## セッション手順

1. 作業開始時にこのリポジトリを再取得(clone / pull)する。
2. 収集・整理を行い、こまめに push する。
3. 作業終了時に INDEX を再生成(`python3 tools/make-index.py`)して push。
4. 作業環境からは Akari-dev 以外をクリーンアップする
   (コーパスの正はこの GitHub リポジトリ)。

## ライセンス

* Microsoft Learn / MSDN ページ: © Microsoft Corporation、CC BY 4.0。
  出典表記: **Microsoft Learn / Microsoft Corporation**。原文のまま保存。
* Download Center の CHM/HLP: 各ディレクトリの `PROVENANCE.md` に
  公式ダウンロードページを記録。未改変で保存。
