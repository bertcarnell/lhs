# Copyright 2019 Robert Carnell

context("test-optseededlhs")

test_that("optseededLHS works", {
  expect_error(optSeededLHS(randomLHS(10, 4), NA))
  expect_error(optSeededLHS(randomLHS(10, 4), NaN))
  expect_error(optSeededLHS(randomLHS(10, 4), Inf))
  expect_error(optSeededLHS(randomLHS(10, 4), 2, NA))
  expect_error(optSeededLHS(randomLHS(10, 4), 2, NaN))
  expect_warning(expect_error(optSeededLHS(randomLHS(10, 4), 2, Inf)))
  expect_error(optSeededLHS(randomLHS(10, 4), 2, 5, NA))
  expect_error(optSeededLHS(randomLHS(10, 4), 2, 5, NaN))
  expect_error(optSeededLHS(randomLHS(10, 4), 2, 5, Inf))

  temp <- randomLHS(10, 4)
  temp[1,1] <- NA
  expect_error(optSeededLHS(temp, 5))

  temp <- randomLHS(10, 4)
  temp[1,1] <- 2
  expect_error(optSeededLHS(temp, 5))

  set.seed(1976)
  A <- optSeededLHS(randomLHS(4, 2), 2)
  expect_true(checkLatinHypercube(A))

  set.seed(1977)
  B <- optSeededLHS(randomLHS(3, 3), 3, 3, .05)
  expect_true(checkLatinHypercube(B))

  A <- optSeededLHS(randomLHS(10, 4), m = 0)
  expect_true(checkLatinHypercube(A))

  expect_error(.Call("optSeededLHS_cpp", 3, 4L, 4L, 0.01, matrix(1L, 2, 2), FALSE))
  X <- .Call("optSeededLHS_cpp", 1L, 4L, 4L, 0.01, matrix(1L, 2, 2), FALSE)
  expect_equal(nrow(X), 1)
  expect_error(.Call("optSeededLHS_cpp", 3L, 4L, 4L, 0.01, matrix(1L, 2, 2), FALSE))
})
