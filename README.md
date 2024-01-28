<table>
<tr>
<td>
<img align="left" width="200" height="200" src="logo.svg"/>
</td>
</tr>
</table>

|                                                         <sub>Actions</sub>                                                          |                                                                          <sub>Windows</sub>                                                                           |                                                              <sub>Code Coverage</sub>                                                              |                                      <sub>Website</sub>                                      |                                             <sub>Doxygen</sub>                                              |                              <sub>CRAN Downloads</sub>                               |                                          <sub>CRAN</sub>                                           |
|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|:---------:|
| [![R build status](https://github.com/bertcarnell/lhs/workflows/R-CMD-check/badge.svg)](https://github.com/bertcarnell/lhs/actions) | [![Build status](https://ci.appveyor.com/api/projects/status/5h8gjnq6a30r8y37/branch/master?svg=true)](https://ci.appveyor.com/project/bertcarnell/lhs/branch/master) | [![Coverage status](https://codecov.io/gh/bertcarnell/lhs/branch/master/graph/badge.svg)](https://codecov.io/github/bertcarnell/lhs?branch=master) | [![](https://img.shields.io/badge/pkgdown-lhs-blue.svg)](https://bertcarnell.github.io/lhs/) | [![](https://img.shields.io/badge/Doxygen-lhs-blue.svg)](https://bertcarnell.github.io/lhs/html/index.html) | [![](https://cranlogs.r-pkg.org/badges/lhs)](https://cran.r-project.org/package=lhs) | [![CRAN status](https://www.r-pkg.org/badges/version/lhs)](https://cran.r-project.org/package=lhs) |

# lhs

`lhs` provides a number of methods for creating and augmenting Latin
Hypercube Samples and Orthogonal Array Latin Hypercube Samples.

-   Reverse Dependency Checks
    -   [Depends](etc/revdep_README_Depends.md)
    -   [Imports](etc/revdep_README_Imports.md)
    -   [Suggests](etc/revdep_README_Suggests.md)
-   Docker Images for Testing
    -   [lhs-debug](https://hub.docker.com/repository/docker/bertcarnell/lhs-debug)
    -   [lhs-revdep](https://hub.docker.com/repository/docker/bertcarnell/lhs_revdep)
        built from [here](https://github.com/bertcarnell/r-debug)

## Installation

You can install the released version of `lhs` from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("lhs")
```

You can also install the development version of `lhs` from github with:

``` r
if (!require(devtools)) install.packages("devtools")
devtools::install_github("bertcarnell/lhs")
```

## Quick Start

Create a random LHS with 10 samples and 3 variables:

``` r
require(lhs)
```

    ## Loading required package: lhs

``` r
set.seed(1776)
X <- randomLHS(n = 10, k = 3)
```

Create a design that is more optimal than the random case:

``` r
X_gen <- geneticLHS(10, 3, pop = 100, gen = 5, pMut = 0.1)
X_max1 <- maximinLHS(10, 3, method = "build", dup = 5)
X_max2 <- maximinLHS(10, 3, method = "iterative", optimize.on = "result", eps = 0.01, maxIter = 300)
X_imp <- improvedLHS(10, 3, dup = 5)
X_opt <- optimumLHS(10, 3, maxSweeps = 10, eps = 0.01)
```

|     | Method   | Mean Distance | Minimum Distance |
|:----|:---------|--------------:|-----------------:|
| 6   | optimum  |        0.7289 |           0.4598 |
| 2   | genetic  |        0.7190 |           0.4059 |
| 4   | maximin  |        0.7246 |           0.3975 |
| 5   | improved |        0.7028 |           0.3872 |
| 3   | maximin  |        0.7296 |           0.3611 |
| 1   | random   |        0.7067 |           0.2709 |

Augment an existing design:

``` r
Y <- randomLHS(10, 5)
Z <- augmentLHS(Y, 2)
dim(Z)
```

    ## [1] 12  5

Build an orthogonal array LHS:

``` r
# a 9 row design is returned because a 10 row design is not possible with these algorithms
W9 <- create_oalhs(10, 3, bChooseLargerDesign = FALSE, bverbose = FALSE)
dim(W9)
```

    ## [1] 9 3

``` r
# a 16 row design is returned because a 10 row design is not possible with these algorithms
W16 <- create_oalhs(10, 3, bChooseLargerDesign = TRUE, bverbose = FALSE)
dim(W16)
```

    ## [1] 16  3

## Help

R-Help Examples of using the LHS package

-   [Latin hyper cube sampling from
    expand.grid()](https://stat.ethz.ch/pipermail/r-help/2007-January/124143.html)
-   [Latin Hypercube Sampling with a
    condition](https://stat.ethz.ch/pipermail/r-help/2011-June/279906.html)
-   [Latin Hypercube with condition sum =
    1](https://stat.ethz.ch/pipermail/r-help/2008-November/180929.html)
-   [Latin hypercube
    sampling](https://www.mail-archive.com/r-help@r-project.org/msg192704.html)
-   [Latin Hypercube Sample and transformation to uniformly distributed
    integers or
    classes](https://stat.ethz.ch/pipermail/r-help/2013-October/361263.html)
-   [Latin hypercube sampling from a non-uniform
    distribution](https://stat.ethz.ch/pipermail/r-help/2017-August/448475.html)
-   [Latin Hypercube Sampling when parameters are defined according to
    specific probability
    distributions](https://stat.ethz.ch/pipermail/r-help/2017-June/447266.html)

StackExchange Examples:

-   [Latin Hypercube around set
    points](https://stats.stackexchange.com/questions/370983/latin-hypercube-around-set-points)
-   [Latin hypercube sampling with categorical
    variables](https://stats.stackexchange.com/questions/388963/latin-hypercube-sampling-with-categorical-variables)
-   [Are Latin hypercube samples
    uncorrelated](https://stats.stackexchange.com/questions/147789/are-latin-hypercube-samples-uncorrelated)
-   [Stopping rule for Latin hypercube sampling
    (LHS)](https://stats.stackexchange.com/questions/407262/stopping-rule-for-latin-hypercube-sampling-lhs)
-   [Is a group of random hypercube samples equivalent to a single latin
    hypercube with more
    samples?](https://stats.stackexchange.com/questions/411085/is-a-group-of-random-hypercube-samples-equivalent-to-a-single-latin-hypercube-wi)
-   [Taking samples of data using Latin Hypercube
    Sampling](https://stats.stackexchange.com/questions/439271/taking-samples-of-data-using-latin-hypercube-sampling)
-   [Number of parameter sets generated by latin hyercube
    sampling](https://stats.stackexchange.com/questions/460918/number-of-parameter-sets-generated-by-latin-hyercube-sampling)
-   [Is there a way to check if sample obeys the Latin Hypercube
    Sampling
    rule?](https://stats.stackexchange.com/questions/465492/is-there-a-way-to-check-if-sample-obeys-the-latin-hypercube-sampling-rule)
-   [Effectiveness of Latin Hypercube
    Sampling](https://stats.stackexchange.com/questions/468202/effectiveness-of-latin-hypercube-sampling)
-   [Dividing CDF rather than PDF equally in Latin Hypercube
    Sampling](https://stats.stackexchange.com/questions/468293/dividing-cdf-rather-than-pdf-equally-in-latin-hypercube-sampling)
-   [Stratified sampling / QMC simulation for compound Poisson
    rv](https://stats.stackexchange.com/questions/469963/stratified-sampling-qmc-simulation-for-compound-poisson-rv)
-   [Using Latin Hypercube Sampling with a condition that the sum of two
    variables should be less than
    one](https://stats.stackexchange.com/questions/474911/using-latin-hypercube-sampling-with-a-condition-that-the-sum-of-two-variables-sh)
-   [How to generate a design for a response surface with a discrete
    input random
    variable?](https://stats.stackexchange.com/questions/444997/how-to-generate-a-design-for-a-response-surface-with-a-discrete-input-random-var)
-   [Is it necessary to shuffle X coordinates in Latin hypercube
    Sampling?](https://stats.stackexchange.com/questions/498492/is-it-necessary-to-shuffle-x-coordinates-in-latin-hypercube-sampling-lhc)

## Other

lhs package announcement: [R-pkgs New R-Packages: Triangle and
LHS](https://stat.ethz.ch/pipermail/r-packages/2006/000715.html)
