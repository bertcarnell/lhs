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
  A <- randomLHS(4,2)
  checkTrue(all(A > 0 & A < 1))
  checkEquals(4, nrow(A))
  checkEquals(2, ncol(A))
  checkTrue(checkLatinHypercube(A))

  # doubles are truncated in n and k
  A <- randomLHS(4.4, 2)
  checkTrue(all(A > 0 & A < 1))
  checkEquals(4, nrow(A))
  checkEquals(2, ncol(A))
  checkTrue(checkLatinHypercube(A))
  
  A <- randomLHS(4, 2.8)
  checkTrue(all(A > 0 & A < 1))
  checkEquals(4, nrow(A))
  checkEquals(2, ncol(A))
  checkTrue(checkLatinHypercube(A))

  A <- randomLHS(4.4, 2.8)
  checkTrue(all(A > 0 & A < 1))
  checkEquals(4, nrow(A))
  checkEquals(2, ncol(A))
  checkTrue(checkLatinHypercube(A))

  checkException(randomLHS(-1, 2), silent=TRUE)
  checkException(randomLHS(10, -30), silent=TRUE)
  checkException(randomLHS(NA, 2), silent=TRUE)
  checkException(randomLHS(NaN, 2), silent=TRUE)
  suppressWarnings(checkException(randomLHS(Inf, 2), silent=TRUE)) # error and warning NAs introduced by coercion
  checkException(randomLHS(10, NA), silent=TRUE)
  checkException(randomLHS(10, NaN), silent=TRUE)
  suppressWarnings(checkException(randomLHS(10, Inf), silent=TRUE)) # error and warning

  A <- randomLHS(1, 5)
  checkEquals(1, nrow(A))
  checkEquals(5, ncol(A))
  checkTrue(all(A == 1))

  checkException(randomLHS(c(1,2,3), c(3,4)), silent=TRUE)

  checkException(randomLHS(-1, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, -30, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(NA, 2, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(NaN, 2, preserveDraw=TRUE), silent=TRUE)
  suppressWarnings(checkException(randomLHS(Inf, 2, preserveDraw=TRUE), silent=TRUE)) # error and warning
  checkException(randomLHS(10, NA, preserveDraw=TRUE), silent=TRUE)
  checkException(randomLHS(10, NaN, preserveDraw=TRUE), silent=TRUE)
  suppressWarnings(checkException(randomLHS(10, Inf, preserveDraw=TRUE), silent=TRUE)) # error and warning

  A <- randomLHS(4, 2, preserveDraw=TRUE)
  checkTrue(all(A > 0 & A < 1))
  checkTrue(checkLatinHypercube(A))

  set.seed(4)
  A <- randomLHS(5, 3, preserveDraw=TRUE)
  set.seed(4)
  B <- randomLHS(5, 5, preserveDraw=TRUE)
  checkEqualsNumeric(A, B[,1:3], tolerance=1E-12)
  checkTrue(checkLatinHypercube(A))
  checkTrue(checkLatinHypercube(B))
}


