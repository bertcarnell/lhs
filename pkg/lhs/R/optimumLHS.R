################################################################################
#
# Function: optimumlhd.R
# Purpose:  To create a nearly optimal latin hypercube design with respect to
#           the S optimality criterion using the Columnwise-pairwise (CP)
#           Algorithm
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables:
#   n is the number of partitions (simulations or design points)
#   k is the number of replication (variables)
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
# Explanation:
#  S optimality seeks to maximize the inverse of the sum of the distances
#  from each point in the design to all other points
#  Algorithm:  generate a random latin hypercube design of size n by k
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
#   increases proportional to K^5 for constant N and N^5 for constant K
#
# 6/30/2012
#   Changed C function call.  Added verbose parameter.
#
################################################################################

optimumLHS <- function(n=10, k=2, maxSweeps=2, eps=.1, verbose=FALSE)
{
  result <- .Call("optimumLHS_cpp", as.integer(n), as.integer(k), as.integer(maxSweeps), eps, as.logical(verbose))

  return(result)
}
