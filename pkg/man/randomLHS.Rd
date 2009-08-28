\name{randomLHS}
\alias{randomLHS}
\alias{latin hypercube}
\title{Random Latin Hypercube}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This sample is taken in a random
manner without regard to optimization.
}
\usage{randomLHS(n, k, preserveDraw)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{preserveDraw}{Default:FALSE.  Ensures that two subsequent draws
     with the same \code{n}, but one with \code{k} and one with \code{m}
     variables \code{(k<m)}, will have the same first k columns
     if the seed is the same.}
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
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Stein, M.  (1987)
  Large Sample Properties of Simulations Using Latin Hypercube Sampling.
  \emph{Technometrics}.
  \bold{29}, 143--151.
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
  # draw a Latin hypercube
  randomLHS(4, 3)
  
  # transform a Latin hypercube
  X <- randomLHS(5, 2)
  Y <- matrix(0, nrow=5, ncol=2)
  Y[,1] <- qnorm(X[,1], mean=3, sd=0.1)
  Y[,2] <- qbeta(X[,2], shape1=2, shape2=3)
  
  # check the preserveDraw option
  set.seed(1976)
  X <- randomLHS(6,3,preserveDraw=TRUE)
  set.seed(1976)
  Y <- randomLHS(6,5,preserveDraw=TRUE)
  all(abs(X - Y[,1:3]) < 1E-12) # TRUE
}
\keyword{design}
