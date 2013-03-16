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

test.randomLHS <- function(){
  a <- matrix(c(0.07163446, 0.1449906, 0.53135074, 0.6487661, 0.48832575,
                0.2959244, 0.83849428, 0.9994098), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(0.5138222, 0.1538120, 0.8542834, 0.7515563, 0.9306291,
                0.2461012, 0.2022003, 0.4902523, 0.4670436),
                nrow=3, ncol=3, byrow=TRUE)

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
  checkEqualsNumeric({set.seed(1976); randomLHS(4, 2)}, a, tolerance=1E-7)
  checkEqualsNumeric({set.seed(1977); randomLHS(3, 3)}, b, tolerance=1E-7)
}


