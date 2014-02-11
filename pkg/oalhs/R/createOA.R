
#' Create an orthogonal array using the Bose algorithm
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBose(3, 3, FALSE)
#' B <- createBose(5, 4, TRUE)
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBush}}, 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createBoseBushl}}
createBose <- function(q, ncol, bRandom)
{
  return (.Call("oa_type1", "bose", as.integer(q), as.integer(ncol), 
               as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createBoseBushl}}
createBoseBush <- function(q, ncol, bRandom)
{
  return (.Call("oa_type1", "bosebush", as.integer(q), as.integer(ncol), 
               as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createBoseBushl}}
createBush <- function(q, ncol, bRandom)
{
  return (.Call("oa_type1", "bush", as.integer(q), as.integer(ncol),  
               as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createBush}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createBoseBushl}}
createAddelKemp <- function(q, ncol, bRandom)
{
  return (.Call("oa_type1", "addelkemp", as.integer(q), as.integer(ncol),  
               as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createBush}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createBoseBushl}}
createAddelKemp3 <- function(q, ncol, bRandom)
{
  return (.Call("oa_type1", "addelkemp3", as.integer(q), as.integer(ncol), 
               as.logical(bRandom), PACKAGE="oalhs"))
}


#' Create an orthogonal array using the Bush algorithm with alternate strength
#'
#' @param q the number of symbols in the array
#' @param ncol number of parameters or columns
#' @param strength the strength of the array to be created
#' @param bRandom should the array be randomized
#' @return an orthogonal array
#' @export
#' @examples A <- createBusht(3, 4, 2, TRUE)
#' B <- createBusht(3, 4, 3, FALSE)
#' G <- createBusht(3, 4, 4, TRUE)
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createBush}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createBoseBushl}}
createBusht <- function(q, ncol, strength, bRandom)
{
  return (.Call("oa_type2", "busht", as.integer(strength), as.integer(q), 
               as.integer(ncol), as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createBush}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createAddelKempN}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createBusht}}
createBoseBushl <- function(q, ncol, lambda, bRandom)
{
  return (.Call("oa_type2", "bosebushl", as.integer(lambda), as.integer(q), 
               as.integer(ncol), as.logical(bRandom), PACKAGE="oalhs"))
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
#' @seealso Other methods to create orthogonal arrays 
#' \code{\link{createBoseBush}}, 
#' \code{\link{createBose}}, 
#' \code{\link{createBush}}, 
#' \code{\link{createAddelKemp}}, 
#' \code{\link{createBusht}}, 
#' \code{\link{createAddelKemp3}}, 
#' \code{\link{createBoseBushl}}
createAddelKempN <- function(q, ncol, exponent, bRandom)
{
  return (.Call("oa_type2", "addelkempn", as.integer(exponent), as.integer(q), 
               as.integer(ncol), as.logical(bRandom), PACKAGE="oalhs"))
}
