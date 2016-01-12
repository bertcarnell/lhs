################################################################################
#
# Function: geneticLHS.R
# Purpose:  To create a nearly optimal latin hypercube design with respect to
#           the S optimality criterion using a Genetic Algorithm
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables:
#   n is the number of partitions (simulations or design points)
#   k is the number of replication (variables)
#   pop is the number of designs in the initial population
#   gen is the number of generations over which the algorithm is applied
#   pMut is the probability with wich a mutation occurs in a column of the
#      progeny
#
# Reference:
#   This code was motivated by the work of Rafal Stocki
#   "A method to improve design reliability using optimal Latin hypercube
#    sampling" Institute of Fundamental Technological Research, Polish
#    Academy of Sciences, ul. Swietokrzyska 21, 00-049 Warsaw, Poland
#
# Explanation:
#  S optimality seeks to maximize the inverse of the sum of the inverse
#  distances from each point in the design to all other points
# Algorithm:
#  1. Generate pop random latin hypercube designs of size n by k
#  2. Calculate the S optimality of each design
#  3. Keep the best design in the first position and throw away half of the
#     rest of the population
#  4. Take a random column out of the best matrix and place it in a
#     random column of each of the other matricies, and take a random column
#     out of each of the other matricies and put it in copy of the best
#     matrix thereby causing the progeny
#  5. For each of the progeny, cause a genetic mutation pMut percent of the
#     time by swtching two elements in each column
#
# The dist function calculates the distance between each row of a matrix
#   and places the answer in a k*k half diagonal matrix
#
# 6/30/2012
#	Added verbose argument
#
################################################################################

geneticLHS <- function(n=10, k=2, pop=100, gen=4, pMut=.1, criterium="S", verbose=FALSE)
{
  if(length(n)!=1 |length(k)!=1 | length(pop)!=1 |length(gen)!=1 | length(pMut)!=1)
    stop("no parameters may be vectors")
  if(any(is.na(c(n,k,pop,gen,pMut))))
    stop("no paramters may be NA or NaN")
  if(any(is.infinite(c(n,k,pop,gen,pMut))))
    stop("no parameters may be infinite")
  if(floor(n)!=n | n<1) stop("n must be a positive integer\n")
  if(floor(k)!=k | k<1) stop("k must be a positive integer\n")
  if(floor(pop)!=pop | pop<1 | pop%%2!=0)
    stop("pop must be an even positive integer\n")
  if(floor(gen)!=gen | gen<1) stop("gen must be a positive integer\n")
  if(pMut<=0 | pMut>=1) stop("pMut must be on the interval (0,1)")

  if(n==1) {
	if (verbose) message("Design is already optimal\n")
    return(rep(1,k))
  }

  A <- array(0, dim=c(n, k, pop),
             dimnames=list(points=1:n, variables=1:k, hypercubes=1:pop))

  for(i in 1:pop) {
    for(j in 1:k) {
      A[ , j, i] <- order(runif(n))
    }
  }

  for(v in 1:gen) {

    B <- numeric(pop)

    for(i in 1:pop) 
    {
      if (criterium=="S")
      {
        B[i] <- 1/sum(1/dist(A[, , i]))
      } else if (criterium == "Maximin")
      {
        B[i] <- min(dist(A[, , i]))
      } else stop("Criterium not recognized")
    }

    H <- order(B, decreasing=TRUE)
    posit <- which.max(B)
    J <- array(NA, dim=c(n, k, pop),
               dimnames=list(points=1:n, variables=1:k, hypercubes=1:pop))
    J[ , , 1:(pop/2)] <- A[ , , posit]
    if((pop/2)==1) break

    for(i in 1:(pop/2)) {
      J[ , , (i+pop/2)] <- A[ , , H[i]]
    }

    J <- na.fail(J)
  
    for(i in 2:(pop/2)) {
      J[ , runifint(1, 1, k), i] <- J[ , runifint(1, 1, k), (i + pop/2)]
    }
    for(i in (pop/2+1):pop) {
      J[ , runifint(1, 1, k), i] <- A[ , runifint(1, 1, k), posit]
    }

    for(i in 2:pop) {
      y <- runif(k)
      for(j in 1:k) {
        if(y[j] <= pMut) {
          z <- runifint(2, 1, n)
          a <- J[z[1], j, i]
          b <- J[z[2], j, i]
          J[z[1], j, i] <- b
          J[z[2], j, i] <- a
        }
      }
    }

    A <- J

    if(v!=gen && verbose) message(paste("Generation ", v, " completed",sep=""))
  }
  
  if (verbose) message("Last generation completed")
  P <- as.matrix(J[ , , 1])
  
  test <- apply(P, 2, sum)
  if(all(test!=(n*(n+1)/2)))
    stop("Unexpected Result: A Latin Hypercube was not created\n")

  eps <- matrix(runif(n*k), nrow=n, ncol=k)

  P <- P - 1 + eps

  return(P/n)
}

