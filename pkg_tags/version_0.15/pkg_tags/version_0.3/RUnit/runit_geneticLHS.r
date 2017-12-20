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

test.geneticLHS <- function(){
  a <- matrix(c(0.3462578, 0.1823516, 0.5145790, 0.9282432, 0.9128999,
                0.2713718, 0.2219954, 0.6256428), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(0.58555300, 0.3212979, 0.8961190, 0.72281982, 0.9449718,
                0.3572891, 0.03827732, 0.5074375, 0.2484802),
                nrow=3, ncol=3, byrow=TRUE)
  f <- matrix(c(0.1344930, 0.6663035, 0.4644433, 0.9991624, 0.9921650,
                0.4117803, 0.7134739, 0.1992269, 0.3106196, 0.3502558),
                nrow=5, ncol=2, byrow=TRUE)

  checkException(geneticLHS(10.1, 2), silent=TRUE)
  checkException(geneticLHS(-1, 2), silent=TRUE)
  checkException(geneticLHS(10, 2.5), silent=TRUE)
  checkException(geneticLHS(10, -30), silent=TRUE)
  checkException(geneticLHS(10, 2, 4.3), silent=TRUE)
  checkException(geneticLHS(10, 2, -2), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, -1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 1.5), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, -.1), silent=TRUE)
  checkException(geneticLHS(10, 2, 4, 4, 1.1), silent=TRUE)
  checkException(geneticLHS(NA, 2), silent=TRUE)
  checkException(geneticLHS(NaN, 2), silent=TRUE)
  checkException(geneticLHS(Inf, 2), silent=TRUE)
  checkException(geneticLHS(10, NA), silent=TRUE)
  checkException(geneticLHS(10, NaN), silent=TRUE)
  checkException(geneticLHS(10, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, Inf), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, NA), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, NaN), silent=TRUE)
  checkException(geneticLHS(10, 2, 2, 4, Inf), silent=TRUE)
  checkEqualsNumeric({
                      set.seed(1976)
                      suppressMessages(geneticLHS(4, 2))
                      }, a, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      suppressMessages(geneticLHS(3, 3, 6))
                      }, b, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1978)
                      suppressMessages(geneticLHS(5, 2, 6, 4, .5))
                      }, f, tolerance=1E-7)
}


