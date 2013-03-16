\name{optimumLHS}
\alias{optimumLHS}
\title{Optimum Latin Hypercube Sample}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This function uses the Columnwise
Pairwise (\acronym{CP}) algorithm to generate an optimal design with respect to the S
optimality criterion.
}
\usage{optimumLHS(n=10, k=2, maxSweeps=2, eps=.1, verbose=FALSE)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{maxSweeps}{The maximum number of times the CP algorithm is applied to all the columns.}
  \item{eps}{The optimal stopping criterion}
  \item{verbose}{Print informational messages}
}
\details{
Latin hypercube sampling (LHS) was developed to generate a distribution
of collections of parameter values from a multidimensional distribution.
A square grid containing possible sample points is a Latin square iff there
is only one sample in each row and each column. A Latin hypercube is the
generalisation of this concept to an arbitrary number of dimensions.  When
sampling a function of \code{k} variables, the range of each variable is divided
into \code{n} equally probable intervals. \code{n} sample points are then drawn such that a
Latin Hypercube is created.  Latin Hypercube sampling generates more efficient
estimates of desired parameters than simple Monte Carlo sampling.

This program generates a Latin Hypercube Sample by creating random permutations
of the first \code{n} integers in each of \code{k} columns and then transforming those
integers into n sections of a standard uniform distribution.  Random values are
then sampled from within each of the n sections.  Once the sample is generated,
the uniform sample from a column can be transformed to any distribution by
using the quantile functions, e.g. qnorm().  Different columns can have
different distributions.

S-optimality seeks to maximize the mean distance from each design point to all
the other points in the design, so the points are as spread out as possible.

This function uses the \acronym{CP} algorithm to generate an optimal
design with respect to the S optimality criterion.
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Stocki, R. (2005)
  A method to improve design reliability using optimal Latin hypercube sampling
  \emph{Computer Assisted Mechanics and Engineering Sciences}
  \bold{12}, 87--105.
}
\author{Rob Carnell}
\seealso{
  \code{\link{randomLHS}}, \code{\link{geneticLHS}},
  \code{\link{improvedLHS}} and \code{\link{maximinLHS}}
  to generate Latin Hypercube Samples.
  \code{\link{optAugmentLHS}}, \code{\link{optSeededLHS}}, and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  optimumLHS(4, 3, 5, .05)
}
\keyword{design}
