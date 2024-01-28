# Copyright 2023 Robert Carnell

#' Quantile Transformations
#'
#' A collection of functions that transform the margins of a Latin hypercube
#' sample in non-standard ways
#'
#' \code{qdirichlet} is not an exact quantile function since the quantile of a
#' multivariate distribution is not unique.  \code{qdirichlet} is also not the independent quantiles of the marginal distributions since
#' those quantiles do not sum to one.  \code{qdirichlet} is the quantile of the underlying gamma functions, normalized.
#' This has been tested to show that \code{qdirichlet} approximates the Dirichlet distribution well and creates the correct marginal means and variances
#' when using a Latin hypercube sample
#'
#' @rdname quanttrans
#'
#' @param p a vector of LHS samples on (0,1)
#' @param fact a factor or categorical variable.  Ordered and un-ordered variables are allowed.
#' @param a a minimum integer
#' @param b a maximum integer
#' @param X multiple columns of an LHS sample on (0,1)
#' @param alpha Dirichlet distribution parameters.  All \code{alpha >= 1} The marginal
#' mean probability of the Dirichlet distribution is given by \code{alpha[i] / sum(alpha)}
#'
#' @return the transformed column or columns
#' @export
#'
#' @examples
#' X <- randomLHS(20, 6)
#' Y <- X
#' Y[,1] <- qnorm(X[,1], 2, 0.5)
#' Y[,2] <- q_factor(X[,2], factor(LETTERS[c(1,3,5,7,8)]))
#' Y[,3] <- q_integer(X[,3], 5, 17)
#' Y[,4:6] <- q_dirichlet(X[,4:6], c(2,3,4))
q_factor <- function(p, fact)
{
  stopifnot(is.factor(fact))
  stopifnot(is.numeric(p))
  stopifnot(p >= 0 & p <= 1)

  nlev <- nlevels(fact)

  cut(p, breaks = (0:nlev) / nlev, labels = levels(fact))
}

#' @rdname quanttrans
#'
#' @export
q_integer <- function(p, a, b)
{
  stopifnot(is.numeric(p))
  stopifnot(p >= 0 & p <= 1)
  stopifnot(as.integer(a) == a)
  stopifnot(as.integer(b) == b)

  floor(p*(b - a + 1)) + a
}

#' @rdname quanttrans
#' @importFrom stats qgamma
#'
#' @export
q_dirichlet <- function(X, alpha)
{
  lena <- length(alpha)
  stopifnot(is.matrix(X))
  sims <- dim(X)[1]
  stopifnot(dim(X)[2] == lena)
  if(any(is.na(alpha)) || any(is.na(X)))
    stop("NA values not allowed in qdirichlet")

  Y <- matrix(0, nrow=sims, ncol=lena)
  ind <- which(alpha != 0)
  for(i in ind)
  {
    Y[,i] <- stats::qgamma(X[,i], alpha[i], 1)
  }
  Y <- Y / rowSums(Y)
  return(Y)
}
