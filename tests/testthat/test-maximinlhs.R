# Copyright 2019 Robert Carnell

context("test-maximinlhs")

test_that("maximinLHS works", {
  expect_error(maximinLHS(-1, 2))
  expect_error(maximinLHS(10, -30))
  expect_error(maximinLHS(10, 2, dup = -2))
  expect_error(maximinLHS(NA, 2))
  expect_error(maximinLHS(NaN, 2))
  expect_warning(expect_error(maximinLHS(Inf, 2)))
  expect_error(maximinLHS(10, NA))
  expect_error(maximinLHS(10, NaN))
  expect_warning(expect_error(maximinLHS(10, Inf)))
  expect_error(maximinLHS(10, 2, dup = NA))
  expect_error(maximinLHS(10, 2, dup = NaN))
  expect_warning(expect_error(maximinLHS(10, 2, dup = Inf)))

  set.seed(1976)
  expect_true(checkLatinHypercube(maximinLHS(4, 2)))

  set.seed(1977)
  expect_true(checkLatinHypercube(maximinLHS(3, 3, dup = 5)))

  expect_error(maximinLHS(10, 4, method = "none"))
  expect_error(maximinLHS(10, 4, method = "build", optimize.on = "none"))
  expect_warning(maximinLHS(10, 4, method = "build", optimize.on = "result"))
  expect_error(maximinLHS(10, c(4,5), method = "iterative"))
  expect_error(maximinLHS(10, NA, method = "iterative"))
  expect_error(maximinLHS(10, Inf, method = "iterative"))
  expect_error(maximinLHS(12.2, 4, method = "iterative"))
  expect_error(maximinLHS(12, 4.3, method = "iterative"))
  expect_error(maximinLHS(12, 4, dup = 10.2, method = "iterative"))

  A <- maximinLHS(12, 4, dup = 10, method = "iterative", optimize.on = "result")
  expect_true(checkLatinHypercube(A))
  A <- maximinLHS(20, 5, dup = 3, method = "iterative", optimize.on = "grid")
  expect_true(checkLatinHypercube(A))
})

test_that("maximinLHS works with expanded capability", {
  expect_true(checkLatinHypercube(maximinLHS(4, 3, method = "build", dup = 2)))
  expect_true(checkLatinHypercube(maximinLHS(4, 3, method = "iterative", eps = 0.05, maxIter = 100, optimize.on = "grid")))
  expect_true(checkLatinHypercube(maximinLHS(4, 3, method = "iterative", eps = 0.05, maxIter = 100, optimize.on = "result")))
})
