AGENTS.md

Repository Purpose

このリポジトリは、Windows CE 1 から Windows CE 6 までに関する技術資料・ドキュメントを収集、保存するためのリポジトリである。

主な収集対象は以下のサイトとする。

* Microsoft 公式サイト
* MSDN
* MS Learn
* Microsoft Docs
* Internet Archive / Wayback Machine

収集対象は Windows CE に関係する資料のみとする。

⸻

Collection System

資料の収集には Python と GitHub Actions を使用する。

基本的な流れは以下のとおり。

1. 収集対象 URL を管理ファイルから読み込む
2. harvest.py を実行する
3. 指定された URL からデータを取得する
4. 取得したデータをリポジトリ内に保存する
5. GitHub Actions から定期的または手動で実行できるようにする

収集処理の中心となるスクリプトは harvest.py とする。

実装方法については、この目的を満たす範囲で柔軟に決めてよい。

⸻

URL Management

収集対象 URL は、Python ソースコードに個々の URL を直接大量に記述するのではなく、管理用ファイルに分離する。

基本 URL

各収集先サイトの URL の大元となる基本形やサイト固有の情報は、必要に応じて harvest.py または設定ファイル側で定義する。

例:

https://learn.microsoft.com/...
https://msdn.microsoft.com/...
https://web.archive.org/...

個別 URL

実際に収集する個々のページについては、1 行 1 URL を基本とした管理ファイルに記載し、harvest.py が読み込んで処理する。

URL の管理形式は、後から大量の URL を追加・整理しやすいことを優先する。

⸻

Data Collection

収集ページは比較的統一された形式を持つ場合が多いが、古い Microsoft 系サイトやアーカイブされたページには、サイトごと・時代ごとに異なる特殊な HTML 構造が存在する。

そのため、収集処理では可能な限り元の情報を失わないことを優先する。

特に以下を意識する。

* HTML の構造を可能な限り保持する
* ページ内のテキストを欠落させない
* メタデータを可能な範囲で保持する
* 元 URL を保存する
* Wayback Machine 等の場合はアーカイブ URL も保持する
* 特殊なページ構造を無理に共通フォーマットへ変換しない

ただし、将来的な検索・解析・再利用に明らかに有用な形式への変換は妨げない。

「完全な正規化」よりも「原資料を失わないこと」を優先する。

⸻

Storage Structure

収集データは、収集元の種類ごとにトップレベルディレクトリを分ける。

例:

MSLearn/
MSDN/
Microsoft/
Wayback/

必要に応じて収集元を追加してよい。

各トップレベルディレクトリ以下は、元 URL の階層を可能な限り反映した構造で保存する。

例えば、

https://learn.microsoft.com/en-us/previous-versions/windows/embedded/...

を収集した場合、

MSLearn/
└── en-us/
    └── previous-versions/
        └── windows/
            └── embedded/
            ...

のように、URL から対応関係を追跡しやすい構造を基本とする。

ただし、ファイルシステム上扱えない文字や URL 特有の構造があるため、必要に応じて安全なファイル名・ディレクトリ名へ変換してよい。

重要なのは、

保存されたデータから元 URL を追跡できること

である。

⸻

Existing Data

すでに収集済みのページについては、原則として再取得をスキップする。

ただし、保存先のファイルが存在しない、破損している、または収集済みデータとして正常に扱えない場合は、再取得対象としてよい。

つまり、

URL が収集済み
    ↓
保存データが存在する
    ↓
正常なデータとして扱える
    → スキップ

とする。

一方、

URL が収集済み
    ↓
保存データが存在しない / 消失している / 不完全
    → 再取得

とする。

必要に応じて HTTP のステータス、保存時のメタデータ、ハッシュなどを利用して判定してよい。

⸻

GitHub Actions

GitHub Actions から harvest.py を実行できるようにする。
GitHub Actions の実行条件は手動のみにする。
GitHub API 等を利用する場合に必要となる Personal Access Token は、GitHub Actions の Secret として登録されている。

Secret 名:

GITHUB_PAT

GitHub Actions では、この Secret を環境変数等として harvest.py に渡して使用する。

トークンを以下へ直接記述してはならない。

* Python ソースコード
* URL 管理ファイル
* GitHub Actions の YAML
* 収集データ
* ドキュメント

⸻

Scope

このリポジトリで扱う資料の範囲は Windows CE に限定する。

対象には、Windows CE の各バージョンおよび関連する技術資料を含む。

例:

* Windows CE 1.x
* Windows CE 2.x
* Windows CE 3.x
* Windows CE .NET
* Windows CE 5.0
* Windows Embedded CE
* Windows CE 6.0
* Windows CE SDK / API / 開発資料
* Windows CE に関連する Microsoft の技術ドキュメント

Windows CE と直接関係しない一般的な Windows 資料などは、原則として収集対象に含めない。

⸻

Implementation Principles

実装では以下を基本方針とする。

1. 原資料を優先する

HTML やその他の取得データを、必要以上に加工・正規化しない。

特殊なページ構造が存在することを前提にする。

2. 再実行できるようにする

harvest.py は、途中で失敗した場合でも再度実行できるようにする。

すでに取得済みのページを無駄に再取得せず、未取得・消失したデータを継続して収集できる構造を優先する。

3. URL と保存データの対応を明確にする

保存されたファイルが、どの URL に対応するものなのか後から確認できるようにする。

必要に応じて URL や取得日時などのメタデータを保存してよい。

4. サイトごとの差異を許容する

すべてのサイトを完全に同一の HTML パーサーや変換処理に押し込める必要はない。

Microsoft、MSDN、MS Learn、Wayback Machine などで構造が異なる場合は、それぞれに適した処理を実装してよい。

5. 大量の URL を扱えるようにする

収集対象 URL は今後増加することを前提とする。

URL の追加によって harvest.py 自体を毎回変更する必要がない構造を基本とする。

6. 収集の失敗を把握できるようにする

個別 URL の取得に失敗しても、可能な範囲で他の URL の収集を継続する。

失敗した URL、HTTP エラー、解析エラーなどは、後から確認できるようログ等に残す。

⸻

Changes to the Repository

既存の構造や実装を変更する場合は、収集済みデータを不用意に破壊しないことを優先する。

特に以下には注意する。

* 既存の収集データを勝手に削除しない
* URL と保存先の対応を不用意に変更しない
* 既存データの大量な再取得を発生させない
* GitHub Actions の Secret をソースへ露出させない

一方で、収集精度、再現性、保守性を向上させるための構造変更は必要に応じて行ってよい。

⸻

Priority

実装上の判断が必要になった場合は、概ね以下の優先順位を基本とする。

1. Windows CE 資料を正しく収集できること
2. 原資料の情報を失わないこと
3. URL と保存データの対応を維持できること
4. 再実行・継続収集できること
5. 大量の URL を管理できること
6. GitHub Actions 上で安定して実行できること
7. コードや保存形式をシンプルに保つこと

これらは実装を拘束する絶対的な規則ではなく、設計判断の基準として扱う。