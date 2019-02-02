# Copyright 2019 Robert Carnell

#' Create a Latin hypercube from an orthogonal array
#'
#' @param n the number of samples or rows in the LHS (integer)
#' @param k the number of parameters or columns in the LHS (integer)
#' @param oa the orthogonal array to be used as the basis for the LHS (matrix of integers) or data.frame of factors
#'
#' @return a numeric matrix which is a Latin hypercube sample
#' @export
#'
#' @examples
#' oa <- createBose(3, 4, TRUE)
#' B <- oa_to_oalhs(9, 4, oa)
oa_to_oalhs <- function(n, k, oa)
{
  if (is.integer(oa) && is.matrix(oa))
  {
    return(.Call("oa_to_lhs", as.integer(n), as.integer(k), oa,
                 FALSE, PACKAGE = "lhs"))
  } else if (is.data.frame(oa))
  {
    Y <- as.matrix(oa)
    Z <- matrix(as.integer(Y), nrow = nrow(oa), ncol = ncol(oa))
    return(.Call("oa_to_lhs", as.integer(n), as.integer(k), Z,
                 FALSE, PACKAGE = "lhs"))
  } else
  {
    stop("oa must be an integer matrix or it must be a data.frame of factors")
  }
}
