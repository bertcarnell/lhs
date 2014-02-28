################################################################################
#
# Program Name:  runit_augmentLHS.R
# Purpose:       To provide test functions for augmentLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: augmentLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.augmentLHS <- function()
{

  checkException(augmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), Inf), silent=TRUE)

  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- NA
    augmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- 2
    augmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  set.seed(1976)
  checkTrue(checkLatinHypercube(augmentLHS(randomLHS(4, 2), 4)))

  set.seed(1977)
  checkTrue(checkLatinHypercube(augmentLHS(randomLHS(3, 3), 3)))

  set.seed(1977)
  checkTrue(checkLatinHypercube(augmentLHS(randomLHS(4, 1), 2)))

  # this test addresses a bug where an error ocurred on adding 1 row in
  #   augmentLHS
  f <- function()
  {
    temp <- randomLHS(7, 2)
    temp <- augmentLHS(temp,1)
    nrow(temp)
  }
  checkEquals(f(), 8)
  checkLatinHypercube(augmentLHS(randomLHS(7, 2), 7))
  checkLatinHypercube(augmentLHS(randomLHS(10, 5), 10))
}


