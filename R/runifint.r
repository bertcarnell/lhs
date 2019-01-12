# Copyright 2019 Robert Carnell

#' Create a Random Sample of Uniform Integers
#'
#' @param n The number of samples
#' @param min_int the minimum integer \code{x >= min_int}
#' @param max_int the maximum integer \code{x <= max_int}
#'
#' @return the sample sample of size \code{n}
runifint <- function(n=1, min_int=0, max_int=1)
{
	r <- runif(n, min = 0, max = 1)
	int <- min_int + floor(r * (max_int + 1 - min_int))
	int <- pmin(int, max_int)
	return(int)
}
