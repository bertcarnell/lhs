#' Transformed Latin hypercube with a multivariate distribution
#'
#' @description
#' A method to create a transformed Latin Hypercube sample where the marginal
#' distributions can be correlated according to an arbitrary set of criteria
#' contained in a minimized cost function
#'
#' @param lhs a Latin hypercube sample that is uniformly distributed on the
#' margins
#' @param marginal_transform_function a function that takes Latin hypercube sample
#' as the first argument and other passed-through variables as desired.  \code{...} must
#' be passed as a argument.  For example, \code{f <- function(W, second_argument, ...)}.
#' Must return a \code{matrix} or \code{data.frame}
#' @param cost_function a function that takes a transformed Latin hypercube sample
#' as the first argument and other passed-through variables as desired.    \code{...} must
#' be passed as a argument.  For example, \code{f <- function(W, second_argument, ...)}
#' @param debug Should debug messages be printed.  Causes cost function output
#' and iterations to be printed to aid in setting the maximum number of iterations
#' @param maxiter the maximum number of iterations.  The algorithm proceeds by
#' swapping one variable of two points at a time.  Each swap is an iteration.
#' @param ... Additional arguments to be passed through to the \code{marginal_transform_function}
#' and \code{cost_function}
#'
#' @return a list of the Latin hypercube with uniform margins, the transformed
#' Latin hypercube, and the final cost
#' @export
#'
#' @examples
#' correlatedLHS(lhs::randomLHS(30, 2),
#'   marginal_transform_function = function(W, ...) {
#'     W[,1] <- qnorm(W[,1], 1, 3)
#'     W[,2] <- qexp(W[,2], 2)
#'     return(W)
#'   },
#'   cost_function = function(W, ...) {
#'     (cor(W[,1], W[,2]) - 0.5)^2
#'   },
#'   debug = FALSE,
#'   maxiter = 1000)
correlatedLHS <- function(lhs, marginal_transform_function,
                          cost_function, debug=FALSE, maxiter=10000,
                          ...) {
  Nlhs <- nrow(lhs)
  k <- ncol(lhs)

  ## Initial transform and cost
  lhs_t <- marginal_transform_function(lhs, ...)
  if (!is.matrix(lhs_t) & !is.data.frame(lhs_t)) {
    stop("The marginal_transform_function should return a matrix or data.frame")
  }
  if (!all(dim(lhs) == dim(lhs_t))) {
    stop("resulting design after transformation with marginal_transform_function must be the same dimension as the original design")
  }

  initial_cost <- cost_function(lhs_t, ...)
  if (!is.numeric(initial_cost) | length(initial_cost) != 1) {
    stop("cost function must return a single cost as a numeric")
  }

  if (debug) {
    cat(paste0("\nInitial cost: ", initial_cost, "\n"))
  }

  best_cost <- initial_cost

  swap <- function(i1, i2, j1, j2, dat) {
    temp <- dat[i1, j1]
    dat[i1, j1] <- dat[i2, j2]
    dat[i2, j2] <- temp
    return(dat)
  }

  iter <- 1
  recent_improvement <- TRUE
  while (best_cost > 0 & iter < maxiter & recent_improvement) {
    recent_improvement <- FALSE
    if (debug && iter > 1) {
      cat(paste0("Iteration ", iter, " with cost: ", best_cost, "\n"))
    }
    for (j in 1:k) {
      if (debug) {
        cat(paste0("\tSwapping on Variable ", j, " of ", k, " on Iteration ", iter, "\n"))
      }
      for (i1 in 1:(Nlhs-1)) {
        for (i2 in i1:Nlhs) {
          if (best_cost > 0) {
            lhs <- swap(i1, i2, j, j, lhs)
            lhs_t <- marginal_transform_function(lhs, ...)
            cost <- cost_function(lhs_t, ...)
            if (cost >= best_cost) {
              # swap back
              lhs <- swap(i2, i1, j, j, lhs)
            } else {
              # stay here and update best
              best_cost <- cost
              recent_improvement <- TRUE
              break
            }
            iter <- iter + 1
            if (best_cost == 0 | iter > maxiter) break
          }
        }
        if (best_cost == 0 | iter > maxiter) break
      }
      if (best_cost == 0 | iter > maxiter) break
    }
  }

  if (debug) {
    cat(paste0("Ending at cost: ", best_cost, "\n"))
    if (!all(apply(lhs, 2, function(x) sum(floor(x*Nlhs)+1)) == Nlhs*(Nlhs+1)/2)) {
      stop("Latin hypercube not created in swapping process")
    }
    if (!all(lhs > 0 & lhs < 1)) {
      stop("Latin hypercube sample outside bounds (0,1)")
    }
  }

  return(list(lhs = lhs,
              transformed_lhs = marginal_transform_function(lhs, ...), # the transform might not have been after swapping back
              cost = best_cost))
}
