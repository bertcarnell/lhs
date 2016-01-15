\name{geneticLHS}
\alias{geneticLHS}
\title{Latin Hypercube Sampling with a Genetic Algorithm}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This function attempts to optimize the
sample with respect to the S optimality criterion through a genetic type
algorithm.
}
\usage{geneticLHS(n=10, k=2, pop=100, gen=4, pMut=.1, criterium="S", verbose=FALSE)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{pop}{The number of designs in the initial population}
  \item{gen}{The number of generations over which the algorithm is applied}
  \item{pMut}{The probability with which a mutation occurs in a column of the progeny}
  \item{criterium}{The optimality criterium of the algorithm.  Default is \code{S}.  \code{Maximin} is also supported}
  \item{verbose}{Print informational messages.  Default is \code{FALSE}}
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

Genetic Algorithm:
\enumerate{
  \item Generate \code{pop} random latin hypercube designs of size \code{n} by \code{k}
  \item Calculate the S optimality measure of each design
  \item Keep the best design in the first position and throw away half of the
    rest of the population
  \item Take a random column out of the best matrix and place it in a
    random column of each of the other matricies, and take a random column
    out of each of the other matricies and put it in copies of the best
    matrix thereby causing the progeny
  \item For each of the progeny, cause a genetic mutation \code{pMut} percent of the
    time.  The mutation is accomplished by swtching two elements in a column
  }
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Stocki, R. (2005)
  A method to improve design reliability using optimal Latin hypercube sampling
  \emph{Computer Assisted Mechanics and Engineering Sciences}
  \bold{12}, 87--105.

  Stein, M.  (1987)
  Large Sample Properties of Simulations Using Latin Hypercube Sampling.
  \emph{Technometrics}.
  \bold{29}, 143--151.
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
