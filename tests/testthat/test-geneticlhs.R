# Copyright 2019 Robert Carnell

context("test-geneticlhs")

test_that("geneticLHS works", {
  expect_error(geneticLHS(-1, 2))
  expect_error(geneticLHS(10, -30))
  expect_error(geneticLHS(10, 2, -2))
  expect_error(geneticLHS(NA, 2))
  expect_error(geneticLHS(NaN, 2))
  expect_warning(expect_error(geneticLHS(Inf, 2)))
  expect_error(geneticLHS(10, NA))
  expect_error(geneticLHS(10, NaN))
  expect_warning(expect_error(geneticLHS(10, Inf)))
  expect_error(geneticLHS(10, 2, NA))
  expect_error(geneticLHS(10, 2, NaN))
  expect_warning(expect_error(geneticLHS(10, 2, Inf)))

  set.seed(1976)
  expect_true(checkLatinHypercube(geneticLHS(4, 2)))

  set.seed(1977)
  expect_true(checkLatinHypercube(geneticLHS(3, 3, 6)))

  expect_error(geneticLHS(10, 2, 4, -1))
  expect_error(geneticLHS(10, 2, 4, 4, -.1))
  expect_error(geneticLHS(10, 2, 4, 4, 1.1))
  expect_error(geneticLHS(10, 2, 2, NA))
  expect_error(geneticLHS(10, 2, 2, NaN))
  expect_warning(expect_error(geneticLHS(10, 2, 2, Inf)))

  #expect_error(geneticLHS(10, 2, 2, 4, NA))
  #expect_error(geneticLHS(10, 2, 2, 4, NaN))

  expect_error(geneticLHS(10, 2, 2, 4, Inf))

  set.seed(1976)
  expect_true(checkLatinHypercube(geneticLHS(20, 5, pop = 100, gen = 4,
                                             pMut = 0.2, criterium = "S")))

  capture_output(X <- .Call("geneticLHS_cpp", 1L, 4L, 10L, 4L, 0.01, "S", TRUE))
  expect_equal(nrow(X), 1)

  A <- geneticLHS(1, 4)
  expect_equal(nrow(A), 1)
  expect_true(checkLatinHypercube(A))
})
