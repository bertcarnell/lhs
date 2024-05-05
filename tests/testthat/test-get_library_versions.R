# Copyright 2024 Robert Carnell

context("test-get_library_versions")

test_that("get_library_versions", {
  a <- get_library_versions()
  expect_true(is.character(a))
  expect_equal(1, length(a))
  expect_true(nchar(a) > 10)
})
