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
  a <- matrix(c(
    0.61802566, 0.04072546,
    0.43517287, 0.89893706,
    0.13505177, 0.57555028,
    0.78584321, 0.49711298,
    0.69500775, 0.71004887,
    0.94796751, 0.13730839,
    0.36447982, 0.77853392,
    0.03875566, 0.33133683
    ), nrow=8, ncol=2, byrow=TRUE)
  b <- matrix(c(
    0.1383291, 0.1783548, 0.87107438,
    0.3419933, 0.4984879, 0.09815034,
    0.9836697, 0.9921542, 0.57375508,
    0.6827262, 0.0522494, 0.83049003,
    0.5045188, 0.7365888, 0.43593985,
    0.1971579, 0.5684597, 0.20014368
    ), nrow=6, ncol=3, byrow=TRUE)
  d <- matrix(c(
    0.8563343,
    0.2321231,
    0.3426021,
    0.6052802,
    0.1022039,
    0.7157418
    ), nrow=6, ncol=1)

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
  
  f <- function()
  {
    set.seed(1976)
    augmentLHS(randomLHS(4, 2), 4)
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), a, tolerance=1E-7)
  }

  f <- function()
  {
    set.seed(1977)
    augmentLHS(randomLHS(3, 3), 3)
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), b, tolerance=1E-7)
  }

  f <- function()
  {
    set.seed(1977)
    augmentLHS(randomLHS(4, 1), 2)
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), d, tolerance=1E-7)
  }

  # this test addresses a bug where an error ocurred on adding 1 row in
  #   augmentLHS
  f <- function()
  {
    temp <- randomLHS(7, 2)
    temp <- augmentLHS(temp,1)
    nrow(temp)
  }
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEquals(f(), 8)
  }
  
  # this test addresses a bug submitted on 8/8/2016
  A <- matrix(c(0.0625000,0.3750000,0.9166667,0.5208333,0.7500000,0.2083333,
                0.04166667,0.66666667,0.37500000,0.97916667,0.52083333,0.27083333), 
              nrow=6, ncol=2)
  checkTrue(all(!is.na(augmentLHS(A, m=10))))

}


