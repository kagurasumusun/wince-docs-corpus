# Development Surface database — 権利・出典の扱い (RIGHTS)

この文書は `devsurface/` の DB が「何を、どの権利根拠で保持し、何を保持しないか」を定める。
収集元ごとの機械可読な値は `devsurface/data/sources.json` の `rights_status` にあり、
本文書はその語彙の意味と判断の根拠を与える。

---

## 1. 前提: この DB が保持するもの / しないもの

**保持するもの(事実と短い引用)**

* API・型・構造体・列挙・定数・マクロの**名前**、**宣言(逐語)**、引数、戻り値
* `Header:` / `Defined in:` / `Link Library:` などの**書誌的事実**
* 可用性を示す**短い引用**(例: `OS Versions: Windows CE 1.0 and later.`)
* ABI に関する**短い引用**(`devsurface/data/abi/abi-facts.jsonl` の 25 件、
  いずれも 1〜2 文。根拠の確認に必要な最小限)

これらは「開発インターフェースの仕様情報」であり、元ドキュメントの**表現の創作物ではなく事実**である。
引用は「どの値がどこから来たか」を第三者が検証できるようにするために付けている。

**保持しないもの(明示的な禁止)**

* 第三者の**ソースコード**(Windows CE 関連を含む)。ヘッダの実物、SDK のソース、
  Platform Builder / Shared Source / Visual Studio のソースは**一切取り込まない・複製しない**。
* 非公開情報、漏洩情報、入手経路不明の資料、アクセス制御を回避して得た資料
* ライセンスが不明な資料を**確認せずに**取り込むこと
* 長文の転載。引用は値を裏付ける最小限に留める(宣言 1 件、文 1〜2 件)

**証拠に使わないもの**

* Windows NT 系(Win32/Win64/ReactOS/Wine 等)の仕様は、構造理解の参考にはなるが
  **Windows CE の根拠としては扱わない**(このリポジトリの収集方針。方針文は履歴から参照できる)。
* cegcc / mingw など第三者実装は参考情報であり、CE の根拠にしない。

---

## 2. `rights_status` 語彙と、証拠レジストリとの対応

`data/sources.json` で使う値は次の 2 種。括弧内は
`origin/autonomous/bootstrap-evidence-registry` の
`data/sources/archive-sources.json` が使う語彙への対応。

| この DB の値 | 意味 | 証拠レジストリ語彙 | この DB での扱い |
|---|---|---|---|
| `cc-by-4.0` | Microsoft Learn `previous-versions` の当該ページ。ページに CC BY 4.0 の条件が示される | `cleared_for_intended_use`(条件: 出典表示) | 抽出・引用可。出典表示を必須とする(§3) |
| `archived-copy-rights-unknown` | Microsoft 公式配布物のアーカイブ、または Wayback Machine に保存された MSDN スナップショット。**配布条件を確認していない** | `rights_unknown` | 事実抽出と最小限の引用のみ。アーカイブそのものの再配布は本 DB の範囲外 |

証拠レジストリ側の語彙のうち未使用のもの
(`likely_permitted_but_verify`, `permission_required`, `counsel_review`,
`cleared_with_conditions`)は、必要になった時点でこの表に追記する。
**現在どの収集元も「確認済みの再配布可」ではない。**

---

## 3. 出典表示 (attribution)

* すべてのドキュメントは **© Microsoft Corporation**。DB の収集元レコードは
  `publisher: "Microsoft Corporation"` を保持する。
* CC BY 4.0 のページ由来の引用は、`source.source_url`(または
  `sources.json` の `locator_template` と `page_id`)で出典を一意に指せる。
* 本 DB は Microsoft の承認・後援を受けたものではない。Microsoft の商標・製品名は
  識別の目的でのみ用いる。
* 収集元の上位ディレクトリ(`archives/*/PROVENANCE.md`)に、入手日・入手元 URL・
  アーカイブのチェックサム等の来歴を記録する。

---

## 4. 収集元ごとの状況

| `source_id` | 種別 | 権利 | 判断 |
|---|---|---|---|
| `mslearn-windows-ce-5.0` | 公式オンライン | `cc-by-4.0` | 抽出・引用可。Microsoft Learn の `previous-versions` |
| `mslearn-windows-ce-net-4x` | 公式オンライン | `cc-by-4.0` | 同上 |
| `mslearn-windows-embedded-ce-6.0` | 公式オンライン | `cc-by-4.0` | 同上 |
| `mslearn-windows-embedded-compact-7` | 公式オンライン | `cc-by-4.0` | 同上(宣言付きページは 0 件) |
| `mslearn-uncategorized` | 公式オンライン | `cc-by-4.0` | 同上(バージョン表記のないページ) |
| `supplementary-windows-mobile-6.5` | 公式オンライン | `cc-by-4.0` | 同上(Windows Mobile 6.5 = CE 5.x 系) |
| `chm-windows-ce-3.0` | 公式配布アーカイブ | `archived-copy-rights-unknown` | Download Center 配布の CHM を抽出。事実と最小限の引用のみ |
| `wayback-msdn-2010-05` | アーカイブ写し | `archived-copy-rights-unknown` | Wayback 保存の MSDN。同上 |
| `media-windows-ce-1.0` … `media-windows-ce-6.0` | 公式媒体 | `archived-copy-rights-unknown` | **本文は未解析**。来歴のみ記録 |
| `mslearn-dotnet-compact-framework` | 公式オンライン | `cc-by-4.0` | 対象外(マネージド)。カタログのみ |

`archived-copy-rights-unknown` の 8 件は、**確認が済むまで再配布可能とみなさない**。
本 DB 自体(事実の集合と最小限の引用)は、元ドキュメントの代替物ではないため
リポジトリ内での利用は問題ないと判断しているが、リポジトリ外へ配布する場合は
この区分の収集元由来の引用の扱いを再確認すること。

---

## 5. 収集時の約束 (このリポジトリ全体)

* 取得は**公式公開**の経路のみ。認証回避・アクセス制御回避・非公開への到達は行わない。
* サイトへは逐次アクセス、429/503 ではバックオフする(`tools/harvest.py` の実装)。
  Wayback・Learn への大量同時アクセスはしない。
* 著作権・利用条件が不明な資料は、**出所と条件の確認が済むまで**取り込まない。
* 第三者のソースコードは収集対象にしない(事実・仕様・宣言・ABI メタデータのみ)。

---

## 6. 検証のしかた

1. 値の出所: レコードの `source.page_path` を開き、`evidence[].locator` の位置を見る。
2. 宣言の逐語性: `python3 tools/devsurface/validate.py --verify-declarations all`。
3. ABI 引用の逐語性: `python3 tools/devsurface/collect_abi_facts.py --check`。
4. 収集元の権利区分: `python3 tools/devsurface/query.py sql "SELECT id, rights_status, scope FROM sources"`。

---

## 7. 未確認事項 (オープン)

* Microsoft Learn ページに付される CC BY 4.0 が、`previous-versions` の
  全ページに一様に適用されるか(ページごとのフッター表記で確認する必要がある)。
* Wayback Machine のスナップショットの再利用条件は、元コンテンツの条件と
  アーカイブ側の条件の双方を確認する必要がある。
* Download Center の配布物(CHM/ZIP/HLP)のライセンス条項は、
  各 `PROVENANCE.md` に記録した入手元ページの条件を確認する必要がある。
* 上記 3 点のいずれも、**確認が済むまで `cc-by-4.0` への格上げはしない**。
