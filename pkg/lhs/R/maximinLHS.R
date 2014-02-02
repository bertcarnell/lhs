################################################################################
#
# Function: maximinLHS.R
# Purpose:  To create an optimum Latin Hypercube Sampling algorithm that is
#           implements the maximin criteria.  The maximin critera attemps to
#           maximize the minimum distance between points
# Author:   Rob Carnell
#           This program is motivated by the MATLAB program written by
#           John Burkardt
# Created:  May 05
#
# Discussion:
#    n Points in an k dimensional Latin hypercube are to be selected.
#    This algorithm tries to pick a solution which has the property that the
#    points are S optimal.
#    It uses the dup (DUPLICATION) factor to limit the number of points available
#    to choose from at each step.
#
#  Parameters:
#    k= positive integer, the spatial dimension.
#    n= positive integer, the number of points to be generated.
#    dup= positive integer, the DUPLICATION factor.
#      (default=1, a value of 5 is reasonable)
#
#  Steps
#   1.  Select a random starting point and place it in the matrix X
#   2.  Populate the matrix AVAIL with the integers from 1 to n
#   3.  Replace the values in AVAIL which have already been used by the
#       the first point in X with the value N
#   4.  Generate the valid points for each row in a random manner by using
#       the numbers in the rows of AVAIL
#   5.  For each cadidate point, calculate the distance to the points already
#       used in X.  Select the candidate point with the maximum minimum distance
#       value and place it in X (actually squared distance is used to eliminate
#       the square root processing step)
#   7.  Having chosen the new point for X, update AVAIL to replace those
#       numbers in each row that have been used.  The first "count" columns in
#       AVAIL are valid points.
#   8.  There is only one choice for the last point
#
# 6/30/2012
#   Changed the C function call
#
################################################################################

maximinLHS <- function(n, k, dup=1)
{
  result <- .Call("maximinLHS_cpp", as.integer(n), as.integer(k), as.integer(dup))

  return(result)
}

