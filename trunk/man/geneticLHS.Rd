\name{geneticLHS}
\alias{geneticLHS}
\title{Latin Hypercube Sampling with a Genetic Algorithm}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This function attempts to optimize the
sample with respect to the S optimality criterion through a genetic type
algorithm.
}
\usage{geneticLHS(n=10, k=2, pop=100, gen=4, pMut=.1)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{pop}{The number of designs in the initial population}
  \item{gen}{The number of generations over which the algorithm is applied}
  \item{pMut}{The probability with wich a mutation occurs in a column of the progeny}
}
\details{
Latin hypercube sampling (LHS) was developed to generate a distribution of
collections of parameter values from a multidimensional distribution.  A square
grid containing possible sample points is a Latin square iff there is only one
sample in each row and each column. A Latin hypercube is the generalisation of
this concept to an arbitrary number of dimensions.  When sampling a function of
k variables, the range of each variable is divided into n equally probable
intervals. n sample points are then drawn such that a Latin Hypercube is
created.  Latin Hypercube sampling generates more efficient estimates of
desired parameters than simple Monte Carlo sampling.

This program generates a Latin Hypercube Sample by creating random permutations
of the first n integers in each of k columns and then transforming those
integers into n sections of a standard uniform distribution.  Random values are
then sample from within each of the n sections.  Once the sample is generated,
the uniform sample from a column can be transformed to any distribution by
using the quantile functions, e.g. qnorm().  Different columns can have
different distributions.

S-optimality seeks to maximize the mean distance from each design point to all
the other points in the design, so the points are as spread out as possible.

Genetic Algorithm:
\enumerate{
  \item Generate pop random latin hypercube designs of size n by k
  \item Calculate the S optimality measure of each design
  \item Keep the best design in the first position and throw away half of the
    rest of the population
  \item Take a random column out of the best matrix and place it in a
    random column of each of the other matricies, and take a random column
    out of each of the other matricies and put it in copies of the best
    matrix thereby causing the progeny
  \item For each of the progeny, cause a genetic mutation pMut percent of the
    time by swtching two elements in each column
  }
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Stocki, Rafal. "A method to improve design reliability using optimal Latin hypercube sampling"
  Institute of Fundamental Technological Research, Polish Academy of Sciences,
  ul. Swietokrzyska 21, 00-049 Warsaw, Poland

  Iman, R.L., J.C. Helton, J.E. Campbell. 1981. An approach to sensitivity analysis of computer
  models, Part 1. Introduction, input variable selection and preliminary variable assessment. Journal
  of Quality Technology 13:174-183.
}
\author{Rob Carnell}
\seealso{
  \code{\link{randomLHS}},
  \code{\link{improvedLHS}}, \code{\link{maximinLHS}}, and
  \code{\link{optimumLHS}} to generate Latin Hypercube Samples.
  \code{\link{optAugmentLHS}}, \code{\link{optSeededLHS}}, and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  geneticLHS(4, 3, 50, 5, .25)
}
\keyword{design}
