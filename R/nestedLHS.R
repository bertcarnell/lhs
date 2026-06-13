# Copyright 2026 Robert Carnell

#' Construct a nested Latin hypercube design
#'
#' Constructs a Latin hypercube design of \code{large} points that contains a
#' smaller Latin hypercube design of \code{small} points as a subset.
#'
#' @details A nested Latin hypercube design (Qian, 2009) is a pair of Latin
#' hypercube designs in which the points of the smaller design are a subset of the
#' points of the larger design.  Both the small design (of \code{small} points)
#' and the large design (of \code{large} points) are Latin hypercube designs in
#' their own right.  Nested designs are useful for computer experiments that
#' involve two levels of fidelity:  the inexpensive high-fidelity-equivalent
#' subset is run at the \code{small} points and the larger, less expensive code is
#' run at all \code{large} points.
#'
#' \code{large} must be an integer multiple of \code{small}.  The design is
#' constructed one column at a time by dividing [0,1] into \code{small} coarse
#' intervals, each of which contains \eqn{a = large / small} fine intervals.  One
#' fine interval per coarse interval is chosen to host a point of the small design
#' (guaranteeing it is a Latin hypercube design of \code{small}) and the remaining
#' fine intervals are assigned to the extra points of the large design
#' (guaranteeing it is a Latin hypercube design of \code{large}).  The small
#' design is returned as the first \code{small} rows of the large design.
#'
#' @param small the number of points (rows) in the smaller, nested design
#' @param large the number of points (rows) in the larger design.  Must be an
#' integer multiple of \code{small} and strictly greater than \code{small}.
#' @param k the number of columns or parameters/variables
#' @return a list with two Latin Hypercube Sample matrices, each with \code{k}
#' columns and values uniformly distributed on [0,1]:
#' \describe{
#'   \item{small}{the nested design with \code{small} rows}
#'   \item{large}{the design with \code{large} rows, whose first \code{small}
#'   rows are identical to \code{small}}
#' }
#' @export
#' @importFrom stats runif
#'
#' @author Rob Carnell
#' @references
#' Qian, P. Z. G. (2009) Nested Latin hypercube designs. \emph{Biometrika}.
#' \bold{96}, 957--970.
#'
#' @keywords design
#'
#' @seealso [randomLHS()], [geneticLHS()], [improvedLHS()], [maximinLHS()],
#' and [optimumLHS()] to generate Latin Hypercube Samples.  [slicedLHS()] to
#' generate a Latin hypercube design that can be partitioned into smaller Latin
#' hypercube designs.  [augmentLHS()] to add points to an existing design.
#'
#' @examples
#' set.seed(1234)
#' A <- nestedLHS(small = 3, large = 9, k = 4)
#' # the small design is the first 3 rows of the large design
#' all(A$small == A$large[1:3, ])
nestedLHS <- function(small, large, k)
{
  for (arg in list(small = small, large = large, k = k))
  {
    if (length(arg) != 1)
      stop("small, large, and k may not be vectors")
    if (is.na(arg) | is.infinite(arg))
      stop("small, large, and k may not be infinite, NA, or NaN")
    if (arg != floor(arg) | arg < 1)
      stop("small, large, and k must be positive integers")
  }
  small <- as.integer(small)
  large <- as.integer(large)
  k <- as.integer(k)

  if (large <= small)
    stop("large must be strictly greater than small")
  if (large %% small != 0)
    stop("large must be an integer multiple of small")

  a <- large %/% small
  largeMat <- matrix(0, nrow = large, ncol = k)

  for (j in seq_len(k))
  {
    # choose one fine interval (in 1..large) per coarse interval to host a point
    #   of the small design
    host <- (seq_len(small) - 1L) * a + sample.int(a, small, replace = TRUE)
    # randomly map the small coarse intervals to the first 'small' rows so the
    #   nested design is a random Latin hypercube design
    smallRows <- sample.int(small)
    largeMat[smallRows, j] <- (host - 1 + runif(small)) / large

    # the remaining fine intervals fill the extra rows of the large design so it
    #   is a random Latin hypercube design of 'large' points
    remaining <- setdiff(seq_len(large), host)
    extraRows <- small + sample.int(large - small)
    largeMat[extraRows, j] <- (remaining - 1 + runif(large - small)) / large
  }

  smallMat <- largeMat[seq_len(small), , drop = FALSE]
  return(list(small = smallMat, large = largeMat))
}
