context("test-maximinlhs")

test_that("maximinLHS works", {
  expect_error(maximinLHS(-1, 2))
  expect_error(maximinLHS(10, -30))
  expect_error(maximinLHS(10, 2, -2))
  expect_error(maximinLHS(NA, 2))
  expect_error(maximinLHS(NaN, 2))
  expect_warning(expect_error(maximinLHS(Inf, 2)))
  expect_error(maximinLHS(10, NA))
  expect_error(maximinLHS(10, NaN))
  expect_warning(expect_error(maximinLHS(10, Inf)))
  expect_error(maximinLHS(10, 2, NA))
  expect_error(maximinLHS(10, 2, NaN))
  expect_warning(expect_error(maximinLHS(10, 2, Inf)))

  set.seed(1976)
  expect_true(checkLatinHypercube(maximinLHS(4, 2)))

  set.seed(1977)
  expect_true(checkLatinHypercube(maximinLHS(3, 3, 5)))
})
