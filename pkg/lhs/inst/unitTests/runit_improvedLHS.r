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

test.improvedLHS <- function()
{
  checkException(improvedLHS(-1, 2), silent=TRUE)
  checkException(improvedLHS(10, -30), silent=TRUE)
  checkException(improvedLHS(10, 2, -2), silent=TRUE)
  checkException(improvedLHS(NA, 2), silent=TRUE)
  checkException(improvedLHS(NaN, 2), silent=TRUE)
  suppressWarnings(checkException(improvedLHS(Inf, 2), silent=TRUE))
  checkException(improvedLHS(10, NA, 2), silent=TRUE)
  checkException(improvedLHS(10, NaN, 2), silent=TRUE)
  suppressWarnings(checkException(improvedLHS(10, Inf, 2), silent=TRUE))
  checkException(improvedLHS(10, 2, NA), silent=TRUE)
  checkException(improvedLHS(10, 2, NaN), silent=TRUE)
  suppressWarnings(checkException(improvedLHS(10, 2, Inf), silent=TRUE))
  
  set.seed(1976)
  checkTrue(checkLatinHypercube(improvedLHS(4, 2)))

  set.seed(1977)
  checkTrue(checkLatinHypercube(improvedLHS(3, 3, 5)))
  
  set.seed(1111)
  A <- improvedLHS(20, 6)
  set.seed(1111)
  B <- improvedLHS(20, 6)
  checkTrue(all(A == B))
  D <- improvedLHS(20, 6)
  checkTrue(any(A != D))
}
