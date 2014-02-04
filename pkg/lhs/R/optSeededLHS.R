################################################################################
#
# Function: optSeededLHS.R
# Purpose:  To create a nearly optimal latin hypercube design with respect to
#           the S optimality criterion using the Columnwise-pairwise (CP)
#           Algorithm using input seed design
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables:
#   seed is the input Seed design.  The input seed must have the correct number
#      of variables and must be on the interval [0,1]
#   m is the number of addtional points to augment the design with
#      (default=1, must be a positive integer)
#   maxSweeps is the maximum number of times the CP algorithm is applied to all
#     the columns.
#   eps is the optimal stopping criterion (explained later)
#
# Reference:
#   This code was motivated by the work of Rafal Stocki
#   "A method to improve design reliability using optimal Latin hypercube
#    sampling" Institute of Fundamental Technological Research, Polish
#    Academy of Sciences, ul. Swietokrzyska 21, 00-049 Warsaw, Poland
#
# Required functions: ranperm.R, augmentlhd.R
#
# Explanation:
#  S optimality seeks to maximize the inverse of the sum of the distances
#  from each point in the design to all other points
# Algorithm:  generate a random latin hypercube design by augmenting the seed
#  design.
#  within each column of that matrix, interchange two numbers.
#  At each step, calculate the inverse of the sum of the distances between all
#  points, and pick modification which minimizes the distances.
#  Continue to move from column to column until the stopping criterion is
#  reached.  Either the maximum number of sweeps through the matrix is reached,
#  or the interchanges in a given row have no benefit to the S optimality, or
#  the decrease in the inverse of the sum of the distances is small compared to
#  the first decrease due to the interchange in the first column (ratio set by
#  eps)
#
# Run Time and computer resources:  Stocki asserts that processing time
#   increases proportional to k^5 for constant n and n^5 for constant k
#
# The dist function calculates the distance between each row of a matrix
#   and places the answer in a k*k half diagonal matrix
#
# 6/30/2012
#   Changed the C function call.  Added the verbose argument.
#
################################################################################

optSeededLHS <- function(seed, m=0, maxSweeps=2, eps=.1, verbose=FALSE)
{
  k <- ncol(seed)
  if (m == 0)
  {
    N <- nrow(seed)
    Pold <- seed
  }
  else
  {
    N <- m + nrow(seed)

    Pold <- augmentLHS(seed, m)
  }
  
  result <- .Call("optSeededLHS_cpp", as.integer(N), as.integer(k), as.integer(maxSweeps), eps, Pold, as.logical(verbose))

  return(result)
}
