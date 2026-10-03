# corpus/chm/windows-ce-5.0/

The **documentation of Windows CE 5.0 CD1**, extracted from the 98 component
CHM help files that the product media ships
(`sources/windows-ce-5.0/P<n>_wce<component>5.chm`, see
`sources/windows-ce-5.0/PROVENANCE.md`). 20,209 pages, 108 MiB.

The CD's documentation is the platform *component* documentation: one CHM per
catalogue component, each with its introduction, how-to guides and the API
reference of that component. It complements the pages harvested from
learn.microsoft.com (`corpus/learn/windows-ce-5.0/`): only 4 of the 20,141
distinct titles appear in both trees, and the Learn harvest does not carry the
per-component reference at all.

```
corpus/chm/windows-ce-5.0/<component>/<original path inside the CHM>
```

`<component>` is the CHM's own name without its inventory prefix (`P302_`), so
`P312_wcecore5.chm` becomes `wcecore5/`. About a fifth of the size is the
MSHTML component (`wcemshtml5/`, 6,413 pages, the HTML engine's DHTML
reference), then the user interface (`wceui5/`), DirectShow (`wcedshow5/`) and
DCOM (`wcedcom5/`).

Pages per component (the full list):

  wcemshtml5 (6413)  wceui5 (2519)  wcedshow5 (1805)  wcedcom5 (977)  wcertc5
  (504)  wcesapi5 (492)  wced3dm5 (417)  wcecore5 (394)  wcetapi5 (356)
  wceupnp5 (316)  wcebluetooth5 (279)  wceddraw5 (269)  wceactsync5 (262)
  wcedvd5 (261)  wcemsmq5 (251)  wcetcpip5 (236)  wceshdocvw5 (213)
  wceurlmon5 (211)  wcevail5 (184)  wcedvmgt5 (177)  wceimm5 (174)  wcesoap5
  (166)  wcecrypto5 (161)  wceldap5 (153)  wcerdp5 (133)  wceiemlang5 (129)
  wceipv65 (125)  wcecertificates5 (121)  wceimaging5 (120)  wcewave5 (115)
  wcedialup5 (105)  wcesnmp5 (103)  wcepoom5 (93)  wcejpn5 (92)  wceobex5 (89)
  wceauthservices5 (77)  wcefonts5 (75)  wceinput5 (64)  wceservdotexe5 (64)
  wceuniscribe5 (63)  wceexchclient5 (61)  wcefiledb5 (61)  wcenls5 (61)
  wcesmartcard5 (59)  wcep2p5 (58)  wcestylus5 (52)  wcemouse5 (50)
  wceremoteconifg5 (50)  wcefilesystem5 (49)  wcetui5 (49)  wceics5 (47)
  wceedb5 (45)  wcefirewall5 (45)  wceeap5 (42)  wceredir5 (42)  wcekorea5
  (35)  wcenetui5 (33)  wcehwx5 (32)  wcemui5 (32)  wcecredentialmgr5 (31)
  wcestoragemgr5 (30)  wcechs5 (29)  wcemultimon5 (28)  wcetvlens5 (27)
  wcelass5 (24)  wcepcauthentication5 (24)  wceras5 (24)  wceaccess5 (22)
  wcefileserver5 (21)  wceipsec5 (19)  wceregistry5 (18)  wcecht5 (17)
  wceftpserver5 (17)  wcemacbridge5 (17)  wceasp5 (16)  wceie6 (16)  wcel2tp5
  (14)  wcenetapi5 (14)  wceserial5 (13)  wcenetutils5 (12)  wcepie5 (12)
  wceprint5 (11)  wcedrm5 (10)  wcevpn5 (10)  wcetelnet5 (9)  wcejscript5 (8)
  wceprintserver5 (8)  wcesystempassword5 (8)  wcevbscript5 (8)  wcenetlog5
  (7)  wcepppoe5 (7)  wceiexml5 (5)  wcephoneime5 (5)  wcecmdprocess5 (2)
  wceunisdk5 (2)  wceacm5 (1)  wceierpc5 (1)  wceoverview5 (1)

## How it is extracted

* `tools/extract-chm.py` with the `windows-ce-5.0` entry of
  `queues/chm-sets.tsv`; `.github/workflows/extract-chm.yml` runs it (7z reads
  CHM, and the runner has 7z).
* Every HTML page inside a CHM is kept with its original relative path, its
  `Windows-1252` markup re-encoded to UTF-8, and file names that clash inside
  one component get a numeric suffix.
* The `Topic Not Found` placeholder that every component CHM of this CD
  carries (97 copies of the same navigation error page) is skipped.
* 31 pages exist in two components each (`wcemouse5` and `wcestylus5` share
  their mouse/stylus pages) — the media ships them twice, so they are kept
  twice; `data/reports/duplicates.tsv` lists them.
* Re-extraction is idempotent: a component directory that already exists is
  not extracted again.
