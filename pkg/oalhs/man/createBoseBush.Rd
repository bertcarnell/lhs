\name{createBoseBush}
\alias{createBoseBush}
\title{Create an orthogonal array using the Bose-Bush algorithm}
\usage{
  createBoseBush(q, ncol, bRandom)
}
\arguments{
  \item{q}{the number of symbols in the array}

  \item{ncol}{number of parameters or columns}

  \item{bRandom}{should the array be randomized}
}
\value{
  an orthogonal array
}
\description{
  Create an orthogonal array using the Bose-Bush algorithm
}
\examples{
A <- createBoseBush(4, 3, FALSE)
B <- createBoseBush(3, 3, TRUE)
}
\seealso{
  Other methods to create orthogonal arrays
  \code{\link{createBush}}, \code{\link{createBose}},
  \code{\link{createAddelKemp}},
  \code{\link{createAddelKemp3}},
  \code{\link{createAddelKempN}},
  \code{\link{createBusht}}, \code{\link{createBoseBushl}}
}

