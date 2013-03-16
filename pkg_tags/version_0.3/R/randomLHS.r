################################################################################
#
# Function:  randomLHS.R
# Purpose:   This function creates a random latin hypercube design
# Author:    Doug Mooney
# Modified:  Rob Carnell
# Date:      May 05
#
# Variables:
#   N is the number of partitions (simulations or design points)
#   K is the number of replication (variables)
#
# Ex:  randomLHS(4,3) returns a 4x3 matrix with
#      each column constructed as follows
#      A random permutation of (1,2,3,4)
#      is generated, say (3,1,2,4) for each of K columns
#
#      Then a uniform random number is picked from
#      each indicated quartile.  In this example a random
#      number between .5 and .75 is chosen, then one between
#      0 and .25, then one between .25 and .5, finally one between
#      .75 and 1.  Note:  We must loop through in each step here to get a
#      different runif for each cell of the .P matrix
#
#      Here is sample run of randomLHS(4,3)
#
#		> randomlhd(4, 3)
#   	       [,1]      [,2]      [,3] 
#		[1,] 0.1379328 0.8588952 0.1370420
#		[2,] 0.5323584 0.2725897 0.6963334
#		[3,] 0.4522889 0.5765811 0.9899364
#		[4,] 0.8484975 0.1562488 0.4050679
#
#########################################################################

randomLHS <- function(n, k)
{
  if(length(n)!=1 |length(k)!=1) stop("n and k may not be vectors")
  if(any(is.na(c(n,k)))) stop("n and k may not be NA or NaN")
  if(any(is.infinite(c(n,k)))) stop("n and k may not be infinite")
  if(floor(n)!=n | n<1) stop("n must be a positive integer\n")
  if(floor(k)!=k | k<1) stop("k must be a positive integer\n")

  ranperm <- function(X, N){
    return(order(runif(N)))
  }

  P <- matrix(nrow=n, ncol=k)
  P <- apply(P, 2, ranperm, N=n)
  
  eps <- matrix(runif(n*k), nrow=n, ncol=k)

  P <- P - 1 + eps

  return(P/n)
}

