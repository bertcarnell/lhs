<div>
  <table>
    <tr>
      <td>
        <img align="left" width="200" height="200" src="logo.svg"/>
      </td>
    </tr>
  </table>
</div>

This package provides a number of methods for creating and augmenting 
Latin Hypercube Samples and Orthogonal Array Latin Hypercube Samples.

|<sub>Actions</sub>|<sub>Linux & MacOS</sub>|<sub>Windows</sub>|<sub>Code Coverage</sub>|<sub>CRAN Downloads</sub>|<sub>CRAN</sub>|
|:---:|:---:|:---:|:---:|:---:|:---:|
|[![R build status](https://github.com/bertcarnell/lhs/workflows/R-CMD-check/badge.svg)](https://github.com/bertcarnell/lhs/actions)|[![Build Status](https://travis-ci.org/bertcarnell/lhs.svg?branch=master)](https://travis-ci.org/bertcarnell/lhs)|[![Build status](https://ci.appveyor.com/api/projects/status/5h8gjnq6a30r8y37/branch/master?svg=true)](https://ci.appveyor.com/project/bertcarnell/lhs/branch/master)|[![Coverage status](https://codecov.io/gh/bertcarnell/lhs/branch/master/graph/badge.svg)](https://codecov.io/github/bertcarnell/lhs?branch=master)|[![](https://cranlogs.r-pkg.org/badges/lhs)](https://cran.r-project.org/package=lhs)|[![CRAN status](https://www.r-pkg.org/badges/version/lhs)](https://cran.r-project.org/package=lhs)|

Visit the webpage [here](https://bertcarnell.github.io/lhs/)

See the Doxygen documentation [here](https://bertcarnell.github.io/lhs/html/index.html)

The reverse dependency checks for `lhs` can be found [here](etc/revdep_README.md).

## Installation

You can install the released version of `lhs` from [CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("lhs")
```

You can also install the development version of `lhs` from here with:

``` r
# install.packages("devtools")
devtools::install_github("bertcarnell/lhs")
```

## Examples

Create a random LHS with 10 samples and 3 variables:

``` r
require(lhs)
set.seed(1776)
X <- randomLHS(n = 10, k = 3)
```

Create a design that is more optimal than the random case:

```r
A <- geneticLHS(10, 3, pop = 100, gen = 5, pMut = 0.1)
B <- maximinLHS(10, 3, method = "build", dup = 5)
D <- maximinLHS(10, 3, method = "iterative", optimize.on = "result", eps = 0.01, maxIter = 300)
E <- improvedLHS(10, 3, dup = 5)
G <- optimumLHS(10, 3, maxSweeps = 10, eps = 0.01)
```

```r
data.frame(method = c("random","genetic","maximin","maximin","improved","optimum"),
           mean_dist = c(mean(dist(X)), mean(dist(A)), mean(dist(B)),
                         mean(dist(D)), mean(dist(E)), mean(dist(G))),
           min_dist = c(min(dist(X)), min(dist(A)), min(dist(B)),
                        min(dist(D)), min(dist(E)), min(dist(G))))
```

|Method|Mean Distance|Minimum Distance|
|------|-------------|----------------|
|random | 0.7067224 | 0.2708864 |
|genetic | 0.7189860 | 0.4058587 |
|maximin | 0.7295788 | 0.3611274 |
|maximin | 0.7245922 | 0.3974934 |
|improved | 0.7028446 | 0.3871904 |
|optimum | 0.7289469 | 0.4597657 |

Augment an existing design:

```r
Y <- randomLHS(10, 5)
Z <- augmentLHS(Y, 2)
```

Build an orthogonal array LHS:

```r
# a 9 row design is returned because a 10 row design is not possible with these algorithms
W9 <- create_oalhs(10, 3, bChooseLargerDesign = FALSE, bverbose = FALSE)

# a 16 row design is returned because a 10 row design is not possible with these algorithms
W16 <- create_oalhs(10, 3, bChooseLargerDesign = TRUE, bverbose = FALSE)
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

StackExchange Examples:

- [Latin Hypercube around set points](https://stats.stackexchange.com/questions/370983/latin-hypercube-around-set-points)
- [Latin hypercube sampling with categorical variables](https://stats.stackexchange.com/questions/388963/latin-hypercube-sampling-with-categorical-variables)
- [Are Latin hypercube samples uncorrelated](https://stats.stackexchange.com/questions/147789/are-latin-hypercube-samples-uncorrelated)
- [Stopping rule for Latin hypercube sampling (LHS)](https://stats.stackexchange.com/questions/407262/stopping-rule-for-latin-hypercube-sampling-lhs)
- [Is a group of random hypercube samples equivalent to a single latin hypercube with more samples?](https://stats.stackexchange.com/questions/411085/is-a-group-of-random-hypercube-samples-equivalent-to-a-single-latin-hypercube-wi)
- [Taking samples of data using Latin Hypercube Sampling](https://stats.stackexchange.com/questions/439271/taking-samples-of-data-using-latin-hypercube-sampling)
- [Number of parameter sets generated by latin hyercube sampling](https://stats.stackexchange.com/questions/460918/number-of-parameter-sets-generated-by-latin-hyercube-sampling)
- [Is there a way to check if sample obeys the Latin Hypercube Sampling rule?](https://stats.stackexchange.com/questions/465492/is-there-a-way-to-check-if-sample-obeys-the-latin-hypercube-sampling-rule)
- [Effectiveness of Latin Hypercube Sampling](https://stats.stackexchange.com/questions/468202/effectiveness-of-latin-hypercube-sampling)
- [Dividing CDF rather than PDF equally in Latin Hypercube Sampling](https://stats.stackexchange.com/questions/468293/dividing-cdf-rather-than-pdf-equally-in-latin-hypercube-sampling)
- [Stratified sampling / QMC simulation for compound Poisson rv](https://stats.stackexchange.com/questions/469963/stratified-sampling-qmc-simulation-for-compound-poisson-rv)
- [Using Latin Hypercube Sampling with a condition that the sum of two variables should be less than one](https://stats.stackexchange.com/questions/474911/using-latin-hypercube-sampling-with-a-condition-that-the-sum-of-two-variables-sh)
- [How to generate a design for a response surface with a discrete input random variable?](https://stats.stackexchange.com/questions/444997/how-to-generate-a-design-for-a-response-surface-with-a-discrete-input-random-var)
- [Is it necessary to shuffle X coordinates in Latin hypercube Sampling?](https://stats.stackexchange.com/questions/498492/is-it-necessary-to-shuffle-x-coordinates-in-latin-hypercube-sampling-lhc)

## Other

lhs package announcement:  [R-pkgs New R-Packages: Triangle and LHS](http://r.789695.n4.nabble.com/R-pkgs-New-R-Packages-Triangle-and-LHS-tp803930.html)
