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
  checkException(optAugmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, Inf), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- NA
    optAugmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- 2
    optAugmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    optAugmentLHS(randomLHS(4, 2), 2)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    optAugmentLHS(randomLHS(3, 3), 3, 3)
  }
  checkTrue(checkLatinHypercube(f()))
}


