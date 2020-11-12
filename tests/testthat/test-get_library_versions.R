test_that("get_library_versions", {
  a <- get_library_versions()
  expect_true(is.character(a))
  expect_equal(1, length(a))
  expect_true(nchar(a) > 10)
})
