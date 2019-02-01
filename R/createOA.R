# Copyright 2019 Robert Carnell

#' Create an orthogonal array using the Bose algorithm
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBose(3, 3, FALSE)
#' B <- createBose(5, 4, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBush()],
#' [createBoseBush()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBose <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bose", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bose-Bush algorithm
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBoseBush(4, 3, FALSE)
#' B <- createBoseBush(8, 3, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBush()],
#' [createBose()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBoseBush <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bosebush", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bush algorithm
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBush(3, 3, FALSE)
#' B <- createBush(4, 5, TRUE)
#' @seealso Other methods to create orthogonal arrays [createBoseBush()],
#' [createBose()], [createAddelKemp()], [createAddelKemp3()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createBush <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "bush", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Addelman-Kempthorne algorithm
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createAddelKemp(3, 3, TRUE)
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
#' with 2*q^3 rows
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createAddelKemp3(3, 3, TRUE)
#' B <- createAddelKemp3(3, 5, FALSE)
#' @seealso Other methods to create orthogonal arrays [createBushBush()],
#' [createBose()], [createAddelKemp()],
#' [createAddelKempN()], [createBusht()], [createBoseBushl()]
createAddelKemp3 <- function(q, ncol, bRandom=TRUE)
{
  return(.Call("oa_type1", "addelkemp3", as.integer(q), as.integer(ncol),
               as.logical(bRandom), PACKAGE = "lhs"))
}

#' Create an orthogonal array using the Bush algorithm with alternate strength
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param strength the strength of the array to be created
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
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

#' Create an orthogonal array using the Bose-Bush algorithm with alternate strength >= 3
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param lambda the lambda of the BoseBush algorithm
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBoseBushl(3, 3, 3, TRUE)
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
#' alternate strength
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
