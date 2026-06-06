# Copyright 2026 Robert Carnell

#' Create a Latin hypercube design with transformed margins
#'
#' A unified, high-level interface that generates a Latin hypercube sample and
#' transforms each margin to a user supplied distribution, factor, or integer
#' range in a single call, returning a ready to use \code{data.frame}.
#'
#' @details \code{lhs_design} is a convenience wrapper around the design
#' generators ([randomLHS()], [improvedLHS()], [maximinLHS()], [optimumLHS()],
#' [geneticLHS()], and [create_oalhs()]) and the quantile transformations
#' ([qfactor()], [qinteger()], [qdirichlet()]).  The number of columns of the
#' underlying Latin hypercube sample is determined from the \code{variables}
#' specification, the sample is generated using the requested \code{type}, and
#' each margin is transformed and assembled into a named \code{data.frame}.
#'
#' [transform_lhs()] applies the same transformations to an existing Latin
#' hypercube sample (for example one created by [augmentLHS()], [slicedLHS()],
#' or any matrix with values on [0,1]) without generating a new design.
#'
#' Each element of \code{variables} describes one variable and may be one of:
#' \describe{
#'   \item{a function}{a function of a single numeric vector of values on [0,1]
#'   that returns the transformed column, e.g. \code{function(p) qnorm(p, 2, 0.5)}.
#'   It consumes a single column of the Latin hypercube sample.}
#'   \item{a distribution list}{a list with a character element \code{dist}
#'   naming a quantile function (e.g. \code{"qnorm"}) and any further named
#'   arguments passed to that function, e.g.
#'   \code{list(dist = "qnorm", mean = 2, sd = 0.5)}.  It consumes a single
#'   column.}
#'   \item{a factor list}{a list with \code{type = "factor"}, a \code{levels}
#'   vector, and an optional logical \code{ordered} (default \code{FALSE}).  It
#'   consumes a single column and is transformed with [qfactor()].}
#'   \item{an integer list}{a list with \code{type = "integer"} and integer
#'   \code{min} and \code{max} values.  It consumes a single column and is
#'   transformed with [qinteger()].}
#'   \item{a dirichlet list}{a list with \code{type = "dirichlet"} and a numeric
#'   \code{alpha} vector.  It consumes \code{length(alpha)} columns, transforms
#'   them with [qdirichlet()], and produces \code{length(alpha)} output columns
#'   named with the variable name followed by an index.}
#' }
#'
#' @param n the number of rows or samples
#' @param variables a named list describing the marginal transformation of each
#' variable.  See Details for the accepted specifications.  The names become the
#' columns of the returned \code{data.frame}.
#' @param type the type of Latin hypercube sample to generate.  One of
#' \code{"random"}, \code{"improved"}, \code{"maximin"}, \code{"optimum"},
#' \code{"genetic"}, or \code{"oalhs"}.
#' @param ... further arguments passed to the underlying design generator, for
#' example \code{dup} for \code{"improved"} or \code{maxSweeps} for
#' \code{"optimum"}.
#' @return a \code{data.frame} with one column per output variable and values
#' transformed to the requested margins
#' @export
#'
#' @author Rob Carnell
#'
#' @keywords design
#'
#' @seealso [transform_lhs()] to transform an existing design.  [randomLHS()],
#' [improvedLHS()], [maximinLHS()], [optimumLHS()], [geneticLHS()], and
#' [create_oalhs()] for the underlying generators.  [qfactor()], [qinteger()],
#' and [qdirichlet()] for the underlying transformations.
#'
#' @examples
#' set.seed(1234)
#' D <- lhs_design(20, variables = list(
#'   x = list(dist = "qnorm", mean = 2, sd = 0.5),
#'   grp = list(type = "factor", levels = c("a", "b", "c")),
#'   count = list(type = "integer", min = 5L, max = 17L),
#'   z = function(p) qexp(p, rate = 2),
#'   comp = list(type = "dirichlet", alpha = c(2, 3, 4))
#' ), type = "maximin")
#' head(D)
lhs_design <- function(n, variables,
                       type = c("random", "improved", "maximin", "optimum",
                                "genetic", "oalhs"),
                       ...)
{
  type <- match.arg(type)
  if (length(n) != 1 || is.na(n) || is.infinite(n) || n != floor(n) || n < 1)
    stop("n must be a positive integer")
  .lhs_check_variables(variables)

  k <- sum(vapply(variables, .lhs_spec_ncol, integer(1)))

  lhs <- switch(type,
    random   = randomLHS(n, k, ...),
    improved = improvedLHS(n, k, ...),
    maximin  = maximinLHS(n, k, ...),
    optimum  = optimumLHS(n, k, ...),
    genetic  = geneticLHS(n, k, ...),
    oalhs    = .lhs_call_oalhs(n, k, ...))

  transform_lhs(lhs, variables)
}

#' @rdname lhs_design
#'
#' @param lhs a Latin hypercube sample matrix with values on [0,1].  The number
#' of columns must equal the total number of columns consumed by
#' \code{variables}.
#' @export
transform_lhs <- function(lhs, variables)
{
  if (!is.matrix(lhs))
    stop("lhs must be a matrix")
  if (any(is.na(lhs)))
    stop("lhs cannot contain any NA entries")
  if (any(lhs < 0 | lhs > 1))
    stop("lhs must have entries on the interval [0,1]")
  .lhs_check_variables(variables)

  ncols <- vapply(variables, .lhs_spec_ncol, integer(1))
  if (sum(ncols) != ncol(lhs))
    stop(paste0("the number of columns of lhs (", ncol(lhs),
                ") must equal the number of columns required by variables (",
                sum(ncols), ")"))

  out <- list()
  col <- 1L
  for (i in seq_along(variables))
  {
    nm <- names(variables)[i]
    m <- ncols[i]
    idx <- seq.int(col, length.out = m)
    if (m == 1L)
    {
      out[[nm]] <- .lhs_apply_spec(lhs[, idx], variables[[i]])
    } else
    {
      res <- .lhs_apply_spec(lhs[, idx, drop = FALSE], variables[[i]])
      for (jj in seq_len(m))
        out[[paste0(nm, jj)]] <- res[, jj]
    }
    col <- col + m
  }

  data.frame(out, stringsAsFactors = FALSE, check.names = FALSE)
}

# Validate the variables list shared by lhs_design and transform_lhs
.lhs_check_variables <- function(variables)
{
  if (!is.list(variables) || length(variables) == 0)
    stop("variables must be a non-empty list")
  nm <- names(variables)
  if (is.null(nm) || any(!nzchar(nm)))
    stop("every element of variables must be named")
  if (anyDuplicated(nm))
    stop("the names of variables must be unique")
  invisible(TRUE)
}

# Number of Latin hypercube columns consumed by a single variable specification
.lhs_spec_ncol <- function(spec)
{
  if (is.function(spec))
    return(1L)
  if (is.list(spec))
  {
    if (identical(spec$type, "dirichlet"))
    {
      if (is.null(spec$alpha))
        stop("a dirichlet specification must include 'alpha'")
      return(length(spec$alpha))
    }
    return(1L)
  }
  stop("each variable specification must be a function or a list")
}

# Apply a single variable specification to one or more columns of an LHS
.lhs_apply_spec <- function(x, spec)
{
  if (is.function(spec))
    return(spec(x))

  type <- spec$type
  if (!is.null(type) && type == "factor")
  {
    if (is.null(spec$levels))
      stop("a factor specification must include 'levels'")
    fact <- factor(spec$levels, levels = spec$levels,
                   ordered = isTRUE(spec$ordered))
    return(qfactor(x, fact))
  }
  if (!is.null(type) && type == "integer")
  {
    if (is.null(spec$min) || is.null(spec$max))
      stop("an integer specification must include 'min' and 'max'")
    return(qinteger(x, spec$min, spec$max))
  }
  if (!is.null(type) && type == "dirichlet")
    return(qdirichlet(x, spec$alpha))
  if (!is.null(spec$dist))
  {
    fn <- match.fun(spec$dist)
    args <- spec[setdiff(names(spec), "dist")]
    return(do.call(fn, c(list(x), args)))
  }
  stop("unrecognized variable specification")
}

# Call create_oalhs supplying defaults for its required flags
.lhs_call_oalhs <- function(n, k, ...)
{
  args <- list(...)
  if (is.null(args$bChooseLargerDesign))
    args$bChooseLargerDesign <- TRUE
  if (is.null(args$bverbose))
    args$bverbose <- FALSE
  do.call(create_oalhs, c(list(n, k), args))
}
