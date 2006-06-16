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
################################################################################

optSeededLHS <- function(seed, m=1, maxSweeps=2, eps=.1)
{
  if(is.matrix(seed)==FALSE)
    stop("Input seed Design must be in the Matrix class\n")
  if(length(m)!=1 | length(maxSweeps)!=1 |length(eps)!=1)
    stop("m, eps, and maxSweeps may not be vectors")
  if(any(is.na(c(m,maxSweeps,eps))))
    stop("m, eps, and maxSweeps may not be NA or NaN")
  if(any(is.infinite(c(m,eps,maxSweeps))))
    stop("m, eps, and maxSweeps may not be infinite")
  if(eps>=1 | eps<=0) stop("eps must fall in the interval (0,1)\n")
  if(floor(maxSweeps)!=maxSweeps | maxSweeps<1)
    stop("maxSweeps must be a positive integer\n")
  if(floor(m)!=m | m<1) stop("m must be a positive integer\n")
  if(try(is.function(augmentLHS), silent=TRUE)!=TRUE)
    stop("The augmentLHS.R function must be sourced\n")
  if(any(is.na(seed)==TRUE))
    stop("Input Design cannot contain any NA entries\n")
  if(max(seed)>1 | min(seed)<0)
    stop("The seed design must be uniformly distributed on [0,1]\n")

  k <- ncol(seed)
  n <- m + nrow(seed)

  Pold <- augmentLHS(seed, m)
  
  if(m==1) return(Pold)

  Pold <- c(t(Pold)) # changes to an n*k length vector

  jLen <- choose(n, 2) + 1
  J1 <- numeric(jLen)
  J2 <- numeric(jLen)
  J3 <- numeric(jLen)
  Pnew <- numeric(n*k)

  resultList <- .C("optSeededLHS_C", as.integer(n), as.integer(k),
                     as.integer(maxSweeps), as.double(eps), as.double(Pold),
                     as.double(J1), as.integer(J2), as.integer(J3),
                     as.integer(jLen), as.double(Pnew))

  result <- resultList[[5]]

  return(matrix(result, nrow=n, ncol=k, byrow=TRUE))
}
