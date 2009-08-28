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

test.optSeededLHS <- function(){
  a <- matrix(c(#0.6180257, 0.49711298,
#0.4351729, 0.89893706,
#0.1350518, 0.57555028,
#0.7858432, 0.04072546,
#0.1830144, 0.26001034,
#0.9439103, 0.76395668
0.07163446, 0.2959244,
0.31597518, 0.6487661,
0.48832575, 0.9994098,
0.53135074, 0.1449906,
0.83849428, 0.3749384,
0.79180969, 0.7589378
), nrow=6, ncol=2, byrow=TRUE)
  b <- matrix(c(#0.1383291, 0.1783548, 0.83049003,
#0.3419933, 0.4984879, 0.09815034,
#0.1971579, 0.9921542, 0.57375508,
#0.6827262, 0.7365888, 0.87107438,
#0.5045188, 0.0522494, 0.43593985,
#0.9836697, 0.5684597, 0.20014368
0.5138222, 0.1538120, 0.85428343,
0.7515563, 0.9306291, 0.24610117,
0.1023604, 0.2140764, 0.46704364,
0.2022003, 0.7480675, 0.50013043,
0.4914100, 0.4902523, 0.03091406,
0.8472311, 0.5447051, 0.76678826
),
                nrow=6, ncol=3, byrow=TRUE)
d <- c(
0.10396151, 0.25958653, 0.36637122, 0.55781742, 0.59808034, 0.19197323,
0.81697611, 0.45096428, 0.21899433, 0.06628890, 0.64052217, 0.62843514,
0.43680777, 0.32830041, 0.05163994, 0.79218112, 0.95639112, 0.34103569,
0.50864628, 0.83801189, 0.87577930, 0.71317637, 0.29662090, 0.88617093,
0.71675304, 0.97693675, 0.13718823, 0.53249899, 0.78255706, 0.09290869
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
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- NA
                  optSeededLHS(temp, 5)
                  }, silent=TRUE)
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- 2
                  optSeededLHS(temp, 5)
                  }, silent=TRUE)
  checkEqualsNumeric({
                      set.seed(1976)
                      sTemp <- capture.output(rtemp <- optSeededLHS(randomLHS(4, 2), 2))
                      rtemp
                      }, a, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      sTemp <- capture.output(rtemp <- optSeededLHS(randomLHS(3, 3), 3, 3, .05))
                      rtemp
                      }, b, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1979)
                      temp2 <- augmentLHS(randomLHS(10,2), 5)
                      temp2 <- c(t(temp2))
                      sTemp <- capture.output(
                      rTemp <- .C("optSeededLHS_C", as.integer(15), as.integer(2),
                         as.integer(3), as.double(0.1), as.double(temp2),
                         double(choose(15,2)+1), integer(choose(15,2)+1),
                         integer(choose(15,2)+1), as.integer(choose(15,2)+1),
                         double(2*15)))
                      rTemp[[5]]
                      }, d, tolerance=1E-7)
}


