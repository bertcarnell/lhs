\name{augmentLHS}
\alias{augmentLHS}
\title{Augment a Latin Hypercube Design}
\description{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.
}
\usage{augmentLHS(lhs, m=1)}
\arguments{
  \item{lhs}{The Latin Hypercube Design to which points are to be added}
  \item{m}{The number of additional points to add to matrix \code{lhs}}
}
\details{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.  Augmentation is perfomed
in a random manner.

The algorithm used by this function has the following steps.
First, create a new matrix to hold the candidate points after the design has
been re-partitioned into \eqn{(n+m)^{2}}{(n+m)^2} cells, where n is number of
points in the original \code{lhs} matrix.  Then randomly sweep through each
column (1\ldots\code{k}) in the repartitioned design to find the missing cells.
For each column (variable), randomly search for an empty row, generate a
random value that fits in that row, record the value in the new matrix.
The new matrix can contain more filled cells than \code{m} unles \eqn{m = 2n},
in which case the new matrix will contain exactly \code{m} filled cells.
Finally, keep only the first m rows of the new matrix.  It is guaranteed to
have \code{m} full rows in the new matrix.  The deleted rows are partially full.
The additional candidate points are selected randomly due to the random search
for empty cells.
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
  \code{\link{optAugmentLHS}} and \code{\link{optSeededLHS}}
  to modify and augment existing designs.
}
\examples{
  a <- randomLHS(4,3)
  a
  augmentLHS(a, 2)
}
\keyword{design}
