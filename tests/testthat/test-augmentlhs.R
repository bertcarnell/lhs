context("test-augmentlhs")

test_that("augment works", {
  expect_error(augmentLHS(randomLHS(10, 4), NA))
  expect_error(augmentLHS(randomLHS(10, 4), NaN))
  expect_error(augmentLHS(randomLHS(10, 4), Inf))

  set.seed(1976)
  temp <- randomLHS(10, 4)
  temp[1,1] <- NA
  expect_error(augmentLHS(temp, 5))

  set.seed(1976)
  temp <- randomLHS(10, 4)
  temp[1,1] <- 2
  expect_error(augmentLHS(temp, 5))

  set.seed(1976)
  expect_true(checkLatinHypercube(augmentLHS(randomLHS(4, 2), 4)))

  set.seed(1977)
  expect_true(checkLatinHypercube(augmentLHS(randomLHS(3, 3), 3)))

  set.seed(1977)
  expect_true(checkLatinHypercube(augmentLHS(randomLHS(4, 1), 2)))

  # this test addresses a bug where an error ocurred on adding 1 row in
  #   augmentLHS
  temp <- randomLHS(7, 2)
  temp <- augmentLHS(temp, 1)
  expect_equal(nrow(temp), 8)

  expect_true(checkLatinHypercube(augmentLHS(randomLHS(7, 2), 7)))
  expect_true(checkLatinHypercube(augmentLHS(randomLHS(10, 5), 10)))
})
