################################################################################
#
# Function: augmentLHS.R
# Purpose:  To add an additional m points to an existing latin hypercube
#           design in lhs while maintaining marginal distribution uniformity
# Author:   Rob Carnell
# Created:  26 May 05
#
# Variables: lhs contains an existing latin hypercube design with a number
#                of rows equal to the points in the design (simulations)
#                and a number of columns equal to the number of variables
#                (parameters).  The values of each cell must be between 0 and 1
#                and uniformly distributed
#            m is the number of addtional points to augment the design with
#              (default=1, must be a positive integer)
#
# Explanation:
#   First, create a matrix B to hold the candidate points after the design has
#   been re-partitioned into (N+m)^2 cells
#   We want to randomly sweep through each column (1 to K) in the repartitioned
#   design to see where the missing cells lie.
#   For each column (variable), randomly search for an empty row, generate a
#   random value that fits in that row, record the value in B
#   B can contain more filled cells than m unles m = 2N, in which case B will
#   contain exactly m filled cells
#   Finally, keep only the first m rows of B.  It is guaranteed to have m full
#   rows in B.  The deleted rows are partially full.  The candidate
#   points are selected randomly due to the random search for empty cells
#
# 10/21/06
#   augmentLHS functions where one row was added had an error - fixed
#
################################################################################

augmentLHS <- function(lhs, m=1)
{
  if(!is.matrix(lhs))
    stop("Input Latin Hypercube Design must be in the Matrix class\n")
  if(length(m)!=1) stop("m may not be a vector")
  if(is.na(m) | is.infinite(m)) stop("m may not be infinite, NA, or NaN")
  if(m!=floor(m) | m<1) stop("m must be a positive integer\n")
  if(any(is.na(lhs)))
    stop("Input Design cannot contain any NA entries\n")
  if(any(lhs<0 | lhs>1))
    stop(paste("Input Latin Hypercube Design must have entries on the ",
              "interval [0,1] which are uniformly distributed\n", sep=""))

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

  if(is.matrix(B[1:m,])){
    E <- rbind(lhs, B[1:m, ])
  } else E <- rbind(lhs, matrix(B[1:m,], nrow=m, ncol=K))
  row.names(E) <- NULL
  return(E)
}

