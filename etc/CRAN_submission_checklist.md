# CRAN Submission Checklist

## Local Windows

- [ ] Run `bclib` tests in PowerShell
  - `cd ../bclib`
  - `sh cmakeshell.sh Release`
- [ ] Run `oa` tests in PowerShell
  - ensure any recent changes to `bclib` are `git pull`ed as a submodule in `oa` (`git submodule update` in `git bash`)
  - `cd ../oa/src`
  - `sh cmakeshell.sh Release`
- [ ] Run `lhslib` tests in PowerShell
  - ensure any recent change to `bclib` are `git pull`ed as a submodule in `lhslib` (`git submodule update` in `git bash`)
  - `cd ../lhslib/src`
  - `sh cmakeshell.sh Release`
- [ ] Increment `lhs` version up from CRAN if not already done
- [ ] Check the `ChangeLog` entry for the version to be released
- [ ] Copy the sub-project code in to `src`
  - `sh developmentBuild.sh`
- [ ] Build the Visual Studio project in PowerShell (does not compile, but is useful for debugging and C++ development)
  - `sh cmakeshell.sh`
- [ ] Doxygen deployment to `docs` in PowerShell (output directory specified in the `Doxyfile`)
  - `doxygen Doxyfile`
- RStudio
  - [ ] Document with `roxygen2` by running `Document` in the UI
  - [ ] Run `testthat` tests by running `Test Package` in the UI
  - [ ] Build the `.tar.gz` or `R CMD build`
  - [ ] Run `check` or `R CMD check --as-cran`
  - [ ] In R, create the `pkgdown` site with `pkgdown::build_site()`
- [ ] `commit` and `push` all updates to `github`

#### rhub

- from R or RStudio
  - [ ] `rhub::check_for_cran(path="path-to-package/lhs-<version>.tar.gz")`
  - [ ] `rhub::check_with_valgrind(path="path-to-package/lhs-<version>.tar.gz")`
  - [ ] `rhub::check_with_sanitizers(path="path-to-package/lhs-<version>.tar.gz")`

#### win-builder

- https://win-builder.r-project.org/upload.aspx
- [ ] upload the `lhs-<version>.tar.gz` from the step above

## Travis and Appveyor

- check travis and appveyor results once built
  - [ ] https://travis-ci.org/bertcarnell/lhs
  - [ ] https://ci.appveyor.com/project/bertcarnell/lhs/branch/master

## Local Linux

- [ ] `git pull`
- [ ] Run `bclib` tests
  - `cd ../bclib`
  - `sh cmakeshell.sh Release`
- [ ] Run `oa` tests
  - ensure any recent changes to `bclib` are `git pull`ed
  - `cd ../oa`
  - `git submodule update`
  - `sh cmakeshell.sh Release`
- [ ] Run `lhslib` tests
  - ensure any recent change to `bclib` are `git pull`ed
  - `cd ../lhslib`
  - `git submodule update`
  - `sh cmakeshell.sh Release`
- [ ] `sh developmentBuild.sh`
- [ ] `sh cmakeshell.sh`
- [ ] `R CMD build lhs`
- [ ] `R CMD check --as-cran --use-valgrind`

## Reverse Dependencies

- [ ] Build the Docker image
  - [Notes](notes.md)
- [ ] Check the dependencies
  - [Notes](notes.md)
- upload the results
  - copy to /etc and push 

## Submit to CRAN

- [ ] [form](https://cran.r-project.org/submit.html)
- [ ] Tag the github repository with the version

