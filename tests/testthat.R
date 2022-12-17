if (require(testthat))
{
  library(lhs)
  test_check("lhs")
} else {
  cat("\ntestthat not available for testing\n")
}
