# Copyright 2020 Robert Carnell

#' Get version information for all libraries in the lhs package
#'
#' @return a character string containing the versions
#' @export
#'
#' @importFrom utils packageVersion
#'
#' @examples
#' get_library_versions()
get_library_versions <- function()
{
  return(paste(.Call("get_library_versions", PACKAGE = "lhs"), "lhs:", utils::packageVersion("lhs")))
}
