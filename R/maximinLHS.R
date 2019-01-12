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
#' @param dup A factor that determines the number of candidate points used in the
#' search. A multiple of the number of remaining points than can be added.
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @keywords design
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
#' maximinLHS(4, 3, 2)
maximinLHS <- function(n, k, dup=1)
{
  result <- .Call("maximinLHS_cpp", as.integer(n), as.integer(k), as.integer(dup))

  return(result)
}

