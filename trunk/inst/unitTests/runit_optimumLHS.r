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

test.optimumLHS <- function(){
  a <- matrix(c(0.8216345, 0.53135074, 0.7383257, 0.08849428, 0.1449906,
                0.39876608, 0.2959244, 0.99940985), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(0.5138222, 0.08488965, 0.8688670, 0.8204786, 0.93062914,
                0.1569190, 0.1876168, 0.57943451, 0.4670436),
                nrow=3, ncol=3, byrow=TRUE)
  f <- matrix(c(0.9944108, 0.7442834, 0.4341714, 0.9317972, 0.1953845,
                0.5770278, 0.7979830, 0.3255536, 0.2571826, 0.1873088),
                nrow=5, ncol=2, byrow=TRUE)

  d <- c(7, 3, 4, 7, 6, 9, 9, 5, 3, 2, 2, 6, 1, 10, 10, 8, 5, 4, 8, 1)

  checkException(optimumLHS(10.1, 2), silent=TRUE)
  checkException(optimumLHS(-1, 2), silent=TRUE)
  checkException(optimumLHS(10, 2.5), silent=TRUE)
  checkException(optimumLHS(10, -30), silent=TRUE)
  checkException(optimumLHS(10, 2, 4.3), silent=TRUE)
  checkException(optimumLHS(10, 2, -2), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, -1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1.5), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 1), silent=TRUE)
  checkException(optimumLHS(10, 2, 3, 0), silent=TRUE)
  checkException(optimumLHS(NA, 2), silent=TRUE)
  checkException(optimumLHS(NaN, 2), silent=TRUE)
  checkException(optimumLHS(Inf, 2), silent=TRUE)
  checkException(optimumLHS(10, NA), silent=TRUE)
  checkException(optimumLHS(10, NaN), silent=TRUE)
  checkException(optimumLHS(10, Inf), silent=TRUE)
  checkException(optimumLHS(10, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, NaN), silent=TRUE)
  checkException(optimumLHS(10, 2, Inf), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, NA), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, NaN), silent=TRUE)
  checkException(optimumLHS(10, 2, 2, Inf), silent=TRUE)
  checkEqualsNumeric({
                      set.seed(1976)
                      sTemp <- capture.output(rTemp <- optimumLHS(4, 2))
                      rTemp
                      }, a, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      sTemp <- capture.output(rTemp <- optimumLHS(3, 3, 5))
                      rTemp
                      }, b, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1978)
                      sTemp <- capture.output(rTemp <- optimumLHS(5, 2, 5, .5))
                      rTemp
                      }, f, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1979)
                      temp <- matrix(0, nrow=10, ncol=2)
                      for(j in 1:2) {
                        temp[ ,j] <- order(runif(10))
                      }
                      temp <- c(t(temp))
                      sTemp <- capture.output(
                      rTemp <- .C("optimumLHS_C", as.integer(10), as.integer(2),
                         as.integer(3), as.double(0.1), as.integer(temp),
                         double(choose(10,2)+1), integer(choose(10,2)+1),
                         integer(choose(10,2)+1), as.integer(choose(10,2)+1),
                         integer(2*10)))
                      rTemp[[5]]
                      }, d, tolerance=1E-7)
}


