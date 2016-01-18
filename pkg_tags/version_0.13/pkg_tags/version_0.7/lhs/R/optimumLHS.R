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
################################################################################

optimumLHS <- function(n=10, k=2, maxSweeps=2, eps=.1)
{
  if(length(n)!=1 |length(k)!=1 | length(maxSweeps)!=1 |length(eps)!=1)
    stop("n, k, eps, and maxSweeps may not be vectors")
  if(any(is.na(c(n,k,maxSweeps,eps))))
    stop("n, k, eps, and maxSweeps may not be NA or NaN")
  if(any(is.infinite(c(n,k,eps,maxSweeps))))
    stop("n, k, eps, and maxSweeps may not be infinite")
  if(eps>=1 | eps<=0) stop("eps must fall in the interval (0,1)\n")
  if(floor(maxSweeps)!=maxSweeps | maxSweeps<1)
    stop("maxSweeps must be a positive integer\n")
  if(floor(n)!=n | n<1) stop("n must be a positive integer\n")
  if(floor(k)!=k | k<1) stop("k must be a positive integer\n")

  Pold <- matrix(0, nrow=n, ncol=k)
  for(j in 1:k) {
    Pold[ ,j] <- order(runif(n))
  }
  Pold <- c(t(Pold)) # changes to an n*k length vector

  if(n==1) {
    message("Design is already optimal\n")
    return(matrix(Pold, nrow=n, ncol=k, byrow=TRUE))
  }

  jLen <- choose(n, 2) + 1
  J1 <- numeric(jLen)
  J2 <- numeric(jLen)
  J3 <- numeric(jLen)
  Pnew <- numeric(n*k)

  resultList <- .C("optimumLHS_C", as.integer(n), as.integer(k),
                     as.integer(maxSweeps), as.double(eps), as.integer(Pold),
                     as.double(J1), as.integer(J2), as.integer(J3),
                     as.integer(jLen), as.integer(Pnew))

  result <- resultList[[5]]

  z <- runif(n*k)

  result <- (result - 1 + z) / n

  return(matrix(result, nrow=n, ncol=k, byrow=TRUE))
}
