# Copyright 2026 Robert Carnell

#' Construct a sliced Latin hypercube design
#'
#' Constructs a Latin hypercube design that can be partitioned into a number of
#' equally sized slices, each of which is itself a Latin hypercube design, while
#' the union of the slices is also a Latin hypercube design.
#'
#' @details A sliced Latin hypercube design (Qian, 2012) is composed of \code{t}
#' slices, each containing \code{m} points in \code{k} columns.  Each slice is a
#' Latin hypercube design of \code{m} points, and the combined \eqn{n = m \times t}{n = m*t}
#' points form a Latin hypercube design of \code{n} points.  Sliced designs are
#' useful for computer experiments that contain both quantitative and qualitative
#' factors (one slice per combination of the qualitative factors) and for
#' collecting data in batches while preserving the \emph{latin} properties of the
#' combined design.
#'
#' The design is constructed one column at a time.  Each of the \code{m} coarse
#' intervals of width \eqn{1/m} is divided into \code{t} fine intervals of width
#' \eqn{1/n}.  Within each coarse interval the \code{t} fine intervals are randomly
#' assigned to the \code{t} slices.  As a result the union of the slices uses each
#' fine interval exactly once (a Latin hypercube design of \code{n}) while each
#' slice uses each coarse interval exactly once (a Latin hypercube design of
#' \code{m}).  A uniform value is then drawn from each assigned interval.
#'
#' @param m the number of points (rows) in each slice
#' @param t the number of slices
#' @param k the number of columns or parameters/variables
#' @return a sliced Latin hypercube sample with \code{m*t} rows and \code{k}
#' columns and values uniformly distributed on [0,1].  The returned matrix has an
#' integer attribute \code{"slices"} of length \code{m*t} that gives the slice
#' membership (1\ldots\code{t}) of each row.
#' @export
#' @importFrom stats runif
#'
#' @author Rob Carnell
#' @references
#' Qian, P. Z. G. (2012) Sliced Latin Hypercube Designs. \emph{Journal of the
#' American Statistical Association}. \bold{107}, 393--399.
#'
#' @keywords design
#'
#' @seealso [randomLHS()], [geneticLHS()], [improvedLHS()], [maximinLHS()],
#' and [optimumLHS()] to generate Latin Hypercube Samples.  [nestedLHS()] to
#' generate a Latin hypercube design that contains a smaller Latin hypercube
#' design as a subset.
#'
#' @examples
#' set.seed(1234)
#' A <- slicedLHS(m = 3, t = 2, k = 4)
#' # the slice membership of each of the 6 rows
#' attr(A, "slices")
slicedLHS <- function(m, t, k)
{
  for (arg in list(m = m, t = t, k = k))
  {
    if (length(arg) != 1)
      stop("m, t, and k may not be vectors")
    if (is.na(arg) | is.infinite(arg))
      stop("m, t, and k may not be infinite, NA, or NaN")
    if (arg != floor(arg) | arg < 1)
      stop("m, t, and k must be positive integers")
  }
  m <- as.integer(m)
  t <- as.integer(t)
  k <- as.integer(k)

  n <- m * t
  result <- matrix(0, nrow = n, ncol = k)

  for (j in seq_len(k))
  {
    # fine[l, s] is the fine interval (in 1..n) assigned to slice s within coarse
    #   interval l.  Within each coarse interval the t fine intervals are randomly
    #   distributed across the t slices.
    fine <- matrix(0L, nrow = m, ncol = t)
    for (l in seq_len(m))
      fine[l, ] <- (l - 1L) * t + sample.int(t)

    for (s in seq_len(t))
    {
      # within a slice randomly assign the m coarse intervals to the m rows so
      #   that each slice is itself a random Latin hypercube design
      rowperm <- sample.int(m)
      rows <- (s - 1L) * m + rowperm
      result[rows, j] <- (fine[, s] - 1 + runif(m)) / n
    }
  }

  attr(result, "slices") <- rep(seq_len(t), each = m)
  return(result)
}
