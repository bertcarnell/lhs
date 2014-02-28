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

test.geneticLHS <- function()
{
  checkException(geneticLHS(-1, 2), silent=TRUE)
  checkException(geneticLHS(10, -30), silent=TRUE)
  checkException(geneticLHS(10, 2, -2), silent=TRUE)
  checkException(geneticLHS(NA, 2), silent=TRUE)
  checkException(geneticLHS(NaN, 2), silent=TRUE)
  suppressWarnings(checkException(geneticLHS(Inf, 2), silent=TRUE))
  checkException(geneticLHS(10, NA), silent=TRUE)
  checkException(geneticLHS(10, NaN), silent=TRUE)
  suppressWarnings(checkException(geneticLHS(10, Inf), silent=TRUE))
  checkException(geneticLHS(10, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, NaN), silent=TRUE)
  suppressWarnings(checkException(geneticLHS(10, 2, Inf), silent=TRUE))
  
  set.seed(1976)
  checkTrue(checkLatinHypercube(geneticLHS(4, 2)))
  
  set.seed(1977)
  checkTrue(checkLatinHypercube(geneticLHS(3, 3, 6)))
  
  checkException(geneticLHS(10, 2, 4, -1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, -.1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, 1.1), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NaN), silent=TRUE)
  suppressWarnings(checkException(geneticLHS(10, 2, 2, Inf), silent=TRUE))

  #checkException(geneticLHS(10, 2, 2, 4, NA), silent=TRUE)
  #checkException(geneticLHS(10, 2, 2, 4, NaN), silent=TRUE)

  checkException(geneticLHS(10, 2, 2, 4, Inf), silent=TRUE)
}


