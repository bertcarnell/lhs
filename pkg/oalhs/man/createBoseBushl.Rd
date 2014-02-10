\name{createBoseBushl}
\alias{createBoseBushl}
\title{Create an orthogonal array using the Bose-Bush algorithm with alternate strength >= 3}
\usage{
  createBoseBushl(q, ncol, lambda, bRandom)
}
\arguments{
  \item{q}{the number of symbols in the array}

  \item{ncol}{number of parameters or columns}

  \item{lambda}{the lambda of the BoseBush algorithm}

  \item{bRandom}{should the array be randomized}
}
\value{
  an orthogonal array
}
\description{
  Create an orthogonal array using the Bose-Bush algorithm
  with alternate strength >= 3
}
\examples{
A <- createBoseBushl(3, 3, 3, TRUE)
B <- createBoseBushl(4, 4, 16, TRUE)
}
\seealso{
  Other methods to create orthogonal arrays
  \code{\link{createBoseBush}}, \code{\link{createBose}},
  \code{\link{createBush}}, \code{\link{createAddelKemp}},
  \code{\link{createAddelKempN}},
  \code{\link{createAddelKemp3}}, \code{\link{createBusht}}
}

