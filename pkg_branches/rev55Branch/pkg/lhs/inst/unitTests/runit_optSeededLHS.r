################################################################################
#
# Program Name:  runit_optSeededLHS.R
# Purpose:       To provide test functions for optSeededLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: optSeededLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.optSeededLHS <- function()
{
  a <- matrix(c(0.6180257, 0.49711298,
    0.4351729, 0.89893706,
    0.1350518, 0.57555028,
    0.7858432, 0.04072546,
    0.1830144, 0.26001034,
    0.9439103, 0.76395668
    ), nrow=6, ncol=2, byrow=TRUE)
  b <- matrix(c(0.1383291, 0.1783548, 0.83049003,
    0.3419933, 0.4984879, 0.09815034,
    0.1971579, 0.9921542, 0.57375508,
    0.6827262, 0.7365888, 0.87107438,
    0.5045188, 0.0522494, 0.43593985,
    0.9836697, 0.5684597, 0.20014368
    ), nrow=6, ncol=3, byrow=TRUE)
  d <- c(
    0.996613897, 0.484630660, 0.266861663, 0.669602700, 0.513479382, 0.628102959, 0.495412583, 0.437709079,
    0.719244803, 0.317626305, 0.885710407, 0.786240186, 0.174220855, 0.092432279, 0.666634688, 0.832565101,
    0.241787113, 0.906217329, 0.098890415, 0.271876831, 0.551860859, 0.130397376, 0.462662571, 0.942768167,
    0.845221401, 0.149395456, 0.007741981, 0.591189585, 0.376615843, 0.204320178
    )

  checkException(optSeededLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, Inf), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, NA), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, NaN), silent=TRUE)
  checkException(optSeededLHS(randomLHS(10, 4), 2, 5, Inf), silent=TRUE)

  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- NA
    optSeededLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)

  f <- function()
  {
    temp <- randomLHS(10, 4)
    temp[1][1] <- 2
    optSeededLHS(temp, 5)
  }
  checkException(f(), silent=TRUE)

  # Can't use suppressMessages here since the messages come from Rprintf
  #   have to use capture.output...
  f <- function()
  {
    set.seed(1976)
    sTemp <- capture.output(rtemp <- optSeededLHS(randomLHS(4, 2), 2))
    rtemp
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
    sTemp <- capture.output(rtemp <- optSeededLHS(randomLHS(3, 3), 3, 3, .05))
    rtemp
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
    set.seed(1979)
    temp2 <- augmentLHS(randomLHS(10,2), 5)
    temp2 <- c(t(temp2))
    sTemp <- capture.output(
      rTemp <- .C("optSeededLHS_C", as.integer(15), as.integer(2),
         as.integer(3), as.double(0.1), as.double(temp2),
         as.integer(choose(15,2)+1), as.integer(TRUE))
    )
    rTemp[[5]]
  }
  if (!grepl("sun",R.version$platform) &&
      !grepl("sparc", R.version$platform) &&
      !grepl("solaris", R.version$platform))
  {
    checkEqualsNumeric(f(), d, tolerance=1E-7)
  }
}


