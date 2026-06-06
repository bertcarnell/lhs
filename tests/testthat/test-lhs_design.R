# Copyright 2026 Robert Carnell

context("test-lhs_design")

test_that("transform_lhs transforms each kind of margin", {
  set.seed(1234)
  # 5 single-column variables + a 3-column dirichlet = 8 LHS columns
  X <- randomLHS(50, 8)
  vars <- list(
    x = list(dist = "qnorm", mean = 2, sd = 0.5),
    grp = list(type = "factor", levels = c("a", "b", "c")),
    ogrp = list(type = "factor", levels = c("lo", "mid", "hi"), ordered = TRUE),
    count = list(type = "integer", min = 5L, max = 17L),
    z = function(p) qexp(p, rate = 2),
    comp = list(type = "dirichlet", alpha = c(2, 3, 4))
  )
  D <- transform_lhs(X, vars)

  expect_s3_class(D, "data.frame")
  expect_equal(nrow(D), 50)
  # 5 single columns + dirichlet (3) - but comp consumes 3 columns and yields 3
  expect_equal(ncol(D), 8)
  expect_equal(names(D),
               c("x", "grp", "ogrp", "count", "z", "comp1", "comp2", "comp3"))

  # normal margin
  expect_true(is.numeric(D$x))
  # unordered factor
  expect_true(is.factor(D$grp) && !is.ordered(D$grp))
  expect_setequal(levels(D$grp), c("a", "b", "c"))
  # ordered factor with levels in order
  expect_true(is.ordered(D$ogrp))
  expect_equal(levels(D$ogrp), c("lo", "mid", "hi"))
  # integer in range
  expect_true(all(D$count >= 5L & D$count <= 17L))
  # function transform matches a direct call
  expect_equal(D$z, qexp(X[, 5], rate = 2))
  # dirichlet rows sum to one
  expect_true(all(abs(rowSums(D[, c("comp1", "comp2", "comp3")]) - 1) < 1e-9))
})

test_that("lhs_design generates and transforms for each type", {
  vars <- list(
    a = list(dist = "qunif", min = 0, max = 10),
    b = list(type = "integer", min = 1L, max = 6L)
  )
  for (ty in c("random", "improved", "maximin", "optimum", "genetic"))
  {
    set.seed(99)
    D <- lhs_design(12, vars, type = ty)
    expect_s3_class(D, "data.frame")
    expect_equal(nrow(D), 12)
    expect_equal(names(D), c("a", "b"))
    expect_true(all(D$a >= 0 & D$a <= 10))
    expect_true(all(D$b >= 1L & D$b <= 6L))
  }

  # oalhs may return a different (valid OA) number of rows
  set.seed(99)
  D <- lhs_design(9, vars, type = "oalhs")
  expect_s3_class(D, "data.frame")
  expect_equal(ncol(D), 2)
})

test_that("lhs_design passes extra arguments to the generator", {
  set.seed(7)
  vars <- list(a = function(p) p)
  expect_silent(lhs_design(10, vars, type = "improved", dup = 3))
  expect_silent(lhs_design(10, vars, type = "optimum", maxSweeps = 2, eps = 0.1))
})

test_that("lhs_design and transform_lhs validate their inputs", {
  vars <- list(a = function(p) p, b = function(p) p)

  # n validation
  expect_error(lhs_design(0, vars))
  expect_error(lhs_design(c(1, 2), vars))
  expect_error(lhs_design(NA, vars))
  expect_error(lhs_design(2.5, vars))

  # variables validation
  expect_error(lhs_design(10, list()))
  expect_error(lhs_design(10, list(function(p) p)))            # unnamed
  expect_error(lhs_design(10, list(a = function(p) p, a = function(p) p)))
  expect_error(lhs_design(10, list(a = "not a spec")))
  expect_error(lhs_design(10, list(a = list(type = "factor"))))    # no levels
  expect_error(lhs_design(10, list(a = list(type = "integer"))))   # no min/max
  expect_error(lhs_design(10, list(a = list(type = "dirichlet")))) # no alpha

  # transform_lhs column count must match
  X <- randomLHS(10, 3)
  expect_error(transform_lhs(X, vars))         # needs 2 columns, given 3
  expect_error(transform_lhs(as.data.frame(X), vars))  # not a matrix
  Y <- randomLHS(10, 2)
  Y[1, 1] <- NA
  expect_error(transform_lhs(Y, vars))
  Z <- randomLHS(10, 2)
  Z[1, 1] <- 2
  expect_error(transform_lhs(Z, vars))
})

test_that("transform_lhs works on augmented designs", {
  set.seed(321)
  X <- augmentLHS(randomLHS(6, 2), 4)
  vars <- list(a = list(dist = "qnorm"), b = list(type = "integer", min = 0L, max = 9L))
  D <- transform_lhs(X, vars)
  expect_equal(nrow(D), 10)
  expect_equal(names(D), c("a", "b"))
})
