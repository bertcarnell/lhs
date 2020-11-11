# Copyright 2019 Robert Carnell

context("test-createoa")

test_that("createBose works", {
  B <- createBose(2, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 2L)))

  B <- createBose(3, 4, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBose(3, 3)
  expect_equal(nrow(B), 3^2)
  expect_equal(ncol(B), 3)

  B <- createBose(3, 4)
  expect_equal(nrow(B), 3^2)
  expect_equal(ncol(B), 4)

  B <- createBose(5, 4)
  expect_equal(nrow(B), 5^2)
  expect_equal(ncol(B), 4)

  expect_error(.Call("oa_type1", "bose", 3, 3L, FALSE))
  expect_error(.Call("oa_type1", 0, 3L, 3L, FALSE))
  expect_error(.Call("oa_type1", "bose", c(3L, 4L), 3L, FALSE))
  expect_error(.Call("oa_type1", "bose", as.integer(NA), 3L, FALSE))
  expect_error(.Call("oa_type1", "bob", 3L, 3L, FALSE))
})

test_that("createBoseBush works", {
  B <- createBoseBush(2, 4, FALSE)
  expect_true(checkOA(encodeOA(B, 2L)))

  B <- createBoseBush(4, 8, FALSE)
  expect_true(checkOA(encodeOA(B, 4L)))

  B <- createBoseBush(4, 5)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 5)

  B <- createBoseBush(4, 4)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 4)

  B <- createBoseBush(8, 3)
  expect_equal(nrow(B), 2*8^2)
  expect_equal(ncol(B), 3)

  expect_warning({
    B <- createBoseBush(8, 17)
  })
  expect_equal(nrow(B), 2*8^2)
  expect_equal(ncol(B), 17)
  expect_true(checkOA(encodeOA(B, 8L)))

  expect_error({
    B <- createBoseBush(8, 18)
  })
})

test_that("createBush works", {
  B <- createBush(3, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBush(4, 5, FALSE)
  expect_true(checkOA(encodeOA(B, 4L)))

  B <- createBush(3, 3)
  expect_equal(nrow(B), 3^3)
  expect_equal(ncol(B), 3)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBush(3, 4)
  expect_equal(nrow(B), 3^3)
  expect_equal(ncol(B), 4)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBush(5, 4)
  expect_equal(nrow(B), 5^3)
  expect_equal(ncol(B), 4)
  expect_true(checkOA(encodeOA(B, 5L)))

  expect_warning({
    B <- createBush(2, 3)
  })
  expect_equal(nrow(B), 2^3)
  expect_equal(ncol(B), 3)
  expect_true(checkOA(encodeOA(B, 2L)))

  expect_error({
    B <- createBush(2, 4)
  })
})

test_that("createAddelKemp works", {
  B <- createAddelKemp(2, 4, FALSE)
  expect_true(checkOA(encodeOA(B, 2L)))

  B <- createAddelKemp(3, 6, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createAddelKemp(4, 5)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 5)

  B <- createAddelKemp(4, 4)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 4)

  B <- createAddelKemp(5, 3)
  expect_equal(nrow(B), 2*5^2)
  expect_equal(ncol(B), 3)

  expect_warning({
    B <- createAddelKemp(q = 3^1, ncol = 2*3 + 1, bRandom = FALSE)
  }, regexp = "Warning:")
  expect_true(checkOA(encodeOA(B, 3L)))
  expect_equal(7, ncol(B))
  expect_equal(18, nrow(B))
})

test_that("createAddelKemp3 works", {
  B <- createAddelKemp3(2, 13, FALSE)
  expect_true(checkOA(encodeOA(B, 2L)))

  B <- createAddelKemp3(3, 25, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createAddelKemp3(4, 5)
  expect_equal(nrow(B), 2*4^3)
  expect_equal(ncol(B), 5)

  B <- createAddelKemp3(4, 4)
  expect_equal(nrow(B), 2*4^3)
  expect_equal(ncol(B), 4)

  B <- createAddelKemp3(5, 3)
  expect_equal(nrow(B), 2*5^3)
  expect_equal(ncol(B), 3)
})

test_that("createBusht works", {
  B <- createBusht(3, 4, 2, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBusht(3, 4, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  expect_error(.Call("oa_type2", "busht", 3, 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", 0, 3L, 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "busht", c(3L, 4L), 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "busht", as.integer(NA), 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "bosebushl", as.integer(NA), 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "addelkempn", as.integer(NA), 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "bob", as.integer(NA), 4L, 3L, FALSE))
  expect_error(.Call("oa_type2", "bob", 3L, 4L, 3L, FALSE))
  X <- .Call("oa_type2", "busht", 3L, 4L, 3L, TRUE)
  expect_equal(nrow(X), 64)
})

test_that("createBoseBushl works", {
  B <- createBoseBushl(3, 5, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createBoseBushl(4, 4, 16, FALSE)
  expect_true(checkOA(encodeOA(B, 4L)))

  B <- createBoseBushl(q = 2^2, ncol = 2*2^2, lambda = 2, bRandom = FALSE)
  expect_true(checkOA(encodeOA(B, 4L)))

  expect_warning({
    B <- createBoseBushl(q = 2^2, ncol = 2*2^2 + 1, lambda = 2, bRandom = FALSE)
  }, regexp = "Warning:")
  expect_true(checkOA(encodeOA(B, 4L)))
  expect_equal(9, ncol(B))
  expect_equal(32, nrow(B))

  expect_warning({
    B <- createBoseBushl(q = 3^1, ncol = 3*3 + 1, lambda = 3, bRandom = FALSE)
  }, regexp = "Warning:")
  expect_true(checkOA(encodeOA(B, 3L)))
  expect_equal(10, ncol(B))
  expect_equal(27, nrow(B))
})

test_that("createAddelKempN works", {
  B <- createAddelKempN(2, 3, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 2L)))

  B <- createAddelKempN(3, 4, 4, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  # These two tests were failing prior to lhs 1.1
  B <- createAddelKempN(3, 5, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))

  B <- createAddelKempN(3, 25, 3, FALSE)
  expect_true(checkOA(encodeOA(B, 3L)))
})
