# Copyright 2019 Robert Carnell

#' Maximin Latin Hypercube Sample
#'
#' Draws a Latin Hypercube Sample from a set of uniform distributions for use in
#' creating a Latin Hypercube Design.  This function attempts to optimize the
#' sample by maximizing the minium distance between design points (maximin criteria).
#'
#' @details Latin hypercube sampling (LHS) was developed to generate a distribution
#' of collections of parameter values from a multidimensional distribution.
#' A square grid containing possible sample points is a Latin square iff there
#' is only one sample in each row and each column. A Latin hypercube is the
#' generalisation of this concept to an arbitrary number of dimensions.  When
#' sampling a function of \code{k} variables, the range of each variable is divided
#' into \code{n} equally probable intervals. \code{n} sample points are then drawn such that a
#' Latin Hypercube is created.  Latin Hypercube sampling generates more efficient
#' estimates of desired parameters than simple Monte Carlo sampling.
#'
#' This program generates a Latin Hypercube Sample by creating random permutations
#' of the first \code{n} integers in each of \code{k} columns and then transforming those
#' integers into n sections of a standard uniform distribution.  Random values are
#' then sampled from within each of the n sections.  Once the sample is generated,
#' the uniform sample from a column can be transformed to any distribution by
#' using the quantile functions, e.g. qnorm().  Different columns can have
#' different distributions.
#'
#' Here, values are added to the design one by one such that the maximin criteria is
#' satisfied.
#'
#' @param n The number of partitions (simulations or design points or rows)
#' @param k The number of replications (variables or columns)
#' @param method \code{build} or \code{iterative} is the method of LHS creation.
#' \code{build} finds the next best point while constructing the LHS.
#' \code{iterative} optimizes the resulting sample on [0,1] or sample grid on [1,N]
#' @param dup A factor that determines the number of candidate points used in the
#' search. A multiple of the number of remaining points than can be
#' added.  This is used when \code{method="build"}
#' @param eps The minimum percent change in the minimum distance used in the
#' \code{iterative} method
#' @param maxIter The maximum number of iterations to use in the \code{iterative} method
#' @param optimize.on \code{grid} or \code{result} gives the basis of the optimization.
#' \code{grid} optimizes the LHS on the underlying integer grid.
#' \code{result} optimizes the resulting sample on [0,1]
#' @param debug prints additional information about the process of the optimization
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @keywords design
#' @importFrom stats dist
#'
#' @references
#'   Stein, M.  (1987) Large Sample Properties of Simulations Using Latin Hypercube Sampling.
#'   \emph{Technometrics}.  \bold{29}, 143--151.
#'
#'   This function is motivated by the MATLAB program written by John Burkardt and modified 16 Feb 2005
#'   \url{http://www.csit.fsu.edu/~burkardt/m_src/ihs/ihs.m}
#'
#' @seealso [randomLHS()], [geneticLHS()], [improvedLHS()] and [optimumLHS()]
#' to generate Latin Hypercube Samples.  [optAugmentLHS()], [optSeededLHS()], and
#' [augmentLHS()] to modify and augment existing designs.
#'
#' @examples
#' maximinLHS(4, 3, dup=2)
#' maximinLHS(4, 3, method="build", dup=2)
#' maximinLHS(4, 3, method="iterative", eps=0.05, maxIter=100, optimize.on="grid")
#' maximinLHS(4, 3, method="iterative", eps=0.05, maxIter=100, optimize.on="result")
maximinLHS <- function(n, k, method="build", dup=1, eps=0.05, maxIter=100,
                       optimize.on="grid", debug=FALSE)
{
  if (!(method %in% c("build","iterative")))
    stop("Method not recognized.  Please use 'build' or 'iterative'")
  if (!(optimize.on %in% c("grid","result")))
    stop("optimize.on parameter must be 'result' or 'grid'")
  if (debug)
    cat("Debug info:\n")

  if (method == "build")
  {
    if (optimize.on == "result")
    {
      if (debug) cat(paste0("\toptimize.on=", optimize.on, "  method=", method, "\n"))
      warning("when method='build' then optimize.on is set to 'grid'")
    }

    result <- .Call("maximinLHS_cpp", as.integer(n), as.integer(k), as.integer(dup),
                    PACKAGE = "lhs")
    return(result)

  } else if (method == "iterative")
  {
    if (length(n) != 1 | length(k) != 1 | length(dup) != 1)
      stop("n, k, and dup may not be vectors")
    if (any(is.na(c(n,k,dup)))) stop("n, k, and dup may not be NA or NaN")
    if (any(is.infinite(c(n,k,dup)))) stop("n, k, and dup may not be infinite")
    if (n != floor(n) | n < 1) stop("n must be a positive integer")
    if (k != floor(k) | k < 1) stop("k must be a positive integer")
    if (dup != floor(dup) | dup < 1)
      stop("The dup factor must be a positive integer")
    adjust <- runif(n*k)

    if (optimize.on == "result")
    {
      X <- randomLHS(n, k, preserveDraw = FALSE)
    } else if (optimize.on == "grid")
    {
      X <- sapply(1:k, function(x) order(runif(n)))
    }
    Y <- X
    minDist <- min(dist(X))
    # the columns of res are the ith row, mth row, jth column, and the min distance when those are exchanged
    res <- matrix(0, nrow = k*choose(n, 2), ncol = 4)
    iter <- 1
    while (iter < maxIter)
    {
      # counter is the counter down the rows of res
      counter <- 1
      # try all pairwise row swaps within each column in the LHS
      for (j in 1:k)
      {
        for (i in 1:(n - 1))
        {
          for (m in (i + 1):n)
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
        if (debug)
          cat("\tstopped because no changes improved minimum distance\n")
        if (optimize.on == "result")
          return(X)
        else
          return((X - 1 + matrix(adjust, nrow = n, ncol = k))/n)
      }
      if (res[ind,4] < (1 + eps)*minDist)
      {
        if (debug)
          cat("\tstopped because the minimum improvement was not reached\n")
        if (optimize.on == "result")
          return(Y)
        else
          return((Y - 1 + matrix(adjust, nrow = n, ncol = k))/n)
      } else
      {
        minDist <- temp
        X <- Y
      }
      iter <- iter + 1
    }
    if (debug)
      cat("\tstoped on iterations\n")
    if (optimize.on == "result")
      return(Y)
    else
      return((Y - 1 + matrix(adjust, nrow = n, ncol = k))/n)
  }
}
