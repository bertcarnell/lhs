# Copyright 2019 Robert Carnell

#' Optimal Augmented Latin Hypercube Sample
#'
#' Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.  This function attempts to
#' add the points to the design in an optimal way.
#'
#' Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.  This function attempts to
#' add the points to the design in a way that maximizes S optimality.
#'
#' S-optimality seeks to maximize the mean distance from each design point to all
#' the other points in the design, so the points are as spread out as possible.
#'
#' @param lhs The Latin Hypercube Design to which points are to be added
#' @param m The number of additional points to add to matrix \code{lhs}
#' @param mult \code{m*mult} random candidate points will be created.
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @keywords design
#' @seealso
#'   [randomLHS()], [geneticLHS()], [improvedLHS()], [maximinLHS()], and
#'   [optimumLHS()] to generate Latin Hypercube Samples.  [optSeededLHS()] and
#'   [augmentLHS()] to modify and augment existing designs.
#' @importFrom stats runif na.exclude na.omit
#'
#' @references
#'   Stein, M.  (1987) Large Sample Properties of Simulations Using Latin Hypercube Sampling.
#'   \emph{Technometrics}. \bold{29}, 143--151.
#'
#' @examples
#' a <- randomLHS(4,3)
#' a
#' optAugmentLHS(a, 2, 3)
optAugmentLHS <- function(lhs, m=1, mult=2)
{
  if (is.matrix(lhs) == FALSE)
    stop("Input Design must be in the Matrix class\n")
  if (length(m) != 1 | length(mult) != 1)
    stop("m and mult may not be vectors")
  if (is.na(m) | is.infinite(m))
    stop("m may not be infinite, NA, or NaN")
  if (is.na(mult) | is.infinite(mult))
    stop("mult may not be infinite, NA, or NaN")
  if (m != floor(m) | m < 1)
    stop("m must be a positive integer\n")
  if (any(is.na(lhs) == TRUE))
    stop("Input Design cannot contain any NA entries\n")
  if (any(lhs < 0 | lhs > 1))
    stop("Input Design must have entries on the interval [0,1]\n")

  K <- ncol(lhs)
  N <- nrow(lhs)

  colvec <- order(runif(K))
  rowvec <- order(runif(N + m))

  B <- matrix(nrow = (N + m), ncol = K)

  for (j in colvec) {
    newrow <- 0
    for (i in rowvec) {
      if ((any((i - 1)/(N + m) <= lhs[ ,j] & lhs[ ,j] <= i/(N + m))) == FALSE) {
        newrow <- newrow + 1
        B[newrow, j] <- runif(1, (i - 1)/(N + m), i/(N + m))
      }
    }
  }

  lhs <- rbind(lhs, matrix(nrow = m, ncol = K))

  for (k in 1:m) {

    P <- matrix(nrow = m*mult, ncol = K)
    for (i in 1:K) {
      P[,i] <- runifint(m*mult, 1, length(na.exclude(B[,i])))
    }
    for (i in 1:K) {
      for (j in 1:(m*mult)) {
        P[j, i] <- B[P[j, i], i]
      }
    }

    vec <- numeric(K)
    dist1 <- 0
    maxdist <- .Machine$double.xmin

    for (i in 1:(m*mult - k + 1)) {
      dist1 <- numeric(N + k - 1)
      for (j in 1:(N + k - 1)) {
        vec <- P[i,] - lhs[j,]
        dist1[j] <- vec %*% vec
        }
      if (sum(dist1) > maxdist) {
        maxdist <- sum(dist1)
        maxrow <- i
      }
    }

    lhs[N + k,] <- P[maxrow,]

    for (i in 1:K) {
      for (j in 1:length(na.omit(B[,i]))) {
        if (P[maxrow,i] == B[j,i]) B[j,i] <- NA
      }
    }
    for (i in 1:K) {
      if (length(na.omit(B[,i])) == 0)
        next
      u <- length(na.omit(B[,i]))
      B[1:u,i] <- na.omit(B[,i])
      B[(u + 1):m,i] <- NA
    }
  }

  return(lhs)
}
