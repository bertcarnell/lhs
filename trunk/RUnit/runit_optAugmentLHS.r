################################################################################
#
# Program Name:  runit_optAugmentLHS.R
# Purpose:       To provide test functions for optAugmentLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optAugmentLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optAugmentLHS <- function(){
  a <- matrix(c(0.07163446, 0.1449906, 0.53135074, 0.6487661, 0.48832575,
                0.2959244, 0.83849428, 0.9994098, 0.79180969, 0.3749384,
                0.31597518, 0.7589378), nrow=6, ncol=2, byrow=TRUE)
  b <- matrix(c(0.5138222, 0.1538120, 0.85428343,
                0.7515563, 0.9306291, 0.24610117,
                0.2022003, 0.4902523, 0.46704364,
                0.8472311, 0.2140764, 0.03091406,
                0.1023604, 0.5447051, 0.76678826,
                0.4914100, 0.7480675, 0.50013043),
                nrow=6, ncol=3, byrow=TRUE)

  checkException(optAugmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NA), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, NaN), silent=TRUE)
  checkException(optAugmentLHS(randomLHS(10, 4), 2, Inf), silent=TRUE)
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- NA
                  optAugmentLHS(temp, 5)
                  }, silent=TRUE)
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- 2
                  optAugmentLHS(temp, 5)
                  }, silent=TRUE)
  checkEqualsNumeric({
                      set.seed(1976)
                      optAugmentLHS(randomLHS(4, 2), 2)
                      }, a, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      optAugmentLHS(randomLHS(3, 3), 3, 3)
                      }, b, tolerance=1E-7)
}


