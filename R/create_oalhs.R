# Copyright 2019 Robert Carnell

#' Create an orthogonal array Latin hypercube
#'
#' @param n the number of samples or rows in the LHS (integer)
#' @param k the number of parameters or columns in the LHS (integer)
#' @param bChooseLargerDesign should a larger oa design be chosen than the n and k requested?
#' @param bverbose should information be printed with execution
#'
#' @return a numeric matrix which is an orthogonal array Latin hypercube sample
#' @export
#'
#' @examples
#' oa <- createBose(3, 4, TRUE)
#' oa_to_oalhs(9, 4, oa, TRUE)
create_oalhs <- function(n, k, bChooseLargerDesign, bverbose)
{
  return(.Call("create_oalhs", as.integer(n), as.integer(k),
               as.logical(bChooseLargerDesign),
               as.logical(bverbose), PACKAGE = "lhs"))
}
