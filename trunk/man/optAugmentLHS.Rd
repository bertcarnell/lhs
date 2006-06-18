\name{optAugmentLHS}
\alias{optAugmentLHS}
\title{Optimal Augmented Latin Hypercube Sample}
\description{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.  This function attempts to
add the points to the design in an optimal way.
}
\usage{optAugmentLHS(lhs, m=1, mult=2)}
\arguments{
  \item{lhs}{The Latin Hypercube Design to which points are to be added}
  \item{m}{The number of additional points to add to matrix \code{lhs}}
  \item{mult}{\code{m*mult} random candidate points will be created.}
}
\details{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.  This function attempts to
add the points to the design in a way that maximizes S optimality.

S-optimality seeks to maximize the mean distance from each design point to all
the other points in the design, so the points are as spread out as possible.
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
\author{Rob Carnell}
\seealso{
  \code{\link{randomLHS}}, \code{\link{geneticLHS}},
  \code{\link{improvedLHS}}, \code{\link{maximinLHS}}, and
  \code{\link{optimumLHS}} to generate Latin Hypercube Samples.
  \code{\link{optSeededLHS}} and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  a <- randomLHS(4,3)
  a
  optAugmentLHS(a, 2, 3)
}
\keyword{design}
