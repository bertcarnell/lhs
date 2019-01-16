# Copyright 2019 Robert Carnell

#' Create a Latin hypercube from an orthogonal array
#'
#' @param n the number of samples or rows in the LHS (integer)
#' @param k the number of parameters or columns in the LHS (integer)
#' @param oa the orthogonal array to be used as the basis for the LHS (matrix of integers)
#' @param bverbose should information be printed with execution
#'
#' @return a numeric matrix which is a Latin hypercube sample
#' @export
#'
#' @examples
#' oa <- createBose(3, 4, TRUE)
#' oa_to_oalhs(9, 4, oa, TRUE)
oa_to_oalhs <- function(n, k, oa, bverbose=FALSE)
{
  return(.Call("oa_to_lhs", as.integer(n), as.integer(k), oa,
               as.logical(bverbose), PACKAGE = "lhs"))
}
