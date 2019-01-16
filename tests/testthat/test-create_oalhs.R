context("test-create_oalhs")

test_that("create_oalhs works", {
  oalhs <- create_oalhs(9, 4, TRUE, FALSE)
  expect_true(checkLatinHypercube(oalhs))
  expect_equal(nrow(oalhs), 9)
  expect_equal(ncol(oalhs), 4)

  # ask for an achievable design
  oalhs <- create_oalhs(4, 2, TRUE, FALSE)
  expect_true(checkLatinHypercube(oalhs))
  expect_equal(nrow(oalhs), 4)
  expect_equal(ncol(oalhs), 2)

  # ask for a design that needs more rows
  oalhs <- create_oalhs(20, 3, TRUE, FALSE)
  expect_true(checkLatinHypercube(oalhs))
  expect_equal(nrow(oalhs), 25)
  expect_equal(ncol(oalhs), 3)

  # ask for a design but ask for less rows
  oalhs <- create_oalhs(20, 3, FALSE, FALSE)
  expect_true(checkLatinHypercube(oalhs))
  expect_equal(nrow(oalhs), 18)
  expect_equal(ncol(oalhs), 3)

  oalhs <- create_oalhs(20, 10, TRUE, FALSE)
  expect_true(checkLatinHypercube(oalhs))
  expect_equal(nrow(oalhs), 54)
  expect_equal(ncol(oalhs), 10)

  # check repeatability
  set.seed(1001)
  X <- create_oalhs(9, 4, TRUE, FALSE)
  set.seed(1001)
  Y <- create_oalhs(9, 4, TRUE, FALSE)
  expect_true(all(X == Y))

})
