# Copyright 2019 Robert Carnell

context("test-optaugmentlhs")

test_that("optAugmentLHS works", {
  expect_error(optAugmentLHS(randomLHS(10, 4), NA))
  expect_error(optAugmentLHS(randomLHS(10, 4), NaN))
  expect_error(optAugmentLHS(randomLHS(10, 4), Inf))
  expect_error(optAugmentLHS(randomLHS(10, 4), 2, NA))
  expect_error(optAugmentLHS(randomLHS(10, 4), 2, NaN))
  expect_error(optAugmentLHS(randomLHS(10, 4), 2, Inf))

  temp <- randomLHS(10, 4)
  temp[1,1] <- NA
  expect_error(optAugmentLHS(temp, 5))

  temp <- randomLHS(10, 4)
  temp[1,1] <- 2
  expect_error(optAugmentLHS(temp, 5))

  set.seed(1976)
  expect_true(checkLatinHypercube(optAugmentLHS(randomLHS(4, 2), 2)))

  set.seed(1977)
  expect_true(checkLatinHypercube(optAugmentLHS(randomLHS(3, 3), 3, 3)))

  expect_error(optAugmentLHS(c(1,2), m = 4, mult = 2))
  expect_error(optAugmentLHS(randomLHS(10, 4), c(1,2)))
  expect_error(optAugmentLHS(randomLHS(10, 4), -2))

  A <- optAugmentLHS(randomLHS(1,4), 1)
  expect_true(checkLatinHypercube(A))
})
