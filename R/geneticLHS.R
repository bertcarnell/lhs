# Copyright 2019 Robert Carnell

#' Latin Hypercube Sampling with a Genetic Algorithm
#'
#' Draws a Latin Hypercube Sample from a set of uniform distributions for use in
#' creating a Latin Hypercube Design.  This function attempts to optimize the
#' sample with respect to the S optimality criterion through a genetic type
#' algorithm.
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
#' Genetic Algorithm:
#' \enumerate{
#' \item Generate \code{pop} random latin hypercube designs of size \code{n} by \code{k}
#' \item Calculate the S optimality measure of each design
#' \item Keep the best design in the first position and throw away half of the rest of the population
#' \item Take a random column out of the best matrix and place it in a random column of each of the other matricies, and take a random column out of each of the other matricies and put it in copies of the best matrix thereby causing the progeny
#' \item For each of the progeny, cause a genetic mutation \code{pMut} percent of the time.  The mutation is accomplished by swtching two elements in a column
#' }
#'
#' @param n The number of partitions (simulations or design points or rows)
#' @param k The number of replications (variables or columns)
#' @param pop The number of designs in the initial population
#' @param gen The number of generations over which the algorithm is applied
#' @param pMut The probability with which a mutation occurs in a column of the progeny
#' @param criterium The optimality criterium of the algorithm.  Default is \code{S}.  \code{Maximin} is also supported
#' @param verbose Print informational messages.  Default is \code{FALSE}
#'
#' @return An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
#' @export
#' @references
#' Stocki, R. (2005) A method to improve design reliability using optimal Latin hypercube sampling
#' \emph{Computer Assisted Mechanics and Engineering Sciences} \bold{12}, 87--105.
#'
#' Stein, M.  (1987) Large Sample Properties of Simulations Using Latin Hypercube Sampling.
#' \emph{Technometrics}.  \bold{29}, 143--151.
#'
#' @seealso [randomLHS()], [improvedLHS()], [maximinLHS()],
#' and [optimumLHS()] to generate Latin Hypercube Samples.  [optAugmentLHS()]
#' [optSeededLHS()], and [augtmentLHS()]  to modify and augment existing designs.
#'
#' @keywords design
#' @author Rob Carnell
#'
#' @examples
#' set.seed(1234)
#' A <- geneticLHS(4, 3, 50, 5, .25)
geneticLHS <- function(n=10, k=2, pop=100, gen=4, pMut=.1, criterium="S", verbose=FALSE)
{
  .Call("geneticLHS_cpp", as.integer(n), as.integer(k), as.integer(pop), as.integer(gen),
        pMut, criterium, as.logical(verbose), PACKAGE = "lhs")
}
