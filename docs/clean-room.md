# Clean room: the definition, the cases, and what this repository does

This project builds a knowledge base of Windows CE interfaces — functions,
types, constants, member lists, calling conventions, link information — from
Microsoft's published documentation, so that a generator can produce
include/def material from the knowledge base **alone**, without looking at the
pages again. That is the situation clean-room practice exists for, so the
project states the definition it follows, the cases it rests on, and the
machine-checkable way it keeps to them.

## 1. The definition

Clean-room design (the "Chinese wall") is *copying a design by reverse
engineering and then recreating it without infringing the copyrights attached
to the original*: a first team studies the original and writes a
**specification**, reviewed so that it contains no protected expression; a
second team, which has never seen the original, implements from that
specification. The defence it provides is **independent creation**. It does not
defeat patents (independent invention is not a defence there), and it is best
practice rather than a legal requirement.

The canonical picture, from the Phoenix BIOS work (and IBM's settlements with
Corona, Eagle, Matsushita/Panasonic and Kyocera): a first team "studied the IBM
BIOS … and described everything it did as completely as possible without using
or referencing any actual code", then a second team "who had no prior knowledge
of the IBM BIOS and had never seen its code" wrote a new BIOS "working only
from the first team's functional specifications".

## 2. The cases

| Case | Held | What it means here |
|------|------|--------------------|
| *Apple Computer v. Franklin Computer* (3d Cir. 1983) | Firmware is copyrightable — the precedent that made the clean-room work necessary | Nothing here is taken from a binary; the sources are documents |
| *NEC v. Intel* (1990) | The first US trial where the clean-room argument was accepted: similarity in routines that compatibility *forces* can be free of creative expression | Interface facts (names, orders, signatures) are compatibility-constrained; the project still keeps the texts it relies on quoted and traceable rather than reconstructing them from memory |
| *Sega v. Accolade* (9th Cir. 1992) | Intermediate copying during reverse engineering to find the interface requirements is fair use | Reading the documentation to learn the interface is this corpus's purpose |
| *Sony v. Connectix* (9th Cir. 2000) | Intermediate copying of a BIOS to build an emulator is fair use; a functional work gets a lower degree of protection | Reinforces that functional interface information is the low-protection end — and that a "Chinese wall" that leaks does not help |
| *Google v. Oracle* (US 2021) | Reimplementing a declaring interface, taking only what a new and transformative program needs, can be fair use | Interface declarations are the material this project extracts; it records what the pages state and nothing beyond |
| Directive 2009/24/EC (EU) | Recital 11: "only the expression of a computer program is protected … ideas and principles which underlie any element of a program, including those which underlie its interfaces, are not protected"; Art. 6 allows the reproduction needed for interoperability | The clearest statement that interface facts are not protected expression |
| 著作権法 30条の4 (JP, 2018) | Uses that do not enjoy the expression — including 情報解析 (extraction, comparison, classification) — are permitted within the limits of what is necessary, unless they unreasonably harm the rightholder; 47条の4 covers incidental computer uses | The extraction here is 情報解析; the "unreasonably harm" limit is why the corpus stays offline and is not republished as a competing copy of Microsoft's documentation |

Two limits follow, and the project must not get them wrong:

* **Copyright is not the only right.** Patents, trademarks and trade secrets are
  outside the clean-room argument, and so is the **contract** formed by a
  licence or terms of use. Those are handled per item in `docs/LICENSING.md` — a
  clean-room process does not excuse publishing a page whose own terms forbid
  publication.
* **Clean room is a process for producing a work**, not a licence to keep or
  publish the original. The original documents stay collected under their own
  terms; only the derived facts are free of the copyright question (and the
  terms of each page still govern copies of it).

## 3. How this repository is arranged as a clean room

| Clean-room role | In this repository |
|-----------------|--------------------|
| First team (studies the original) | `tools/page_parse.py` + `tools/build-kb.py`: read `corpus/`, write `knowledge/`. Open-source documents in `corpus/oss/` are read as documents only (`layer: oss`); their source trees are not in the corpus, and a code sample on a page is not turned into a declaration |
| Reviewed specification | `knowledge/`: facts with their page, plus the declarations **quoted** as evidence of what the page prints — not as the project's own text |
| Second team (implements from the specification only) | a consumer such as `tools/gen-include-def.py`: reads `knowledge/`, writes `build/` |
| The wall | `gen-include-def.py` refuses to open anything under `corpus/` (`check_spec_path()`; `CORPUS_READS` counts any attempt) and `tools/check-cleanroom.py` runs a real build and requires the count to be 0 |
| Independent creation | every record names its page; nothing is reconstructed from memory or analogy. The generator writes a declaration only as the page printed it. A header or a library is taken from the version being built; a borrow from another CE set or from the Win32 reference is marked (`header_from`, `library_from`) and a desktop header is never passed off as a Windows CE header. A declaration whose page lost the spaces between tokens is replaced by another CE page's quotation only when, whitespace aside, the two texts are the same, and the borrow is marked (`borrowed_from` ending `|spacing`); a copy that also prints a calling convention or a different type is not used. A `#define` in `*.h.constants` is the one derived line: the page printed a table row, the row is quoted above the line, and the keyword is marked derived. A number stated only by the Win32 reference is not borrowed |

## 4. What the tools verify (`python3 tools/check-cleanroom.py`)

Result on 2026-10-05, with `--all` (every quote, no sampling; the file is
`knowledge/reports/cleanroom.tsv`):

| Invariant | Checked | Violations |
|-----------|--------:|-----------:|
| no fact without a document — every record's `source.path` (an entity: every page it lists) exists in `corpus/` | 374,617 | 0 |
| quotes are faithful — the record's characters, in order, whitespace aside, are on the page it names (declaration texts, requirement values, constraint sentences, **layout-table rows, constant-table rows and open-source document quotations**) | 268,375 | 0 |
| documented members are on their page — every `documented_fields` name occurs in one of the pages that document the entity (an A/W pair documents one structure) | 5,204 | 0 |
| sample code stays out of the declarations — no entity's `syntax_declarations` points at a `role: "example"` or `implementation` record | 59,926 | 0 |
| syntax blocks are declarations — no `role: "syntax"` text is implementation code; code blocks kept as `role: "example"` and never emitted: 4,572 | all declarations | 0 |
| the generator reads the specification only — a real `gen-include-def.py` run reports zero corpus reads | 0 reads | 0 |

The check found real defects when it was first run seriously, which is the point
of having it:

* code blocks a page prints as **samples** had been labelled `syntax`
  (a sample program, an `#include` list, an `#ifdef`-fenced block), and some
  reached the generated header fragments — the extractor now marks them
  (`implementation: true`, `role: "example"`), the generator refuses to emit
  them, and `check-kb.py` rejects an entity that points at one;
* the member lists of A/W structure pairs were attributed to a single page — the
  union and each field's own page are now recorded
  (`documented_fields_pages`, `documented_field_pages`);
* pages that had lost their line breaks as well as their spaces were yielding no
  member list at all (1,491 structure declarations); the reader now reads the
  members out of the body as printed, which is where the ABI member types come
  from (`kb/abi-offsets.jsonl` rows are checked by the same quote invariant);
* the "verbatim" claim for quotes was stronger than what the extraction
  actually does: whitespace is normalised, and the records say so
  (`spacing: "collapsed"` marks the pages that had already lost the spaces
  between tokens before this project saw them). A token-level reformatting step
  is the next thing to build on top, not something the generator does silently.

## 5. Limits

* This is not legal advice, and the full opinions were not read — the citations
  for a lawyer are: *Sony v. Connectix*, 203 F.3d 596 (9th Cir. 2000); *Sega v.
  Accolade*, 977 F.2d 1510 (9th Cir. 1992); *Google v. Oracle*, 593 U.S. 1
  (2021); *NEC v. Intel*, 1990 US Dist. LEXIS 12567. What is quoted above comes
  from the published summaries, the EU directive's own text and the Japanese
  statute.
* Clean room does not help with **patents** or **trade secrets**, and does not
  override **licence terms** — that is `docs/LICENSING.md`, where the per-item
  terms and the publication finding live.
* The corpus holds documents, not source code (`tools/check-policy.py` and
  `tools/check-corpus.py` enforce that), but the documents themselves print
  code samples. Those are quarantined as `role: "example"` /
  `implementation: true` and never take part in the generated include/def
  material.
* An implementation may be *read* to see which Windows CE names it uses.
  GNU LGPL 2.1 puts activities other than copying, distribution and
  modification outside the licence, so the reading is not a licensed copy.
  The source is not stored, and nothing it prints is turned into a
  declaration or a constant. Qt 4.8's Windows CE header says its stand-in
  numbers are not the real values; those numbers are not recorded.
  `knowledge/reports/oss-surface.tsv` is that observation. The generator
  does not read it.
