################################################################################
#
# Program Name:  runit_geneticLHS.R
# Purpose:       To provide test functions for geneticLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: geneticLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.geneticLHS <- function(){
  checkException(geneticLHS(10.1, 2), silent=TRUE)
  checkException(geneticLHS(-1, 2), silent=TRUE)
  checkException(geneticLHS(10, 2.5), silent=TRUE)
  checkException(geneticLHS(10, -30), silent=TRUE)
  checkException(geneticLHS(10, 2, 4.3), silent=TRUE)
  checkException(geneticLHS(10, 2, -2), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, -1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 1.5), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, -.1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, 1.1), silent=TRUE)
  checkException(geneticLHS(NA, 2), silent=TRUE)
  checkException(geneticLHS(NaN, 2), silent=TRUE)
  checkException(geneticLHS(Inf, 2), silent=TRUE)
  checkException(geneticLHS(10, NA), silent=TRUE)
  checkException(geneticLHS(10, NaN), silent=TRUE)
  checkException(geneticLHS(10, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, Inf), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    suppressMessages(geneticLHS(4, 2))
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    suppressMessages(geneticLHS(3, 3, 6))
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1978)
    suppressMessages(geneticLHS(5, 2, 6, 4, .5))
  }
  checkTrue(checkLatinHypercube(f()))
}
