# Copyright 2019 Robert Carnell

#' Create an orthogonal array using the Bose algorithm.
#'
#' The \code{bose} program
#' produces \code{OA( q^2, k, q, 2 )},  \code{k <= q+1} for prime powers \code{q}.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' R.C. Bose (1938) Sankhya Vol 3 pp 323-338
#' @examples
#' A <- createBose(3, 3, FALSE)
#' B <- createBose(5, 4, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBush()],
#' [createBoseBush()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBose <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bose", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bose-Bush algorithm.
#'
#' The \code{bosebush} program
#' produces \code{OA( 2q^2, k, q, 2 )},  \code{k <= 2q+1}, for powers of 2, \code{q=2^r}.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' R.C. Bose and K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 508-524.
#' @examples
#' A <- createBoseBush(4, 3, FALSE)
#' B <- createBoseBush(8, 3, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBush()],
#' [createBose()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBoseBush <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bosebush", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bush algorithm.
#'
#' The \code{bush} program
#' produces \code{OA( q^3, k, q, 3 )},  \code{k <= q+1} for prime powers \code{q}.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 426-434
#' @examples
#' A <- createBush(3, 3, FALSE)
#' B <- createBush(4, 5, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBush <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bush", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Addelman-Kempthorne algorithm.
#'
#' The \code{addelkemp} program produces \code{OA( 2q^2, k, q, 2 )},  \code{k <= 2q+1},
#' for odd prime powers \code{q}.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' S. Addelman and O. Kempthorne (1961) Annals of Mathematical Statistics, Vol 32 pp 1167-1176.
#' @examples
#' A <- createAddelKemp(3, 3, TRUE)
#' B <- createAddelKemp(3, 5, FALSE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createAddelKemp <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "addelkemp", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Addelman-Kempthorne algorithm
#' with \code{2q^3} rows.
#'
#' The \code{addelkemp3} program produces
#' \code{OA( 2*q^3, k, q, 2 )},  \code{k <= 2q^2+2q+1}, for prime powers \code{q}.
#' \code{q} may be an odd prime power, or \code{q} may be 2 or 4.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' S. Addelman and O. Kempthorne (1961) Annals of Mathematical Statistics, Vol 32 pp 1167-1176.
#' @examples
#' A <- createAddelKemp3(3, 3, TRUE)
#' B <- createAddelKemp3(3, 5, FALSE)
#' @seealso Other methods to create orthogonal arrays [createBushBush()],
#' [createBose()], [createAddelKemp()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createAddelKemp3 <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "addelkemp3", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bush algorithm with alternate strength.
#'
#' The \code{busht} program produces \code{OA( q^t, k, q, t )},  \code{k <= q+1}, \code{t>=3},
#' for prime powers \code{q}.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param strength the strength of the array to be created
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 426-434
#' @examples
#' set.seed(1234)
#' A <- createBusht(3, 4, 2, TRUE)
#' B <- createBusht(3, 4, 3, FALSE)
#' G <- createBusht(3, 4, 3, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBoseBushl()]
createBusht <- function(q, ncol, strength, bRandom=TRUE)
{
  return(.Call("oa_type2", "busht", as.integer(strength), as.integer(q),
               as.integer(ncol), as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bose-Bush algorithm with alternate strength >= 3.
#'
#' The \code{bosebushl} program produces \code{OA( lambda*q^2, k, q, 2 )},
#' \code{k <= lambda*q+1}, for prime powers \code{q} and \code{lambda > 1}.  Both \code{q} and
#' \code{lambda} must be powers of the same prime.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param lambda the lambda of the BoseBush algorithm
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @references
#' Owen, Art.  Orthogonal Arrays for: Computer Experiments, Visualizations, and Integration in high dimenstions. \url{http://lib.stat.cmu.edu/designs/oa.c}. 1994
#' R.C. Bose and K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 508-524.
#' @examples
#' A <- createBoseBushl(3, 3, 3, TRUE)
#' B <- createBoseBushl(4, 4, 16, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createBush()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()]
createBoseBushl <- function(q, ncol, lambda, bRandom=TRUE)
{
  return(.Call("oa_type2", "bosebushl", as.integer(lambda), as.integer(q),
               as.integer(ncol), as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Addelman-Kempthorne algorithm with
#' alternate strength with \code{2q^n} rows.
#'
#' The \code{addelkempn} program produces
#' \code{OA( 2*q^n, k, q, 2 )},  \code{k <= 2(q^n - 1)/(q-1)-1}, for prime powers \code{q}.
#' \code{q} may be an odd prime power, or \code{q} may be 2 or 4.
#'
#' From Owen: An orthogonal array \code{A} is a matrix of \code{n} rows, \code{k}
#' columns with every element being one of \code{q} symbols
#' \code{0,...,q-1}.  The array has strength \code{t} if, in every \code{n} by \code{t}
#' submatrix, the \code{q^t} possible distinct rows, all appear
#' the same number of times.  This number is the index
#' of the array, commonly denoted \code{lambda}.  Clearly,
#' \code{lambda*q^t=n}. The notation for such an array is \code{OA( n, k, q, t )}.
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param exponent the exponent on q
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createAddelKempN(3, 4, 3, TRUE)
#' B <- createAddelKempN(3, 4, 4, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createBush()], [createAddelKemp()], [createAddelKemp3()],
#' [createBusht()], [createBoseBushl()]
createAddelKempN <- function(q, ncol, exponent, bRandom=TRUE)
{
  return(.Call("oa_type2", "addelkempn", as.integer(exponent), as.integer(q),
               as.integer(ncol), as.logical(bRandom), PACKAGE = "lhs"))
}
