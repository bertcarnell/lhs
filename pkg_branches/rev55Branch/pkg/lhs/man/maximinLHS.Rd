\name{maximinLHS}
\alias{maximinLHS}
\title{Maximin Latin Hypercube Sample}
\description{
Draws a Latin Hypercube Sample from a set of uniform distributions for use in
creating a Latin Hypercube Design.  This function attempts to optimize the
sample by maximizing the minium distance between design points (maximin criteria).
}
\usage{maximinLHS(n, k, method="build", dup=1, eps=0.05, maxIter=100, 
                  optimize.on="grid", debug=FALSE)}
\arguments{
  \item{n}{The number of partitions (simulations or design points)}
  \item{k}{The number of replications (variables)}
  \item{method}{\code{build} or \code{iterative} is the method of LHS creation.
                \code{build} finds the next best point while constructing the LHS.
                \code{iterative} optimizes the resulting sample on [0,1] or sample 
                grid on [1,N]}
  \item{dup}{A factor that determines the number of candidate points used in the
             search. A multiple of the number of remaining points than can be
             added.  This is used when \code{method="build"}}
  \item{eps}{The minimum percent change in the minimum distance used in the 
            \code{iterative} method}
  \item{maxIter}{The maximum number of iterations to use in the \code{iterative} method}
  \item{optimize.on}{\code{grid} or \code{result} gives the basis of the optimization.
                     \code{grid} optimizes the LHS on the underlying integer grid.
                     \code{result} optimizes the resulting sample on [0,1]}
  \item{debug}{prints additional information about the process of the optimization}
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

Here, values are added to the design one by one such that the maximin criteria is
satisfied.
}
\value{
An \code{n} by \code{k} Latin Hypercube Sample matrix with values uniformly distributed on [0,1]
}
\references{
  Stein, M.  (1987)
  Large Sample Properties of Simulations Using Latin Hypercube Sampling.
  \emph{Technometrics}.
  \bold{29}, 143--151.

  This function is motivated by the MATLAB program written by
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
  maximinLHS(4, 3, dup=2)
  maximinLHS(4, 3, method="build", dup=2)
  maximinLHS(4, 3, method="iterative", eps=0.05, maxIter=100, optimize.on="grid")
  maximinLHS(4, 3, method="iterative", eps=0.05, maxIter=100, optimize.on="result")
}
\keyword{design}
