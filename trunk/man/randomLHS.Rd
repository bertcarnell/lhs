\name{randomLHS}
\alias{randomLHS}
\alias{latin}
\alias{hypercube}
\title{Random Latin Hypercube}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This sample is take is taken in a random
manner without regard to optimization
}
\usage{randomLHS(n, k)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
}
\details{
Latin hypercube sampling (LHS) was developed to generate a distribution
of collections of parameter values from a multidimensional distribution.
A square grid containing possible sample points is a Latin square iff there
is only one sample in each row and each column. A Latin hypercube is the
generalisation of this concept to an arbitrary number of dimensions.  When
sampling a function of k variables, the range of each variable is divided
into n equally probable intervals. n sample points are then drawn such that a
Latin Hypercube is created.  Latin Hypercube sampling generates more efficient
estimates of desired parameters than simple Monte Carlo sampling.

This program generates a Latin Hypercube Sample by creating random permutations
of the first n integers in each of k columns and then transforming those
integers into n sections of a standard uniform distribution.  Random values are
then sample from within each of the n sections.  Once the sample is generated,
the uniform sample from a column can be transformed to any distribution by
using the quantile functions, e.g. qnorm().  Different columns can have
different distributions.
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Becker, R. A., Chambers, J. M. and Wilks, A. R. (1988)
  \emph{The New S Language}.
  Wadsworth \& Brooks/Cole.

  Iman, R.L., J.C. Helton, J.E. Campbell. 1981. An approach to sensitivity analysis of computer
  models, Part 1. Introduction, input variable selection and preliminary variable assessment. Journal
  of Quality Technology 13:174-183.
}
\author{Rob Carnell and D. Mooney}
\seealso{
  \code{\link{geneticLHS}},
  \code{\link{improvedLHS}}, \code{\link{maximinLHS}}, and
  \code{\link{optimumLHS}} to generate Latin Hypercube Samples.
  \code{\link{optAugmentLHS}}, \code{\link{optSeededLHS}}, and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  randomLHS(4, 3)
}
\keyword{design}
