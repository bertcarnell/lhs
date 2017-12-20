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
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1977)
    improvedLHS(3, 3, 5)
  }
  checkTrue(checkLatinHypercube(f()))
}


