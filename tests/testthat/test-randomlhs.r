# Copyright 2019 Robert Carnell

context("test-randomlhs")

test_that("randomLHS works", {
  A <- randomLHS(4,2)
  expect_true(all(A > 0 & A < 1))
  expect_equal(4, nrow(A))
  expect_equal(2, ncol(A))
  expect_true(checkLatinHypercube(A))

  # doubles are truncated in n and k
  A <- randomLHS(4.4, 2)
  expect_true(all(A > 0 & A < 1))
  expect_equal(4, nrow(A))
  expect_equal(2, ncol(A))
  expect_true(checkLatinHypercube(A))

  A <- randomLHS(4, 2.8)
  expect_true(all(A > 0 & A < 1))
  expect_equal(4, nrow(A))
  expect_equal(2, ncol(A))
  expect_true(checkLatinHypercube(A))

  A <- randomLHS(4.4, 2.8)
  expect_true(all(A > 0 & A < 1))
  expect_equal(4, nrow(A))
  expect_equal(2, ncol(A))
  expect_true(checkLatinHypercube(A))

  expect_error(randomLHS(-1, 2))
  expect_error(randomLHS(10, -30))
  expect_error(randomLHS(NA, 2))
  expect_error(randomLHS(NaN, 2))
  expect_warning(expect_error(randomLHS(Inf, 2)))
  expect_error(randomLHS(10, NA))
  expect_error(randomLHS(10, NaN))
  expect_warning(expect_error(randomLHS(10, Inf)))

  A <- randomLHS(1, 5)
  expect_equal(1, nrow(A))
  expect_equal(5, ncol(A))
  expect_true(all(A == 1))

  expect_error(randomLHS(c(1,2,3), c(3,4)))

  expect_error(randomLHS(-1, 2, preserveDraw = TRUE))
  expect_error(randomLHS(10, -30, preserveDraw = TRUE))
  expect_error(randomLHS(NA, 2, preserveDraw = TRUE))
  expect_error(randomLHS(NaN, 2, preserveDraw = TRUE))
  expect_warning(expect_error(randomLHS(Inf, 2, preserveDraw = TRUE)))
  expect_error(randomLHS(10, NA, preserveDraw = TRUE))
  expect_error(randomLHS(10, NaN, preserveDraw = TRUE))
  expect_warning(expect_error(randomLHS(10, Inf, preserveDraw = TRUE)))

  A <- randomLHS(4, 2, preserveDraw = TRUE)
  expect_true(all(A > 0 & A < 1))
  expect_true(checkLatinHypercube(A))

  set.seed(4)
  A <- randomLHS(5, 3, preserveDraw = TRUE)
  set.seed(4)
  B <- randomLHS(5, 5, preserveDraw = TRUE)
  expect_equal(A, B[,1:3], tolerance = 1E-12)
  expect_true(checkLatinHypercube(A))
  expect_true(checkLatinHypercube(B))
})
