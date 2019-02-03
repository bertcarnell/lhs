# CRAN Submission Checklist

## Local Windows

- Run `bclib` tests
- Run `oa` tests
- Run `lhslib` tests
- Increment `lhs` version up from CRAN
- Check the `ChangeLog` entry
- `sh developmentBuild.sh`
- `sh cmakeshell.sh` to build Visual Studio project (does not compile)
- Doxygen
- RStudio
  - Document
  - `testthat` tests
  - `R CMD build`
  - `R CMD check --as-cran`
  - `pkgdown::build_site`

## Local Linux

- R CMD


## Travis and Appveyor

## R-hub

## win-builder

## Reverse Dependencies

