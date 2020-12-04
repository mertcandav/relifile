<div align="center">
  
# RELIFILE

![CodeQL](https://github.com/mertcandav/relifile/workflows/CodeQL/badge.svg)
![Darwin CI](https://github.com/mertcandav/relifile/workflows/Darwin%20CI/badge.svg)
![Ubuntu CI](https://github.com/mertcandav/relifile/workflows/Ubuntu%20CI/badge.svg)
![WindownNT CI](https://github.com/mertcandav/relifile/workflows/WindownNT%20CI/badge.svg)

**Relife is a scripting language that can be used for software compilation.**

#### [LICENSE](https://github.com/mertcandav/relifile/blob/main/LICENSE)
#### [CONTRIBUTE](https://github.com/mertcandav/relifile/blob/main/CONTRIBUTING.md)
#### [CODE OF CONDUCT](https://github.com/mertcandav/relifile/blob/main/CODE_OF_CONDUCT.md)

</div>

### Quick Start

```
# Quick Start

$GPP = g++
$OUT = -o
$DIR_SOURCE = ./src

workflow
| headerExample
| compile

work headerExample ($DIR_SOURCE)/header.cc
| $GPP $0 $OUT header.o

work compile $(DIR_SOURCE)/main.cc, appName
| $GPP -c $0 header.o $OUT $1

```
