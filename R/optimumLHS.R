# Copyright 2019 Robert Carnell

#' Optimum Latin Hypercube Sample
#'
#' Draws a Latin Hypercube Sample from a set of uniform distributions for use in
#' creating a Latin Hypercube Design.  This function uses the Columnwise
#' Pairwise (\acronym{CP}) algorithm to generate an optimal design with respect to the S
#' optimality criterion.
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
#' S-optimality seeks to maximize the mean distance from each design point to all
#' the other points in the design, so the points are as spread out as possible.
#'
#' This function uses the \acronym{CP} algorithm to generate an optimal
#' design with respect to the S optimality criterion.
#'
#' @param n The number of partitions (simulations or design points or rows)
#' @param k The number of replications (variables or columns)
#' @param maxSweeps The maximum number of times the CP algorithm is applied to all the columns.
#' @param eps The optimal stopping criterion.  Algorithm stops when the change in
#' optimality measure is less than eps*100\% of the previous value.
#' @param verbose Print informational messages
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @seealso   [randomLHS()], [geneticLHS()], [improvedLHS()] and [maximinLHS()]
#' to generate Latin Hypercube Samples.  [optAugmentLHS()], [optSeededLHS()], and
#' [augmentLHS()] to modify and augment existing designs.
#' @keywords design
#'
#' @references
#'   Stocki, R. (2005) A method to improve design reliability using optimal Latin hypercube sampling
#'   \emph{Computer Assisted Mechanics and Engineering Sciences} \bold{12}, 87--105.
#'
#' @examples
#' optimumLHS(4, 3, 5, .05)
optimumLHS <- function(n=10, k=2, maxSweeps=2, eps=.1, verbose=FALSE)
{
  result <- .Call("optimumLHS_cpp", as.integer(n), as.integer(k),
                  as.integer(maxSweeps), eps, as.logical(verbose),
                  PACKAGE = "lhs")

  return(result)
}
