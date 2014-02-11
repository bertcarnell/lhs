\name{createBush}
\alias{createBush}
\title{Create an orthogonal array using the Bush algorithm}
\usage{
createBush(q, ncol, bRandom)
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
Create an orthogonal array using the Bush algorithm
}
\examples{
A <- createBush(3, 3, FALSE)
B <- createBush(4, 5, TRUE)
}
\seealso{
Other methods to create orthogonal arrays
\code{\link{createBoseBush}}, \code{\link{createBose}},
\code{\link{createAddelKemp}},
\code{\link{createAddelKemp3}},
\code{\link{createAddelKempN}}, \code{\link{createBusht}},
\code{\link{createBoseBushl}}
}

