################################################################################
#
# Function: maximinLHS.R
# Purpose:  To create an optimum Latin Hypercube Sampling algorithm that 
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
#  Steps for the "optimal" lhs building process
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
# 10/23/2016
#   Prototyped a new function call for maximinLHS which operates on the lhs 
#     grid or lhs result
#
################################################################################

maximinLHS <- function(n, k, method="build", dup=1, eps=0.05, maxIter=100, 
                       optimize.on="grid", debug=FALSE)
{
  if (length(n) != 1 | length(k) != 1 | length(dup) != 1)
    stop("n, k, and dup may not be vectors")
  if (any(is.na(c(n,k,dup)))) stop("n, k, and dup may not be NA or NaN")
  if (any(is.infinite(c(n,k,dup)))) stop("n, k, and dup may not be infinite")
  if (n != floor(n) | n < 1) stop("n must be a positive integer")
  if (k != floor(k) | k < 1) stop("k must be a positive integer")
  if (dup != floor(dup) | dup < 1)
    stop("The dup factor must be a positive integer")
  if (!(method %in% c("build","iterative")))
    stop("Method not recognized.  Please use 'build' or 'iterative'")
  if (!(optimize.on %in% c("grid","result")))
    stop("optimize.on parameter must be 'result' or 'grid'")
  if (debug)
    cat("Debug info:\n")

  adjust <- runif(n*k)
  if (method == "build")
  {
    if (optimize.on == "result")
    {
      if (debug) cat(paste0("\toptimize.on=", optimize.on, "  method=", method, "\n"))
      warning("when method='build' then optimize.on is set to 'grid'")
    }
      
    result <- numeric(k*n)
    result2 <- .C(C_maximinLHS_C, as.integer(n), as.integer(k), as.integer(dup),
                  as.integer(result))[[4]]
    result2 <- (result2 - 1 + adjust) / n
    return(matrix(result2, nrow=n, ncol=k, byrow=TRUE))
  } else if (method == "iterative")
  {
    if (optimize.on == "result")
    {
      X <- randomLHS(n, k, preserveDraw=FALSE)
    } else if (optimize.on == "grid")
    {
      X <- sapply(1:k, function(x) order(runif(n)))
    } else
    {
      if (debug) cat(paste0("\toptimize.on=", optimize.on, "  method=", method, "\n"))
      stop("optimize.on parameter must be 'result' or 'grid'")
    }
    Y <- X
    minDist <- min(dist(X))
    # the columns of res are the ith row, mth row, jth column, and the min distance when those are exchanged
    res <- matrix(0, nrow=k*choose(n, 2), ncol=4)
    iter <- 1
    while (iter < maxIter)
    {
      # counter is the counter down the rows of res
      counter <- 1
      # try all pairwise row swaps within each column in the LHS 
      for (j in 1:k)
      {
        for (i in 1:(n-1))
        {
          for (m in (i+1):n)
          {
            # swap
            Y[i,j] <- X[m,j]
            Y[m,j] <- X[i,j]
            # record the result
            res[counter,1] <- i
            res[counter,2] <- m
            res[counter,3] <- j
            res[counter,4] <- min(dist(Y))
            # swap back
            Y[i,j] <- X[i,j]
            Y[m,j] <- X[m,j]
            counter <- counter + 1
          }
        }
      }
      # find the best swap
      ind <- which.max(res[,4])
      # make the swap
      Y[res[ind,1],res[ind,3]] <- X[res[ind,2],res[ind,3]]
      Y[res[ind,2],res[ind,3]] <- X[res[ind,1],res[ind,3]]
      temp <- min(dist(Y))
      # test the new minimum distance between points
      if (temp < minDist)
      {
        if (debug) cat("\tstopped because no changes improved minimum distance\n")
        if (optimize.on == "result") return(X) else return((X - 1 + matrix(adjust, nrow = n, ncol = k))/n)
      } 
      if (res[ind,4] < (1+eps)*minDist)
      {
        if (debug) cat("\tstopped because the minimum improvement was not reached\n")
        if (optimize.on == "result") return(Y) else return((Y - 1 + matrix(adjust, nrow = n, ncol = k))/n)
      } else
      {
        minDist <- temp
        X <- Y
      }
      iter <- iter + 1
    }
    if (debug) cat("\tstoped on iterations\n")
    if (optimize.on == "result") return(Y) else return((Y - 1 + matrix(adjust, nrow = n, ncol = k))/n)
  }
}
