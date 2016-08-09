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
  a <- matrix(c(
    0.4137913, 0.004286313,
    0.5290463, 0.866422933,
    0.2091800, 0.523384498,
    0.9041168, 0.340987296
    ), nrow=4, ncol=2, byrow=TRUE)
  b <- matrix(c(
    0.9092260, 0.1063563, 0.5931998,
    0.3674236, 0.9118653, 0.2013260,
    0.1838634, 0.6143440, 0.6896409
    ), nrow=3, ncol=3, byrow=TRUE)
  d <- matrix(c(
    0.75663344, 0.1033584,
    0.84292532, 0.5872683,
    0.41514455, 0.9170010,
    0.01262253, 0.7645178,
    0.30541787, 0.3835217
    ), nrow=5, ncol=2, byrow=TRUE)

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
  
  f <- function()
  {
    set.seed(1976)
    suppressMessages(geneticLHS(4, 2))
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), a, tolerance=1E-7)
  }
  
  f <- function()
  {
    set.seed(1977)
    suppressMessages(geneticLHS(3, 3, 6))
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), b, tolerance=1E-7)
  }

  f <- function()
  {
    set.seed(1978)
    suppressMessages(geneticLHS(5, 2, 6, 4, .5))
  }
  checkTrue(checkLatinHypercube(f()))
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), d, tolerance=1E-7)
  }
}
