################################################################################
#
# Program Name:  runit_optAugmentLHS.R
# Purpose:       To provide test functions for optAugmentLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optAugmentLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optAugmentLHS <- function(){
  a <- matrix(c(
    0.6180257, 0.04072546,
    0.4351729, 0.89893706,
    0.1350518, 0.57555028,
    0.7858432, 0.49711298,
    0.9439103, 0.76395668,
    0.1830144, 0.26001034
    ), nrow=6, ncol=2, byrow=TRUE)
  b <- matrix(c(
    0.1383291, 0.1783548, 0.87107438,
    0.3419933, 0.4984879, 0.09815034,
    0.9836697, 0.9921542, 0.57375508,
    0.6827262, 0.0522494, 0.83049003,
    0.5045188, 0.7365888, 0.20014368,
    0.1971579, 0.5684597, 0.43593985
    ), nrow=6, ncol=3, byrow=TRUE)

  checkException(optAugmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, Inf), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- NA
    optAugmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- 2
    optAugmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    optAugmentLHS(randomLHS(4, 2), 2)
  }
  checkEqualsNumeric(f(), a, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))
  
  f <- function()
  {
    set.seed(1977)
    optAugmentLHS(randomLHS(3, 3), 3, 3)
  }
  checkEqualsNumeric(f(), b, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))
}


