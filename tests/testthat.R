if (require(testthat, quietly = TRUE))
{
  library(lhs)
  test_check("lhs")
} else {
  cat("\ntestthat not available for testing\n")
}
