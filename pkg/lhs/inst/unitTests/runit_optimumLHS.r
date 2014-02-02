################################################################################
#
# Program Name:  runit_optimumLHS.R
# Purpose:       To provide test functions for optimumLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optimumLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optimumLHS <- function()
{
  checkException(optimumLHS(-1, 2), silent=TRUE)
  checkException(optimumLHS(10, -30), silent=TRUE)
  checkException(optimumLHS(10, 2, -2), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, -1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1.5), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 0), silent=TRUE)
  checkException(optimumLHS(NA, 2), silent=TRUE)
  checkException(optimumLHS(NaN, 2), silent=TRUE)
  suppressWarnings(checkException(optimumLHS(Inf, 2), silent=TRUE))
  checkException(optimumLHS(10, NA), silent=TRUE)
  checkException(optimumLHS(10, NaN), silent=TRUE)
  suppressWarnings(checkException(optimumLHS(10, Inf), silent=TRUE))
  checkException(optimumLHS(10, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, NaN), silent=TRUE)
  suppressWarnings(checkException(optimumLHS(10, 2, Inf), silent=TRUE))
  checkException(optimumLHS(10, 2, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, NaN), silent=TRUE)
  suppressWarnings(checkException(optimumLHS(10, 2, 2, Inf), silent=TRUE))

  set.seed(1976)
  rTemp <- optimumLHS(4, 2)
  checkTrue(checkLatinHypercube(rTemp))
  
  set.seed(1977)
  rTemp <- optimumLHS(3, 3, 5)
  checkTrue(checkLatinHypercube(rTemp))

  set.seed(1978)
  rTemp <- optimumLHS(5, 2, 5, .5)
  checkTrue(checkLatinHypercube(rTemp))
  
  set.seed(2010)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j)
      checkTrue(checkLatinHypercube(A))
    }
  }
  set.seed(2011)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j, 5)
      checkTrue(checkLatinHypercube(A))
    }
  }
  set.seed(2012)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j, 5, 0.05)
      checkTrue(checkLatinHypercube(A))
    }
  }
  
}


