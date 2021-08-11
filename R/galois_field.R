# Copyright 2021 Robert Carnell

#' Create a Galois field
#'
#' @param q The order of the Galois Field q = p^n
#'
#' @return a GaloisField object containing
#' \describe{
#'   \item{n}{q = p^n}
#'   \item{p}{The prime modulus of the field q=p^n}
#'   \item{q}{The order of the Galois Field q = p^n.  \code{q} must be a prime power.}
#'   \item{xton}{coefficients of the characteristic polynomial where the first coefficient is on $x^0$, the second is on $x^1$ and so on}
#'   \item{inv}{An index for which row of \code{poly} (zero based) is the multiplicative inverse of this row.  An \code{NA} indicates that this row of \code{poly} has no inverse.  e.g. c(3, 4) means that row 4=3+1 is the inverse of row 1 and row 5=4+1 is the inverse of row 2}
#'   \item{neg}{An index for which row of \code{poly} (zero based) is the negative or additive inverse of this row.  An \code{NA} indicates that this row of \code{poly} has no negative.  e.g. c(3, 4) means that row 4=3+1 is the negative of row 1 and row 5=4+1 is the negative of row 2}
#'   \item{root}{An index for which row of \code{poly} (zero based) is the square root of this row.  An \code{NA} indicates that this row of \code{poly} has no square root.  e.g. c(3, 4) means that row 4=3+1 is the square root of row 1 and row 5=4+1 is the square root of row 2}
#'   \item{plus}{sum table of the Galois Field}
#'   \item{times}{multiplication table of the Galois Field}
#'   \item{poly}{rows are polynomials of the Galois Field where the entries are the coefficients of the polynomial where the first coefficient is on $x^0$, the second is on $x^1$ and so on}
#' }
#' @export
#'
#' @examples
#' gf <- create_galois_field(4);
create_galois_field <- function(q)
{
  if (q <= 1) stop("q must be 2 or greater")
  gf <- .Call("create_galois_field", as.integer(q), PACKAGE = "lhs")
  class(gf) <- "GaloisField"
  names(gf) <- c("n", "p", "q", "xton", "inv", "neg", "root", "plus", "times", "poly")
  if (any(gf$inv == -1))
    gf$inv[which(gf$inv == -1)] <- NA
  if (any(gf$neg == -1))
    gf$neg[which(gf$neg == -1)] <- NA
  if (any(gf$root == -1))
    gf$root[which(gf$root == -1)] <- NA
  return(gf)
}

#' Multiplication in polynomial representation
#'
#' @param p modulus
#' @param n length of polynomials
#' @param xton characteristic polynomial vector for the field (x to the n power)
#' @param p1 polynomial vector 1
#' @param p2 polynomial vector 2
#'
#' @return the product of p1 and p2
#' @export
#'
#' @examples
#' gf <- create_galois_field(4)
#' a <- poly_prod(gf$p, gf$n, gf$xton, c(1, 0), c(0, 1))
#' stopifnot(all(a == c(0, 1)))
poly_prod <- function(p, n, xton, p1, p2)
{
  if (n != length(xton)) stop("the length of xton must be n")
  if (n != length(p1)) stop("the length of p1 must be n")
  if (n != length(p2)) stop("the length of p2 must be n")
  if (any(c(xton, p1, p2) >= p)) stop("The entries of the polynomial vectors must be less than p")
  if (any(c(xton, p1, p2) < 0)) stop("The entries of the polynomial vectors must be greater than 0")

  .Call("poly_prod", as.integer(p), as.integer(n), as.integer(xton),
        as.integer(p1), as.integer(p2), PACKAGE = "lhs")
}

#' Addition in polynomial representation
#'
#' @param p modulus
#' @param n length of polynomial 1 and 2
#' @param p1 polynomial vector 1
#' @param p2 polynomial vector 2
#'
#' @return the sum of p1 and p2
#' @export
#'
#' @examples
#' gf <- create_galois_field(4)
#' a <- poly_sum(gf$p, gf$n, c(1, 0), c(0, 1))
#' stopifnot(all(a == c(1, 1)))
poly_sum <- function(p, n, p1, p2)
{
  if (n != length(p1)) stop("the length of p1 must be n")
  if (n != length(p2)) stop("the length of p2 must be n")
  if (any(c(p1, p2) >= p)) stop("The entries of the polynomial vectors must be less than p")
  if (any(c(p1, p2) < 0)) stop("The entries of the polynomial vectors must be greater than 0")
  .Call("poly_sum", as.integer(p), as.integer(n), as.integer(p1), as.integer(p2),
        PACKAGE = "lhs")
}

#' Convert polynomial to integer in <code>0..q-1</code>
#'
#' @param p modulus
#' @param n the length of poly
#' @param poly the polynomial vector
#'
#' @return an integer
#' @export
#'
#' @examples
#' gf <- create_galois_field(4)
#' stopifnot(poly2int(gf$p, gf$n, c(0, 0)) == 0)
poly2int <- function(p, n, poly)
{
  if (n != length(poly)) stop("the length of poly must be n")
  if (any(poly >= p)) stop("The entries of the polynomial vectors must be less than p")
  if (any(poly < 0)) stop("The entries of the polynomial vectors must be greater than 0")
  .Call("poly2int", as.integer(p), as.integer(n), as.integer(poly), PACKAGE = "lhs")
}

