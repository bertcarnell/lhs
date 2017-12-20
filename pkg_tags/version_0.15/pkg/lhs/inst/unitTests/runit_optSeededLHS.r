################################################################################
#
# Program Name:  runit_optSeededLHS.R
# Purpose:       To provide test functions for optSeededLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optSeededLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optSeededLHS <- function()
{
  checkException(optSeededLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, Inf), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, Inf), silent=TRUE)

  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- NA
    optSeededLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)

  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- 2
    optSeededLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)

  f <- function()
  {
    set.seed(1976)
    optSeededLHS(randomLHS(4, 2), 2)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    optSeededLHS(randomLHS(3, 3), 3, 3, .05)
  }
  checkTrue(checkLatinHypercube(f()))
}


