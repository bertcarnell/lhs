################################################################################
#
# Function: improvedLHS.R
# Purpose:  To implement the Improved distributed Hypercube Sampling Algorithm
# Author:   This program is based on the MATLAB program written by
#             John Burkardt and modified 16 Feb 2005
#             http://www.csit.fsu.edu/~burkardt/m_src/ihs/
#             ihs.m
# R and C code Author:  Rob Carnell
# Created:  May 05
#
# Required C function:  improvedLHS_R.c
#
# Discussion:
#    N Points in an K dimensional Latin hypercube are to be selected.
#    This algorithm tries to pick a solution which has the property that the
#    points are "spread out" as evenly as possible.
#    It does this by determining an optimal even spacing given by OPT
#    It uses the DUPLICATION factor to limit the number of points available
#    to choose from at each step.
#
#  Reference:
#    Brian Beachkofski, Ramana Grandhi,
#    Improved Distributed Hypercube Sampling,
#    American Institute of Aeronautics and Astronautics Paper 2002-1274.
#
#  Parameters:
#    k= positive integer, the spatial dimension.
#    n= positive integer, the number of points to be generated.
#    dup= positive integer, the DUPLICATION factor.
#      (default=1, a value of 5 is reasonable according to Burkardt
#
#  Returns:
#    A Latin Hypercube sample with N rows and K columns where each entry
#    is on the interval [0,1]
#
#  Steps
#   1.  Calculate the optimum spacing interval
#   2.  Select a random starting point and place it in the matrix X
#   3.  Populate the matrix AVAIL with the integers from 1 to N
#   4.  Replace the values in AVAIL which have already been used by the
#       the first point in X with the value N
#   5.  Generate the valid points for each row in a random manner by using
#       the numbers in the rows of AVAIL
#   6.  For each cadidate point, calculate the distance to the points already
#       used in X.  Select the candidate point with the distance value
#       closest to the value of OPT and place it in X
#   7.  Having chosen the new point for X, update AVAIL to replace those
#       numbers in each row that have been used.  The first few columns in
#       AVAIL are valid points.
#   8.  There is only one choice for the last point
#
################################################################################

improvedLHS <- function(n, k, dup=1){
  if(length(n)!=1 |length(k)!=1 | length(dup)!=1)
    stop("n, k, and dup may not be vectors")
  if(any(is.na(c(n,k,dup)))) stop("n, k, and dup may not be NA or NaN")
  if(any(is.infinite(c(n,k,dup)))) stop("n, k, and dup may not be infinite")
  if(n!=floor(n) | n<1) stop("n must be a positive integer\n")
  if(k!=floor(k) | k<1) stop("k must be a positive integer\n")
  if(dup!=floor(dup) | dup<1)
    stop("The DUPLICATION (dup) factor must be a positive integer\n")

  result <- numeric(k*n)
  avail <- numeric(k*n)
  point1 <- numeric(k*(dup*(n-1)))
  list1 <- numeric(dup*(n-1))
  vec <- numeric(k)

  result2 <- .C("improvedLHS_C", as.integer(n), as.integer(k), as.integer(dup),
                as.integer(result), as.integer(avail), as.integer(point1),
                as.integer(list1), as.integer(vec))[[4]]

  eps <- runif(n*k)

  result2 <- (result2 - 1 + eps) / n

  return(t(matrix(result2, nrow=k, ncol=n, byrow=TRUE)))
}

