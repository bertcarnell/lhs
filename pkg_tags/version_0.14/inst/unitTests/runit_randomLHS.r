################################################################################
#
# Program Name:  runit_randomLHS.R
# Purpose:       To provide test functions for randomLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: randomLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.randomLHS <- function()
{
  checkException(randomLHS(10.1, 2), silent=TRUE)
  checkException(randomLHS(-1, 2), silent=TRUE)
  checkException(randomLHS(10, 2.5), silent=TRUE)
  checkException(randomLHS(10, -30), silent=TRUE)
  checkException(randomLHS(NA, 2), silent=TRUE)
  checkException(randomLHS(NaN, 2), silent=TRUE)
  checkException(randomLHS(Inf, 2), silent=TRUE)
  checkException(randomLHS(10, NA), silent=TRUE)
  checkException(randomLHS(10, NaN), silent=TRUE)
  checkException(randomLHS(10, Inf), silent=TRUE)

  A <- randomLHS(4,2)
  checkTrue(all(A > 0 & A < 1))
  checkTrue(checkLatinHypercube(A))

  checkException(randomLHS(10.1, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(-1, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, 2.5, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, -30, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(NA, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(NaN, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(Inf, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, NA, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, NaN, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, Inf, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, 10, preserveDraw=8), silent=TRUE)

  A <- randomLHS(4, 2, preserveDraw=TRUE)
  checkTrue(all(A > 0 & A < 1))
  checkTrue(checkLatinHypercube(A))

  set.seed(4)
  A <- randomLHS(5, 3, preserveDraw=TRUE)
  set.seed(4)
  B <- randomLHS(5, 5, preserveDraw=TRUE)
  checkEqualsNumeric(A, B[,1:3], tolerance=1E-6)
  checkTrue(checkLatinHypercube(A))
  checkTrue(checkLatinHypercube(B))
}


