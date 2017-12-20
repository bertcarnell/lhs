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

test.augmentLHS <- function(){
  checkException(augmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), Inf), silent=TRUE)
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- NA
    augmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1,1] <- 2
    augmentLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    augmentLHS(randomLHS(4, 2), 4)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    augmentLHS(randomLHS(3, 3), 3)
  }
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    augmentLHS(randomLHS(4, 1), 2)
  }
  checkTrue(checkLatinHypercube(f()))

  # this test addresses a bug where an error ocurred on adding 1 row in
  #   augmentLHS
  temp <- randomLHS(7, 2)
  temp <- augmentLHS(temp,1)
  checkEquals(nrow(temp), 8L)

  # this test addresses a bug submitted on 8/8/2016
  A <- matrix(c(0.0625000,0.3750000,0.9166667,0.5208333,0.7500000,0.2083333,
                0.04166667,0.66666667,0.37500000,0.97916667,0.52083333,0.27083333), 
              nrow=6, ncol=2)
  checkTrue(all(!is.na(augmentLHS(A, m=10))))
}


