################################################################################
#
# Function: optAugmentLHS.R
# Purpose:  To add an additional m points to an existing latin hypercube
#           design in lhs while maintaining marginal distribution uniformity
#           and while attempting to maximize S optimality
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables:
#   lhs contains an existing latin hypercube design with a number
#       of rows equal to the points in the design (simulations)
#       and a number of columns equal to the number of variables
#       (parameters).  The values of each cell must be between 0 and 1 and not
#       contain any NA entries.  This algorithm also assumes that the
#       design is uniformly distributed
#   m = the number of addtional points to augment the design with
#       (default=1, must be a positive integer)
#   mult = a multiple.  m*mult random candidate points will be created.
#          (default=2, and it is suggested for large values of m)
#
# Explanation:
#   1. Test for undesirable conditions.
#   2. Create a matrix B to hold the candidate points after the design has
#      been re-partitioned into (N+m)^2 cells
#   3. Randomly sweep through each column (1 to K) in the repartitioned
#      design to see where the missing cells lie.
#   4. For each column (variable), randomly search for an empty cell, generate a
#      random value that fits in that cell, record the value in B
#      B can contain more filled cells than m unles m = 2N, in which case B will
#      contain exactly m filled cells
#   5. Create a matrix P which contains random integers selecting
#      the cells of B
#   6. Replace the cells of P with the corresponding cells of B
#      There is no guarantee that all the possible points will be available in P
#   7. Find the distance from each point in P to the current design
#   8. Select the point which maximizes the distance
#   9. Update B by eliminating the cells in each column of B which correspond
#      to the point that was just used to augment the design
#  10. Repeat until all m points are filled
#
################################################################################

optAugmentLHS <- function(lhs, m=1, mult=2)
{
  if(is.matrix(lhs)==FALSE)
    stop("Input Design must be in the Matrix class\n")
  if(length(m)!=1 | length(mult)!=1) stop("m and mult may not be vectors")
  if(is.na(m) | is.infinite(m)) stop("m may not be infinite, NA, or NaN")
  if(is.na(mult) | is.infinite(mult)) stop("mult may not be infinite, NA, or NaN")
  if(m!=floor(m) | m<1) stop("m must be a positive integer\n")
  if(any(is.na(lhs)==TRUE))
    stop("Input Design cannot contain any NA entries\n")
  if(any(lhs<0 | lhs>1))
    stop("Input Design must have entries on the interval [0,1]\n")

  K <- ncol(lhs)
  N <- nrow(lhs)

  colvec <- order(runif(K))
  rowvec <- order(runif(N + m))

  B <- matrix(nrow=(N + m), ncol=K)

  for(j in colvec) {
    newrow <- 0
    for(i in rowvec) {
      if((any((i-1)/(N + m) <= lhs[ ,j] & lhs[ ,j] <= i/(N + m)))==FALSE) {
        newrow <- newrow + 1
        B[newrow, j] <- runif(1, (i-1)/(N + m), i/(N + m))
      }
    }
  }

  lhs <- rbind(lhs, matrix(nrow=m, ncol=K))

  for(k in 1:m) {

    P <- matrix(nrow=m*mult, ncol=K)
    for(i in 1:K) {
      P[,i] <- runifint(m*mult, 1, length(na.exclude(B[,i])))
    }
    for(i in 1:K) {
      for(j in 1:(m*mult)) {
        P[j, i] <- B[P[j, i], i]
      }
    }

    vec <- numeric(K)
    dist1 <- 0
    maxdist <- .Machine$double.xmin
    
    for(i in 1:(m*mult-k+1)) {
      dist1 <- numeric(N+k-1)
      for(j in 1:(N+k-1)) {
        vec <- P[i,] - lhs[j,]
        dist1[j] <- vec%*%vec
        }
      if(sum(dist1) > maxdist) {
        maxdist <- sum(dist1)
        maxrow <- i
      }
    }
    
    lhs[N+k,] <- P[maxrow,]

    for(i in 1:K) {
      for(j in 1:length(na.omit(B[,i]))) {
        if(P[maxrow,i]==B[j,i]) B[j,i] <- NA
      }
    }
    for(i in 1:K) {
      if(length(na.omit(B[,i]))==0) next
      u <- length(na.omit(B[,i]))
      B[1:u,i] <- na.omit(B[,i])
      B[(u+1):m,i] <- NA
    }
  }
  
  return(lhs)
}

