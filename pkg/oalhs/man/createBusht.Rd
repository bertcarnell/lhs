\name{createBusht}
\alias{createBusht}
\title{Create an orthogonal array using the Bush algorithm with alternate strength}
\usage{
createBusht(q, ncol, strength, bRandom)
}
\arguments{
  \item{q}{the number of symbols in the array}

  \item{ncol}{number of parameters or columns}

  \item{strength}{the strength of the array to be created}

  \item{bRandom}{should the array be randomized}
}
\value{
an orthogonal array
}
\description{
Create an orthogonal array using the Bush algorithm with
alternate strength
}
\examples{
A <- createBusht(3, 4, 2, TRUE)
B <- createBusht(3, 4, 3, FALSE)
G <- createBusht(3, 4, 4, TRUE)
}
\seealso{
Other methods to create orthogonal arrays
\code{\link{createBoseBush}}, \code{\link{createBose}},
\code{\link{createBush}}, \code{\link{createAddelKemp}},
\code{\link{createAddelKempN}},
\code{\link{createAddelKemp3}},
\code{\link{createBoseBushl}}
}

