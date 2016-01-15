################################################################################
#
# Function: runifint.R
# Purpose:  To create a random uniform sample of integers.  Not exported.
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables:
#	n is the number of samples
#	min_int the lower bounds (inclusive)
#   max_int the upper bounds (inclusive)
#
################################################################################

runifint <- function(n=1, min_int=0, max_int=1)
{
	r <- runif(n, min=0, max=1)
	int <- min_int + floor(r * (max_int + 1 - min_int))
	int <- pmin(int, max_int)
	return(int)
}