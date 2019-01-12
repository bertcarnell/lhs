# Copyright 2019 Robert Carnell

#' Augment a Latin Hypercube Design
#'
#' Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.
#'
#' @details Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.  Augmentation is perfomed
#' in a random manner.
#'
#' The algorithm used by this function has the following steps.
#' First, create a new matrix to hold the candidate points after the design has
#' been re-partitioned into \eqn{(n+m)^{2}}{(n+m)^2} cells, where n is number of
#' points in the original \code{lhs} matrix.  Then randomly sweep through each
#' column (1\ldots\code{k}) in the repartitioned design to find the missing cells.
#' For each column (variable), randomly search for an empty row, generate a
#' random value that fits in that row, record the value in the new matrix.
#' The new matrix can contain more filled cells than \code{m} unles \eqn{m = 2n},
#' in which case the new matrix will contain exactly \code{m} filled cells.
#' Finally, keep only the first m rows of the new matrix.  It is guaranteed to
#' have \code{m} full rows in the new matrix.  The deleted rows are partially full.
#' The additional candidate points are selected randomly due to the random search
#' for empty cells.
#'
#' @param lhs The Latin Hypercube Design to which points are to be added.
#' Contains an existing latin hypercube design with a number of rows equal
#' to the points in the design (simulations) and a number of columns equal
#' to the number of variables (parameters).  The values of each cell must be
#' between 0 and 1 and uniformly distributed
#' @param m The number of additional points to add to matrix \code{lhs}
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values
#' uniformly distributed on [0,1]
#' @export
#'
#' @author Rob Carnell
#' @references
#' Stein, M.  (1987) Large Sample Properties of Simulations Using Latin
#' Hypercube Sampling. \emph{Technometrics}. \bold{29}, 143--151.
#'
#' @keywords design
#'
#' @seealso [randomLHS()], [geneticLHS()], [improvedLHS()], [maximinLHS()],
#' and [optimumLHS()] to generate Latin Hypercube Samples.  [optAugmentLHS()]
#' and [optSeededLHS()] to modify and augment existing designs.
#'
#' @examples
#' a <- randomLHS(4,3)
#' a
#' augmentLHS(a, 2)
augmentLHS <- function(lhs, m=1)
{
  if (!is.matrix(lhs))
    stop("Input Latin Hypercube Design must be in the Matrix class\n")
  if (length(m) != 1)
    stop("m may not be a vector")
  if (is.na(m) | is.infinite(m))
    stop("m may not be infinite, NA, or NaN")
  if (m != floor(m) | m < 1)
    stop("m must be a positive integer\n")
  if (any(is.na(lhs)))
    stop("Input Design cannot contain any NA entries\n")
  if (any(lhs < 0 | lhs > 1))
    stop(paste("Input Latin Hypercube Design must have entries on the ",
              "interval [0,1] which are uniformly distributed\n", sep = ""))

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

  if (is.matrix(B[1:m,])) {
    E <- rbind(lhs, B[1:m, ])
  } else E <- rbind(lhs, matrix(B[1:m,], nrow = m, ncol = K))
  row.names(E) <- NULL
  return(E)
}
