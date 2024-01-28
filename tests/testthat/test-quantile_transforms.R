test_that("q_factor works", {
  p <- randomLHS(n=5, k=1)
  fact <- factor(LETTERS[1:4])
  res <- q_factor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))

  p <- randomLHS(n=5, k=1)
  fact <- factor(LETTERS[1:4], levels = LETTERS[4:1], ordered = TRUE)
  res <- q_factor(p, fact)
  expect_true(all(levels(res) %in% levels(fact)))

  p <- randomLHS(n=25, k=1)
  fact <- factor(LETTERS[1:5])
  res <- table(q_factor(p, fact))
  expect_equivalent(rep(5, 5), c(res))
})

test_that("q_integer works", {
  p <- randomLHS(n = 25, k = 1)
  res <- q_integer(p, 6, 12)
  expect_equal(6, min(res))
  expect_equal(12, max(res))
  expect_true(all(res %in% 6:12))
})

test_that("q_dirichlet works", {
  set.seed(19753)
  X <- randomLHS(500, 5)
  Y <- X
  Y[,1:3] <- q_dirichlet(X[,1:3], rep(2,3))
  Y[,4] <- qnorm(X[,4], 2, 1)
  Y[,5] <- qunif(X[,5], 1, 3)

  expect_equal(rep(1,500), rowSums(Y[,1:3]))
})
