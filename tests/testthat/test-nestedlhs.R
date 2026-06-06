# Copyright 2026 Robert Carnell

context("test-nestedlhs")

test_that("nestedLHS works", {
  set.seed(1234)
  small <- 4
  large <- 12
  k <- 5
  A <- nestedLHS(small, large, k)

  # structure and dimensions
  expect_named(A, c("small", "large"))
  expect_equal(nrow(A$small), small)
  expect_equal(nrow(A$large), large)
  expect_equal(ncol(A$small), k)
  expect_equal(ncol(A$large), k)

  # both designs are Latin hypercube designs
  expect_true(checkLatinHypercube(A$small))
  expect_true(checkLatinHypercube(A$large))

  # the small design is a subset of the large design
  expect_equal(A$small, A$large[seq_len(small), , drop = FALSE])

  # works when large is a larger multiple of small
  set.seed(5678)
  B <- nestedLHS(3, 9, 4)
  expect_true(checkLatinHypercube(B$small))
  expect_true(checkLatinHypercube(B$large))
  expect_equal(B$small, B$large[1:3, , drop = FALSE])

  # a single nested point and a single column
  set.seed(9012)
  C <- nestedLHS(1, 5, 1)
  expect_true(checkLatinHypercube(C$small))
  expect_true(checkLatinHypercube(C$large))

  # test exceptions
  expect_error(nestedLHS(c(2, 3), 6, 3))
  expect_error(nestedLHS(2, NA, 3))
  expect_error(nestedLHS(2, Inf, 3))
  expect_error(nestedLHS(2, 6, NaN))
  expect_error(nestedLHS(-1, 6, 3))
  expect_error(nestedLHS(2.2, 6, 3))
  # large must be strictly greater than small
  expect_error(nestedLHS(5, 5, 3))
  # large must be an integer multiple of small
  expect_error(nestedLHS(4, 10, 3))
})
