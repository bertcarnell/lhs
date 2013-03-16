################################################################################
#
# Program Name:  runit_augmentLHS.R
# Purpose:       To provide test functions for augmentLHS.R
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Functions: augmentLHS.R
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
################################################################################

test.augmentLHS <- function(){
  a <- matrix(c(0.07163446, 0.14499056, 0.53135074, 0.64876608, 0.48832575,
                0.29592441, 0.83849428, 0.99940985, 0.29827461, 0.86198138,
                0.14511656, 0.09385727, 0.90492208, 0.60563377, 0.64519659,
                0.44126189), nrow=8, ncol=2, byrow=TRUE)
  b <- matrix(c(0.5138222, 0.1538120, 0.85428343, 0.7515563, 0.9306291,
                0.24610117, 0.2022003, 0.4902523, 0.46704364, 0.4914100,
                0.7480675, 0.76678826, 0.1023604, 0.2140764, 0.03091406,
                0.8472311, 0.5447051, 0.50013043),
                nrow=6, ncol=3, byrow=TRUE)
  d <- matrix(c(0.9611208, 0.4325798, 0.6336407, 0.1508501, 0.2604750,
                0.7897173), nrow=6, ncol=1)

  checkException(augmentLHS(randomLHS(10, 4), NA), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), NaN), silent=TRUE)
  checkException(augmentLHS(randomLHS(10, 4), Inf), silent=TRUE)
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- NA
                  augmentLHS(temp, 5)
                  }, silent=TRUE)
  checkException({
                  temp <- randomLHS(10, 4)
                  temp[1][1] <- 2
                  augmentLHS(temp, 5)
                  }, silent=TRUE)
  checkEqualsNumeric({
                      set.seed(1976)
                      augmentLHS(randomLHS(4, 2), 4)
                      }, a, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      augmentLHS(randomLHS(3, 3), 3)
                      }, b, tolerance=1E-7)
  checkEqualsNumeric({
                      set.seed(1977)
                      augmentLHS(randomLHS(4, 1), 2)
                      }, d, tolerance=1E-7)
  # this test addresses a bug where an error ocurred on adding 1 row in
  #   augmentLHS
  checkEquals({temp <- randomLHS(7, 2)
             temp <- augmentLHS(temp,1)
             nrow(temp)}, 8)
}


