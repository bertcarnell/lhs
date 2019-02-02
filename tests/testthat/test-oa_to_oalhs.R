# Copyright 2019 Robert Carnell

context("test-oa_to_oalhs")

test_that("oa_to_oalhs works with internal oa generation", {
  oa <- createBose(3, 4, TRUE)
  oalhs <- oa_to_oalhs(9, 4, oa)
  expect_true(checkLatinHypercube(oalhs))

  oa <- createBose(3, 4, FALSE)
  oalhs <- oa_to_oalhs(9, 4, oa)
  expect_true(checkLatinHypercube(oalhs))

  oa <- createBoseBush(8, 5, TRUE)
  oalhs <- oa_to_oalhs(128, 5, oa)
  expect_true(checkLatinHypercube(oalhs))

  # check a mismatch in n causes an error
  expect_error(oa_to_oalhs(3, 5, oa))
  # check a mismatch in k causes an error
  expect_error(oa_to_oalhs(128, 8, oa))
  # check a wrong sized oa causes an error
  expect_error(oa_to_oalhs(128, 5, oa[1:100,1:3]))
  # check wrong type
  expect_error(oa_to_oalhs(3, 5, matrix(1.2, nrow = 3, ncol = 5)))

  oa <- createAddelKemp(3, 4, FALSE)
  oalhs <- oa_to_oalhs(18, 4, oa)
  expect_true(checkLatinHypercube(oalhs))

  oa <- createAddelKemp3(4, 20, TRUE)
  oalhs <- oa_to_oalhs(128, 20, oa)
  expect_true(checkLatinHypercube(oalhs))

  expect_error(.Call("oa_to_lhs", 4, 20L, oa, FALSE))
  expect_error(.Call("oa_to_lhs", 4L, 20L, oa, 5))
  expect_error(.Call("oa_to_lhs", as.integer(NA), 20L, oa, FALSE))

})

test_that("oa_to_oalhs works with DoE.base", {
  # note:  trying to ensure that a lack of DoE.base does not break the tests
  # also trying to avoid attaching the DoE.base package because it causes warnings in the test suite
  testthat::skip_if_not_installed("DoE.base")

  # 12 rows, two columns of 1,2 and one column of 1:6
  my_oa <- DoE.base::oa.design(ID = DoE.base::L12.2.2.6.1)
  oalhs <- oa_to_oalhs(12, 3, my_oa)
  expect_true(checkLatinHypercube(oalhs))

  # 20 rows, 19 columns of 1,2
  my_oa <- DoE.base::oa.design(ID = DoE.base::L20.2.19)
  oalhs <- oa_to_oalhs(20, 19, my_oa)
  expect_true(checkLatinHypercube(oalhs))

  # can I get the oa back?
  #c(ifelse(floor(oalhs*20) < 20/2, 1, 2)) == as.integer(as.matrix(my_oa))

  # can I verify that the oalhs is an oa?
  temp <- t(ifelse(floor(oalhs*20) < 20/2, -1, 1)) %*% ifelse(floor(oalhs*20) < 20/2, -1, 1)
  expect_true(all(temp[upper.tri(temp)] == 0))

  # 20 rows, 19 columns of 1,2
  my_oa <- DoE.base::oa.design(ID = DoE.base::L9.3.4)
  oalhs <- oa_to_oalhs(9, 4, my_oa)
  expect_true(checkLatinHypercube(oalhs))

  # can I verify that the oalhs is an oa?
  temp1 <- ifelse(floor(oalhs*9) < 9/3, -1, ifelse(floor(oalhs*9) < 2*9/3, 0, 1))
  temp <- t(temp1) %*% temp1
  expect_true(all(temp[upper.tri(temp)] == 0))
})

test_that("Edge cases", {
  A <- matrix(1L, nrow = 1, ncol = 4)
  B <- oa_to_oalhs(1, 4, A)
  expect_equal(nrow(B), 1)
  expect_true(checkLatinHypercube(B))
})
