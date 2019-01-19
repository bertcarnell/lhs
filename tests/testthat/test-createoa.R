# Copyright 2019 Robert Carnell

context("test-createoa")

test_that("createBose works", {
  B <- createBose(2, 3, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  expect_true(checkOA(B))

  B <- createBose(3, 4, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

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
  B[which(B == 0, arr.ind = TRUE)] <- -1
  expect_true(checkOA(B))

  B <- createBoseBush(4, 8, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- -1/3
  B[which(B == 2, arr.ind = TRUE)] <- 1/3
  B[which(B == 3, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBoseBush(4, 5)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 5)

  B <- createBoseBush(4, 4)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 4)

  B <- createBoseBush(8, 3)
  expect_equal(nrow(B), 2*8^2)
  expect_equal(ncol(B), 3)
})

test_that("createBush works", {
  B <- createBush(3, 3, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBush(4, 5, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- -1/3
  B[which(B == 2, arr.ind = TRUE)] <- 1/3
  B[which(B == 3, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBush(3, 3)
  expect_equal(nrow(B), 3^3)
  expect_equal(ncol(B), 3)

  B <- createBush(3, 4)
  expect_equal(nrow(B), 3^3)
  expect_equal(ncol(B), 4)

  B <- createBush(5, 4)
  expect_equal(nrow(B), 5^3)
  expect_equal(ncol(B), 4)
})

test_that("createAddelKemp works", {
  B <- createAddelKemp(2, 4, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  expect_true(checkOA(B))

  B <- createAddelKemp(3, 6, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createAddelKemp(4, 5)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 5)

  B <- createAddelKemp(4, 4)
  expect_equal(nrow(B), 2*4^2)
  expect_equal(ncol(B), 4)

  B <- createAddelKemp(5, 3)
  expect_equal(nrow(B), 2*5^2)
  expect_equal(ncol(B), 3)
})

test_that("createAddelKemp3 works", {
  B <- createAddelKemp3(2, 13, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  expect_true(checkOA(B))

  B <- createAddelKemp3(3, 25, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

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
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBusht(3, 4, 3, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

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
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBoseBushl(4, 4, 16, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- -1/3
  B[which(B == 2, arr.ind = TRUE)] <- 1/3
  B[which(B == 3, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))
})

test_that("createAddelKempN works", {
  B <- createAddelKempN(2, 3, 3, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  expect_true(checkOA(B))

  B <- createAddelKempN(3, 4, 4, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))
})
