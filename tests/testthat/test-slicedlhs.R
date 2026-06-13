# Copyright 2026 Robert Carnell

context("test-slicedlhs")

test_that("slicedLHS works", {
  set.seed(1234)
  m <- 4
  t <- 3
  k <- 5
  A <- slicedLHS(m, t, k)

  # dimensions
  expect_equal(nrow(A), m * t)
  expect_equal(ncol(A), k)

  # slice membership attribute
  expect_equal(attr(A, "slices"), rep(1:t, each = m))

  # the union of all slices is a Latin hypercube design
  expect_true(checkLatinHypercube(A))

  # each slice is itself a Latin hypercube design
  slices <- attr(A, "slices")
  for (s in seq_len(t)) {
    expect_true(checkLatinHypercube(A[slices == s, ]))
  }

  # a single slice reduces to a random Latin hypercube
  set.seed(5678)
  B <- slicedLHS(5, 1, 3)
  expect_equal(nrow(B), 5)
  expect_true(checkLatinHypercube(B))

  # a single point per slice
  set.seed(9012)
  C <- slicedLHS(1, 4, 2)
  expect_equal(nrow(C), 4)
  expect_true(checkLatinHypercube(C))

  # test exceptions
  expect_error(slicedLHS(c(2, 3), 2, 3))
  expect_error(slicedLHS(2, NA, 3))
  expect_error(slicedLHS(2, Inf, 3))
  expect_error(slicedLHS(2, 2, NaN))
  expect_error(slicedLHS(-1, 2, 3))
  expect_error(slicedLHS(2.2, 2, 3))
  expect_error(slicedLHS(2, 0, 3))
})
