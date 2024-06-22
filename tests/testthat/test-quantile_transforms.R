# Copyright 2024 Robert Carnell

context("test-quantile_transformations")

test_that("qfactor works", {
  p <- randomLHS(n=5, k=1)
  fact <- factor(LETTERS[1:4])
  res <- qfactor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))
  expect_true(all(fact[floor(p[,1]*nlevels(fact)) + 1] == res))

  p <- randomLHS(n=5, k=1)
  fact <- factor(LETTERS[1:4], levels = LETTERS[4:1], ordered = TRUE)
  res <- qfactor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))
  expect_true(all(levels(fact)[floor(p[,1]*nlevels(fact)) + 1] == as.character(res)))

  p <- randomLHS(n=25, k=1)
  fact <- factor(LETTERS[1:5])
  res <- qfactor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))
  expect_true(all(fact[floor(p[,1]*nlevels(fact)) + 1] == res))
  expect_equivalent(rep(5, 5), c(table(res)))

  p <- randomLHS(n=25, k=1)
  fact <- ordered(LETTERS[1:5])
  res <- qfactor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))
  expect_true(all(levels(fact)[floor(p[,1]*nlevels(fact)) + 1] == as.character(res)))
  expect_equivalent(rep(5, 5), c(table(res)))

  expect_error(qfactor("a", factor("a")))
  expect_error(qfactor(c(0.1, 0.2), "a"))
  expect_error(qfactor(1.1, factor("a")))
  expect_error(qfactor(-3, factor("a")))
})

test_that("qinteger works", {
  p <- randomLHS(n = 25, k = 1)
  res <- qinteger(p, 6, 12)
  expect_equal(6, min(res))
  expect_equal(12, max(res))
  expect_true(all(res %in% 6:12))

  p <- randomLHS(n = 25, k = 1)
  res <- qinteger(p, -4L, 2L)
  expect_equal(-4, min(res))
  expect_equal(2, max(res))
  expect_true(all(res %in% -4:2))

  expect_error(qinteger("a", 1, 5))
  expect_error(qinteger(c(0.1, 0.2), 1.1, 5))
  expect_error(qinteger(c(0.1, 0.2), 1, 5.2))
  expect_error(qinteger(c(0.1, 0.2), 8, 5))
  expect_error(qinteger(1.1, factor("a")))
  expect_error(qinteger(-3, factor("a")))
})

test_that("qdirichlet works", {
  set.seed(19753)
  X <- randomLHS(500, 5)
  Y <- X
  Y[,1:3] <- qdirichlet(X[,1:3], rep(2,3))
  Y[,4] <- qnorm(X[,4], 2, 1)
  Y[,5] <- qunif(X[,5], 1, 3)

  expect_equal(rep(1,500), rowSums(Y[,1:3]))

  expect_error(qdirichlet(X[,1:3], rep(2, 7)))
  expect_error(qdirichlet(X[,1:3], c(1, NA, 7)))
})
