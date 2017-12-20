################################################################################
#
# Program Name:  runit_maximinLHS.R
# Purpose:       To provide test functions for maximinLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: maximinLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.maximinLHS <- function(){
  checkException(maximinLHS(10.1, 2), silent=TRUE)
  checkException(maximinLHS(-1, 2), silent=TRUE)
  checkException(maximinLHS(10, 2.5), silent=TRUE)
  checkException(maximinLHS(10, -30), silent=TRUE)
  checkException(maximinLHS(10, 2, 4.3), silent=TRUE)
  checkException(maximinLHS(10, 2, -2), silent=TRUE)
  checkException(maximinLHS(NA, 2), silent=TRUE)
  checkException(maximinLHS(NaN, 2), silent=TRUE)
  checkException(maximinLHS(Inf, 2), silent=TRUE)
  checkException(maximinLHS(10, NA), silent=TRUE)
  checkException(maximinLHS(10, NaN), silent=TRUE)
  checkException(maximinLHS(10, Inf), silent=TRUE)
  checkException(maximinLHS(10, 2, NA), silent=TRUE)
  checkException(maximinLHS(10, 2, NaN), silent=TRUE)
  checkException(maximinLHS(10, 2, Inf), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    maximinLHS(4, 2)
  }
  checkTrue(checkLatinHypercube(f()))
  
  f <- function()
  {
    set.seed(1977)
    maximinLHS(3, 3, dup=5)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    maximinLHS(3, 5, method="iterative", optimize.on="grid")
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    maximinLHS(3, 10, method="iterative", optimize.on="result")
  }
  checkTrue(checkLatinHypercube(f()))
}

