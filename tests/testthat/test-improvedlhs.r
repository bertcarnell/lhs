# Copyright 2019 Robert Carnell

context("test-improvedlhs")

test_that("improvedLHS works", {
  expect_error(improvedLHS(-1, 2))
  expect_error(improvedLHS(10, -30))
  expect_error(improvedLHS(10, 2, -2))
  expect_error(improvedLHS(NA, 2))
  expect_error(improvedLHS(NaN, 2))
  expect_warning(expect_error(improvedLHS(Inf, 2)))
  expect_error(improvedLHS(10, NA, 2))
  expect_error(improvedLHS(10, NaN, 2))
  expect_warning(expect_error(improvedLHS(10, Inf, 2)))
  expect_error(improvedLHS(10, 2, NA))
  expect_error(improvedLHS(10, 2, NaN))
  expect_warning(expect_error(improvedLHS(10, 2, Inf)))

  set.seed(1976)
  expect_true(checkLatinHypercube(improvedLHS(4, 2)))

  set.seed(1977)
  expect_true(checkLatinHypercube(improvedLHS(3, 3, 5)))

  set.seed(1111)
  A <- improvedLHS(20, 6)
  set.seed(1111)
  B <- improvedLHS(20, 6)
  expect_true(all(A == B))
  D <- improvedLHS(20, 6)
  expect_true(any(A != D))
})

test_that("improvedLHS errors work", {
  expect_error(.Call("improvedLHS_cpp", 3, 4L, 4L))
  X <- .Call("improvedLHS_cpp", 1L, 4L, 4L)
  expect_equal(nrow(X), 1)
})
