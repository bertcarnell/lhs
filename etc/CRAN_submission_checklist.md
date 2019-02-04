# CRAN Submission Checklist

## Local Windows

- [ ] Run `bclib` tests
  - `sh cmakeshell.sh Release`
- [ ] Run `oa` tests
  - ensure any recent changes to `bclib` are `git pull`ed
  - `sh cmakeshe1l.sh Release`
- [ ] Run `lhslib` tests
  - ensure any recent change to `bclib` are `git pull`ed
  - `sh cmakeshell.sh Release`
- [ ] Increment `lhs` version up from CRAN
- [ ] Check the `ChangeLog` entry
- [ ] `sh developmentBuild.sh`
- [ ] `sh cmakeshell.sh` to build Visual Studio project (does not compile)
- [ ] Doxygen
- RStudio
  - [ ] Document with `roxygen2`
  - [ ] Run `testthat` tests
  - [ ] `R CMD build`
  - [ ] `R CMD check --as-cran`
  - [ ] `pkgdown::build_site()`
- [ ] push all updates to `github`

#### rhub

- from R or RStudio
  - [ ] rhub::check_for_cran(path="path-to-package.tar.gz")
  - [ ] rhub::check_with_valgrind(path="path-to-package.tar.gz")
  - [ ] rhub::check_with_sanitizers(path="path-to-package.tar.gz")

#### win-builder
- https://win-builder.r-project.org/upload.aspx
- [ ] upload the <package>.tar.gz

## Travis and Appveyor
- check travis and appveyor results once built
  - [ ] https://travis-ci.org/bertcarnell/lhs
  - [ ] https://ci.appveyor.com/project/bertcarnell/lhs/branch/master

## Local Linux

- [ ] `git pull`
- [ ] Run `bclib` tests
  - `sh cmakeshell.sh Release`
- [ ] Run `oa` tests
  - ensure any recent changes to `bclib` are `git pull`ed
  - `sh cmakeshe1l.sh Release`
- [ ] Run `lhslib` tests
  - ensure any recent change to `bclib` are `git pull`ed
  - `sh cmakeshell.sh Release`
- [ ] `sh cmakeshell.sh` to build Visual Studio project (does not compile)
- [ ] `R CMD build lhs`
- [ ] `R CMD check --as-cran --use-valgrind`

## Reverse Dependencies

- [ ] Build the Docker image
  - [Notes](notes.md)
- [ ] Check the dependencies
  - [Notes](notes.md)
- upload the results
  - copy to /etc and push 
