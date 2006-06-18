\name{maximinLHS}
\alias{maximinLHS}
\title{Maximin Latin Hypercube Sample}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This function attempts to optimize the
sample by maximizing the minium distance between design points (maximin criteria)
}
\usage{maximinLHS(n, k, dup=1)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{dup}{A factor that determines the number of candidate points used in the
             search. A multiple of the number of remaining points than can be
             added.}
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

Here, values are added to the design such that the maximin criteria is
satisfied.
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Iman, R.L., J.C. Helton, J.E. Campbell. 1981. An approach to sensitivity analysis of computer
  models, Part 1. Introduction, input variable selection and preliminary variable assessment. Journal
  of Quality Technology 13:174-183.

  This program is based on the MATLAB program written by
  John Burkardt and modified 16 Feb 2005
  \url{http://www.csit.fsu.edu/~burkardt/m_src/ihs/ihs.m}
}
\author{Rob Carnell}
\seealso{
  \code{\link{randomLHS}}, \code{\link{geneticLHS}},
  \code{\link{improvedLHS}} and
  \code{\link{optimumLHS}} to generate Latin Hypercube Samples.
  \code{\link{optAugmentLHS}}, \code{\link{optSeededLHS}}, and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  maximinLHS(4, 3, 2)
}
\keyword{design}
