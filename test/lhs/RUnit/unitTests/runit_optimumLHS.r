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
  a <- matrix(c(
    0.36802566, 0.1851729,
    0.63505177, 0.7858432,
    0.04072546, 0.6489371,
    0.82555028, 0.4971130
    ), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(
    0.4716624, 0.008659989, 0.9836697,
    0.1783548, 0.498487852, 0.3254876,
    0.8710744, 0.764817002, 0.5737551
    ), nrow=3, ncol=3, byrow=TRUE)

  g <- matrix(c(
    0.429337175, 0.1827792,
    0.815301533, 0.4926609,
    0.717167385, 0.9219567,
    0.273122603, 0.7318439,
    0.008915384, 0.2470201
    ), nrow=5, ncol=2, byrow=TRUE)

  d <- c(5, 5, 2, 7, 7, 1, 10, 3, 1, 4, 9, 9, 3, 2, 6, 8, 4, 10, 8, 6)

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
  
  f <- function()
  {
    set.seed(1976)
    sTemp <- capture.output(rTemp <- optimumLHS(4, 2))
    rTemp
  }
  checkEqualsNumeric(f(), a, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))
  
  f <- function()
  {
    set.seed(1977)
    sTemp <- capture.output(rTemp <- optimumLHS(3, 3, 5))
    rTemp
  }
  checkEqualsNumeric(f(), b, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1978)
    sTemp <- capture.output(rTemp <- optimumLHS(5, 2, 5, .5))
    rTemp
  }
  checkEqualsNumeric(f(), g, tolerance=1E-7)
  checkTrue(checkLatinHypercube(f()))

  f <- function()
  {
    set.seed(1979)
    temp <- matrix(0, nrow=10, ncol=2)
    for(j in 1:2)
    {
      temp[ ,j] <- order(runif(10))
    }
    temp <- c(t(temp))
    sTemp <- capture.output(
    rTemp <- .C("optimumLHS_C", as.integer(10), as.integer(2),
       as.integer(3), as.double(0.1), as.integer(temp),
       as.integer(choose(10,2)+1), as.integer(TRUE)))
    rTemp[[5]]
  }
  checkEqualsNumeric(f(), d, tolerance=1E-7)
}


