\name{createAddelKemp3}
\alias{createAddelKemp3}
\title{Create an orthogonal array using the Addelman-Kempthorne algorithm
with 2*q^3 rows}
\usage{
createAddelKemp3(q, ncol, bRandom)
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
algorithm with 2*q^3 rows
}
\examples{
A <- createAddelKemp3(3, 3, TRUE)
B <- createAddelKemp3(3, 5, FALSE)
}
\seealso{
Other methods to create orthogonal arrays
\code{\link{createBoseBush}}, \code{\link{createBose}},
\code{\link{createBush}}, \code{\link{createAddelKemp}},
\code{\link{createAddelKempN}}, \code{\link{createBusht}},
\code{\link{createBoseBushl}}
}

