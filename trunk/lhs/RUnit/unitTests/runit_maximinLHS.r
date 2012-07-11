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
  a <- matrix(c(
    0.07555028, 0.2306772,
    0.49711298, 0.5012294,
    0.52791861, 0.9600331,
    0.92798023, 0.3731828
    ), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(
    0.2825281, 0.08782156, 0.4314198,
    0.8011583, 0.90780705, 0.1439918,
    0.5437211, 0.34970794, 0.8586682
    ), nrow=3, ncol=3, byrow=TRUE)
  d <- c(
    7, 1, 9, 3, 8, 4, 6, 10, 5, 2, 8, 2, 6, 4, 9, 10, 5, 3, 1, 7
    )

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
#  checkEqualsNumeric(f(), a, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))
  
  f <- function()
  {
    set.seed(1977)
    maximinLHS(3, 3, 5)
  }
#  checkEqualsNumeric(f(), b, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1978)
    .C("maximinLHS_C", as.integer(10), as.integer(2),
      as.integer(3), integer(2*10))[[4]]
  }
#  checkEqualsNumeric(f(), d, tolerance=1E-7)
}

