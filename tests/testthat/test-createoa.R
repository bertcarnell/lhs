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
})

test_that("createBush works", {
  B <- createBush(3, 3, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- 0
  B[which(B == 2, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))

  B <- createBose(4, 5, FALSE)
  B[which(B == 0, arr.ind = TRUE)] <- -1
  B[which(B == 1, arr.ind = TRUE)] <- -1/3
  B[which(B == 2, arr.ind = TRUE)] <- 1/3
  B[which(B == 3, arr.ind = TRUE)] <- 1
  expect_true(checkOA(B))
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
