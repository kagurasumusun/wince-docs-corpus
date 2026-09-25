# Unverified fields (generated)

Counts are over 44888 symbol records. A field listed here has no documented
value in the corpus; it is recorded as `unknown` rather than filled in.

| field | records without a documented value |
|---|---:|
| `abi.architecture` | 44888 |
| `abi.data_model` | 44888 |
| `export.decorated_name` | 44888 |
| `export.name` | 44888 |
| `export.ordinal` | 44888 |
| `module` | 44888 |
| `calling_convention` | 42364 |
| `library` | 23246 |
| `header` | 19745 |
| `declaration` | 10779 |

## What would close each gap

| field | evidence that could establish it |
|---|---|
| `calling_convention` | a rights-cleared header or a compiled artifact that prints the convention; never inferable from the API name |
| `export.name` / `export.ordinal` / `export.decorated_name` | a module's export table (observed) or a rights-cleared `.def` |
| `module` | a topic that states the DLL, or an observed import table |
| `header` / `library` | a topic with a Requirements block; many topics omit it |
| `abi.*` | a document that states the data model, packing or layout for the target CPU |
