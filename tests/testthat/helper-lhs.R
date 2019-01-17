# Copyright 2019 Robert Carnell

checkLatinHypercube <- function(X)
{
  # check that the matrix is a latin hypercube
  g <- function(Y)
  {
    # check that this column contains all the cells
    breakpoints <- seq(0, 1, length = length(Y) + 1)
    h <- hist(Y, plot = FALSE, breaks = breakpoints)
    all(h$counts == 1)
  }
  # check all the columns
  all(apply(X, 2, g))
}

checkOA <- function(X)
{
  # check that the matrix is an orthogonal array
  Y <- t(X) %*% X
  all(abs(Y[upper.tri(Y)]) < 1E-9)
}
