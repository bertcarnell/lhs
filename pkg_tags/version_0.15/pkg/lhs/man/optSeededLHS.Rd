\name{optSeededLHS}
\alias{optSeededLHS}
\title{Optimum Seeded Latin Hypercube Sample}
\description{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.  This function then uses the
columnwise pairwise (\acronym{CP}) algoritm to optimize the design.  The original design
is not necessarily maintained.
}
\usage{optSeededLHS(seed, m=1, maxSweeps=2, eps=.1, verbose=FALSE)}
\arguments{
  \item{seed}{The number of partitions (simulations or design points)}
  \item{m}{The number of additional points to add to matrix \code{seed}}
  \item{maxSweeps}{The maximum number of times the CP algorithm is applied to all the columns.}
  \item{eps}{The optimal stopping criterion}
  \item{verbose}{Print informational messages}
}
\details{
Augments an existing Latin Hypercube Sample, adding points to the design, while
maintaining the \emph{latin} properties of the design.  This function then uses the
\acronym{CP} algoritm to optimize the design.  The original design
is not necessarily maintained.
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
  \code{\link{optAugmentLHS}} and
  \code{\link{augmentLHS}} to modify and augment existing designs.
}
\examples{
  a <- randomLHS(4,3)
  a
  optSeededLHS(a, 2, 2, .1)
}
\keyword{design}
