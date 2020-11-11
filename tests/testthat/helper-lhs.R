# Copyright 2019 Robert Carnell

checkLatinHypercube <- function(X)
{
  if (any(apply(X, 2, min) <= 0))
    return(FALSE)
  if (any(apply(X, 2, max) >= 1))
    return(FALSE)
  if (any(is.na(X)))
    return(FALSE)
  # check that the matrix is a latin hypercube
  g <- function(Y)
  {
    # check that this column contains all the cells
    breakpoints <- seq(0, 1, length = length(Y) + 1)
    h <- hist(Y, plot = FALSE, breaks = breakpoints)
    all(h$counts == 1)
  }
  # check all the columns
  return(all(apply(X, 2, g)))
}

checkOA <- function(X)
{
  # check that the matrix is an orthogonal array
  Y <- t(X) %*% X
  all(abs(Y[upper.tri(Y)]) < 1E-9)
}

encodeOA <- function(X, n)
{
  assertthat::assert_that(n > 1 & is.integer(n),
                          msg = "n must be an integer > 1")
  if (n == 2)
  {
    # 0, 1 => -1, 1
    X <- X*2 - 1
  } else if (n == 3)
  {
    # 0, 1, 2 => -1, 0, 1
    X <- X - 1
  } else if (n == 4)
  {
    # 0, 1, 2, 3 => -1, -1/3, 1/3, 1
    X <- X * 2 / 3 - 1
  } else if (n > 4)
  {
    X <- X * 2 / (n - 1) - 1
  }
  return(X)
}
