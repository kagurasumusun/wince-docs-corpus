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

収集対象となる情報は**根こそぎすべて収集する**こと。
収集したデータは上記 README の階層にきれいに整理し、
`data/index/INDEX.tsv` を最新に保つこと。

## 収集対象外(絶対に行わない)

* Shared Source、Platform Builder のソース、Visual Studio のソース
  (Microsoft 公式「公開資料」に該当しない)
* 許可されていない非公開情報、入手経路不明・出所不明の資料、非合法な入手
* **dump(バイナリ/デバイスダンプ)由来の情報**
  (旧 `coredll/*.def` はこの理由で 2026-09-18 に削除済み)
* Wine / ReactOS / MinGW / mingw-w64 / w32api / mingwrt
  — 収集せず、比較対象・調査対象にもしない。
  **唯一の例外:** CeGCC 版 w32api および CeGCC 版 mingwrt は
  「値の確認・参考」程度にのみ参照可(転載・宣言の根拠にはしない)。
* デスクトップ Win32 / デスクトップ .NET Framework のリファレンスページ
  (Windows CE の資料ではない。旧 `pagesw/` `pagesnet/` `pagesmag/` は
  2026-09-18 にこのポリシーにより削除済み)

大手の信頼できる公開情報は**二次的な対象**として扱えるが、上記の
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
