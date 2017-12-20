################################################################################
#
# Program Name:  runit_optimumLHS.R
# Purpose:       To provide test functions for optimumLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optimumLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optimumLHS <- function()
{
  checkException(optimumLHS(10.1, 2), silent=TRUE)
  checkException(optimumLHS(-1, 2), silent=TRUE)
  checkException(optimumLHS(10, 2.5), silent=TRUE)
  checkException(optimumLHS(10, -30), silent=TRUE)
  checkException(optimumLHS(10, 2, 4.3), silent=TRUE)
  checkException(optimumLHS(10, 2, -2), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, -1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1.5), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 0), silent=TRUE)
  checkException(optimumLHS(NA, 2), silent=TRUE)
  checkException(optimumLHS(NaN, 2), silent=TRUE)
  checkException(optimumLHS(Inf, 2), silent=TRUE)
  checkException(optimumLHS(10, NA), silent=TRUE)
  checkException(optimumLHS(10, NaN), silent=TRUE)
  checkException(optimumLHS(10, Inf), silent=TRUE)
  checkException(optimumLHS(10, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, NaN), silent=TRUE)
  checkException(optimumLHS(10, 2, Inf), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, NaN), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, Inf), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    optimumLHS(4, 2)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    rTemp <- optimumLHS(3, 3, 5)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1978)
    rTemp <- optimumLHS(5, 2, 5, .5)
    rTemp
  }
  checkTrue(checkLatinHypercube(f()))
}


