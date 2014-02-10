\name{createBose}
\alias{createBose}
\title{Create an orthogonal array using the Bose algorithm}
\usage{
  createBose(q, ncol, bRandom)
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
  Create an orthogonal array using the Bose algorithm
}
\examples{
A <- createBose(3, 3, FALSE)
B <- createBose(5, 4, TRUE)
}
\seealso{
  Other methods to create orthogonal arrays
  \code{\link{createBush}}, \code{\link{createBoseBush}},
  \code{\link{createAddelKemp}},
  \code{\link{createAddelKemp3}},
  \code{\link{createAddelKempN}},
  \code{\link{createBusht}}, \code{\link{createBoseBushl}}
}

