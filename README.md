# lhs

This package provides a number of methods for creating and augmenting Latin Hypercube Samples

|<sub>Linux & MacOS</sub>|<sub>Windows</sub>|<sub>Code Coverage</sub>|<sub>CRAN Downloads</sub>|<sub>CRAN</sub>|
|:---:|:---:|:---:|:---:|:---:|
|[![Build Status](https://travis-ci.org/bertcarnell/lhs.svg?branch=master)](https://travis-ci.org/bertcarnell/lhs)|[![Build status](https://ci.appveyor.com/api/projects/status/5h8gjnq6a30r8y37/branch/master?svg=true)](https://ci.appveyor.com/project/bertcarnell/lhs/branch/master)|[![Coverage status](https://codecov.io/gh/bertcarnell/lhs/branch/master/graph/badge.svg)](https://codecov.io/github/bertcarnell/lhs?branch=master)|[![](https://cranlogs.r-pkg.org/badges/lhs)](https://cran.r-project.org/package=lhs)|[![CRAN status](https://www.r-pkg.org/badges/version/lhs)](https://cran.r-project.org/package=lhs)|

Visit the webpage [here](https://bertcarnell.github.io/lhs/)

See the Doxygen documentation [here](https://bertcarnell.github.io/lhs/html/index.html)

## Installation

You can install the released version of `lhs` from [CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("lhs")
```

You can also install the development version of `lhs` from here with:

``` r
# (if not done already:)  install.packages("devtools")
devtools::install_github("bertcarnell/lhs")
```

## Example

Create a random LHS with 10 samples and 3 variables 

``` r
X <- randomLHS(10, 3)
```

## Help

R-Help Examples of using the LHS package

- [Latin hyper cube sampling from expand.grid()](http://r.789695.n4.nabble.com/R-Latin-hyper-cube-sampling-from-expand-grid-tp816493.html)
- [Latin Hypercube Sampling with a condition](http://r.789695.n4.nabble.com/Latin-Hypercube-Sampling-with-a-condition-tp3563765.html)
- [Latin Hypercube with condition sum = 1](http://r.789695.n4.nabble.com/Latin-Hypercube-with-condition-sum-1-tp875487.html)
- [Latin hypercube sampling](http://r.789695.n4.nabble.com/latin-hypercube-sampling-tp4659028.html)
- [Latin Hypercube Sample and transformation to uniformly distributed integers or classes](http://r.789695.n4.nabble.com/Latin-Hypercube-Sample-and-transformation-to-uniformly-distributed-integers-or-classes-tp4677804.html)
- [Latin hypercube sampling from a non-uniform distribution](http://r.789695.n4.nabble.com/Latin-hypercube-sampling-from-a-non-uniform-distribution-tp4743686.html)
- [Latin Hypercube Sampling when parameters are defined according to specific probability distributions](http://r.789695.n4.nabble.com/Latin-Hypercube-Sampling-when-parameters-are-defined-according-to-specific-probability-distributions-tp4734710.html)

## Other

lhs package announcement:  [R-pkgs New R-Packages: Triangle and LHS](http://r.789695.n4.nabble.com/R-pkgs-New-R-Packages-Triangle-and-LHS-tp803930.html)
