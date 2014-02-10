\name{createAddelKemp}
\alias{createAddelKemp}
\title{Create an orthogonal array using the Addelman-Kempthorne algorithm}
\usage{
  createAddelKemp(q, ncol, bRandom)
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
  Create an orthogonal array using the Addelman-Kempthorne
  algorithm
}
\examples{
A <- createAddelKemp(3, 3, TRUE)
B <- createAddelKemp(3, 5, FALSE)
}
\seealso{
  Other methods to create orthogonal arrays
  \code{\link{createBoseBush}}, \code{\link{creatBose}},
  \code{\link{createBush}}, \code{\link{createAddelKemp3}},
  \code{\link{createAddelKempN}},
  \code{\link{createBusht}}, \code{\link{createBoseBushl}}
}

