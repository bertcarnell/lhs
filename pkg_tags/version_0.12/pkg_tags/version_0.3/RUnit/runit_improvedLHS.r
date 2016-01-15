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
  a <- matrix(c(0.79592441, 0.1431093, 0.74940985, 0.6248918, 0.41694528,
                0.8659861, 0.09153965, 0.4520949), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(0.07222432, 0.8658036, 0.1136544, 0.65092346, 0.1791829,
                0.3870314, 0.88729741, 0.5094480, 0.8063272),
                nrow=3, ncol=3, byrow=TRUE)
  d <- c(1, 10, 5, 2, 6, 9, 3, 4, 7, 8, 4, 10, 7, 1, 9, 8, 6, 3, 2, 5)



  checkException(improvedLHS(10.1, 2), silent=TRUE)
  checkException(improvedLHS(-1, 2), silent=TRUE)
  checkException(improvedLHS(10, 2.5), silent=TRUE)
  checkException(improvedLHS(10, -30), silent=TRUE)
  checkException(improvedLHS(10, 2, 4.3), silent=TRUE)
  checkException(improvedLHS(10, 2, -2), silent=TRUE)
  checkException(randomLHS(NA, 2), silent=TRUE)
  checkException(randomLHS(NaN, 2), silent=TRUE)
  checkException(randomLHS(Inf, 2), silent=TRUE)
  checkException(randomLHS(10, NA, 2), silent=TRUE)
  checkException(randomLHS(10, NaN, 2), silent=TRUE)
  checkException(randomLHS(10, Inf, 2), silent=TRUE)
  checkException(randomLHS(10, 2, NA), silent=TRUE)
  checkException(randomLHS(10, 2, NaN), silent=TRUE)
  checkException(randomLHS(10, 2, Inf), silent=TRUE)
  checkEqualsNumeric({set.seed(1976); improvedLHS(4, 2)}, a, tolerance=1E-7)
  checkEqualsNumeric({set.seed(1977); improvedLHS(3, 3, 5)}, b, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1978)
                      .C("improvedLHS_C", as.integer(10), as.integer(2),
                      as.integer(3), integer(2*10), integer(2*10),
                      integer(2*3*(10-1)), integer(3*(10-1)), integer(2))[[4]]
                      }, d, tolerance=1E-7)
}


