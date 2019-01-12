# Copyright 2019 Robert Carnell

#' Optimum Seeded Latin Hypercube Sample
#'
#' Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.  This function then uses the
#' columnwise pairwise (\acronym{CP}) algoritm to optimize the design.  The original design is not necessarily maintained.
#'
#' @details
#' Augments an existing Latin Hypercube Sample, adding points to the design, while
#' maintaining the \emph{latin} properties of the design.  This function then uses the
#' \acronym{CP} algoritm to optimize the design.  The original design
#' is not necessarily maintained.
#'
#' @param seed The number of partitions (simulations or design points)
#' @param m The number of additional points to add to the seed matrix \code{seed}.  default value is zero.  If m is zero then the seed design is optimized.
#' @param maxSweeps The maximum number of times the CP algorithm is applied to all the columns.
#' @param eps The optimal stopping criterion
#' @param verbose Print informational messages
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @seealso   [randomLHS()], [geneticLHS()], [improvedLHS()], [maximinLHS()], and
#' [optimumLHS()] to generate Latin Hypercube Samples.  [optAugmentLHS()] and
#' [augmentLHS()] to modify and augment existing designs.
#' @keywords design
#'
#' @references
#'   Stein, M.  (1987) Large Sample Properties of Simulations Using Latin Hypercube Sampling.
#'   \emph{Technometrics}. \bold{29}, 143--151.
#'
#' @examples
#'   a <- randomLHS(4,3)
#'   a
#'   optSeededLHS(a, 2, 2, .1)
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

  result <- .Call("optSeededLHS_cpp", as.integer(N), as.integer(k),
                  as.integer(maxSweeps), eps, Pold, as.logical(verbose),
                  PACKAGE = "lhs")

  return(result)
}
