# Copyright 2019 Robert Carnell

context("test-optimumlhs")

test_that("optimumLHS works", {
  expect_error(optimumLHS(-1, 2))
  expect_error(optimumLHS(10, -30))
  expect_error(optimumLHS(10, 2, -2))
  expect_error(optimumLHS(10, 2, 3, -1))
  expect_error(optimumLHS(10, 2, 3, 1.5))
  expect_error(optimumLHS(10, 2, 3, 1))
  expect_error(optimumLHS(10, 2, 3, 0))
  expect_error(optimumLHS(NA, 2))
  expect_error(optimumLHS(NaN, 2))
  expect_warning(expect_error(optimumLHS(Inf, 2)))
  expect_error(optimumLHS(10, NA))
  expect_error(optimumLHS(10, NaN))
  expect_warning(expect_error(optimumLHS(10, Inf)))
  expect_error(optimumLHS(10, 2, NA))
  expect_error(optimumLHS(10, 2, NaN))
  expect_warning(expect_error(optimumLHS(10, 2, Inf)))
  expect_error(optimumLHS(10, 2, 2, NA))
  expect_error(optimumLHS(10, 2, 2, NaN))
  expect_error(optimumLHS(10, 2, 2, Inf))

  set.seed(1976)
  rTemp <- optimumLHS(4, 2)
  expect_true(checkLatinHypercube(rTemp))

  set.seed(1977)
  rTemp <- optimumLHS(3, 3, 5)
  expect_true(checkLatinHypercube(rTemp))

  set.seed(1978)
  rTemp <- optimumLHS(5, 2, 5, .5)
  expect_true(checkLatinHypercube(rTemp))

  set.seed(2010)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j)
      expect_true(checkLatinHypercube(A))
    }
  }

  set.seed(2011)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j, 5)
      expect_true(checkLatinHypercube(A))
    }
  }

  set.seed(2012)
  for (i in 2:6)
  {
    for (j in 2:6)
    {
      A <- optimumLHS(i, j, 5, 0.05)
      expect_true(checkLatinHypercube(A))
    }
  }

  expect_error(.Call("optimumLHS_cpp", 3, 4L, 4L, 0.01, FALSE))
  X <- .Call("optimumLHS_cpp", 1L, 4L, 4L, 0.01, FALSE)
  expect_equal(nrow(X), 1)

  A <- optimumLHS(1, 4)
  expect_equal(nrow(A), 1)
  expect_true(checkLatinHypercube(A))
})
