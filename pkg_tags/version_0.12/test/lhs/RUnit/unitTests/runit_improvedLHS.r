################################################################################
#
# Program Name:  runit_ImprovedLHS.R
# Purpose:       To provide test functions for improvedLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: improvedLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.improvedLHS <- function(){
  a <- matrix(c(
    0.07555028, 0.2306772,
    0.49711298, 0.5012294,
    0.52791861, 0.9600331,
    0.92798023, 0.3731828
    ), nrow=4, ncol=2, byrow=TRUE)

  b <- matrix(c(
    0.2825281, 0.7544882, 0.0980865,
    0.8011583, 0.2411404, 0.4773251,
    0.5437211, 0.3497079, 0.8586682
    ), nrow=3, ncol=3, byrow=TRUE)

  d <- c(
    5, 10, 3, 8, 1, 9, 6, 7, 4, 2, 2, 6, 3, 1, 10, 4, 5, 8, 9, 7
    )

  checkException(improvedLHS(10.1, 2), silent=TRUE)
  checkException(improvedLHS(-1, 2), silent=TRUE)
  checkException(improvedLHS(10, 2.5), silent=TRUE)
  checkException(improvedLHS(10, -30), silent=TRUE)
  checkException(improvedLHS(10, 2, 4.3), silent=TRUE)
  checkException(improvedLHS(10, 2, -2), silent=TRUE)
  checkException(improvedLHS(NA, 2), silent=TRUE)
  checkException(improvedLHS(NaN, 2), silent=TRUE)
  checkException(improvedLHS(Inf, 2), silent=TRUE)
  checkException(improvedLHS(10, NA, 2), silent=TRUE)
  checkException(improvedLHS(10, NaN, 2), silent=TRUE)
  checkException(improvedLHS(10, Inf, 2), silent=TRUE)
  checkException(improvedLHS(10, 2, NA), silent=TRUE)
  checkException(improvedLHS(10, 2, NaN), silent=TRUE)
  checkException(improvedLHS(10, 2, Inf), silent=TRUE)
  
  f <- function()
  {
    set.seed(1976)
    improvedLHS(4, 2)
  }
  #checkEqualsNumeric(f(), a, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    improvedLHS(3, 3, 5)
  }
  #checkEqualsNumeric(f(), b, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1978)
    .C("improvedLHS_C", as.integer(10), as.integer(2),
      as.integer(3), integer(2*10))[[4]]
  }
  #checkEqualsNumeric(f(), d, tolerance=1E-7)
}


