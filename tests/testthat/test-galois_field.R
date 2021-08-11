test_that("Galois Fields Work", {
  test_field <- function(q, p, n)
  {
    gf <- create_galois_field(q)
    expect_equal(gf$p, p)
    expect_equal(gf$q, q)
    expect_equal(gf$n, n)
  }

  test_field(2, 2, 1)
  test_field(3, 3, 1)
  test_field(4, 2, 2)
  test_field(9, 3, 2)

  # q cannot be less than 2
  expect_error(create_galois_field(-1))
  expect_error(create_galois_field(1))
  # q must be a prime power
  expect_error(create_galois_field(100000000))
  expect_error(create_galois_field(35))
  # the prime power can't be too large
  expect_error(create_galois_field(2^30))
})

test_that("Associative", {
  check_associative <- function(gf){
    for (i in 1:gf$q)
    {
      for (j in 1:gf$q)
      {
        for (k in 1:gf$q)
        {
          sum1 <- poly_sum(gf$p, gf$n, gf$poly[i,], gf$poly[j,])
          sum2 <- poly_sum(gf$p, gf$n, sum1, gf$poly[k,])
          sum3 <- poly_sum(gf$p, gf$n, gf$poly[j,], gf$poly[k,])
          sum4 <- poly_sum(gf$p, gf$n, gf$poly[i,], sum3)
          expect_equal(sum2, sum4)

          prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], gf$poly[j,])
          prod2 <- poly_prod(gf$p, gf$n, gf$xton, prod1, gf$poly[k,])
          prod3 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[j,], gf$poly[k,])
          prod4 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], prod3)
          expect_equal(prod2, prod4)

        }
      }
    }
  }
  check_associative(create_galois_field(3))
  check_associative(create_galois_field(4))
  check_associative(create_galois_field(9))
  check_associative(create_galois_field(8))
})

test_that("Commutative", {
  check_commutative <- function(gf)
  {
    for (i in 1:gf$q)
    {
      for (j in 1:gf$q)
      {
        sum1 <- poly_sum(gf$p, gf$n, gf$poly[i,], gf$poly[j,])
        sum2 <- poly_sum(gf$p, gf$n, gf$poly[j,], gf$poly[i,])
        expect_equal(sum1, sum2)

        prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], gf$poly[j,])
        prod2 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[j,], gf$poly[i,])
        expect_equal(prod1, prod2)
      }
    }
  }
  check_commutative(create_galois_field(3))
  check_commutative(create_galois_field(4))
  check_commutative(create_galois_field(9))
  check_commutative(create_galois_field(8))
})

test_that("Identity", {
  check_identity <- function(gf, zero, one)
  {
    for (i in 1:gf$q)
    {
      sum1 <- poly_sum(gf$p, gf$n, gf$poly[i,], zero)
      expect_equal(sum1, gf$poly[i,])
      prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], one)
      expect_equal(prod1, gf$poly[i,])
    }
  }
  check_identity(create_galois_field(3), 0, 1)
  check_identity(create_galois_field(4), c(0,0), c(1,0))
  check_identity(create_galois_field(9), c(0,0), c(1,0))
  check_identity(create_galois_field(8), c(0,0,0), c(1,0,0))
})

test_that("Inverse", {
  check_inverse <- function(gf, zero, one)
  {
    #gf <- create_galois_field(3)
    for (i in 1:gf$q)
    {
      #i <- 1
      sum1 <- poly_sum(gf$p, gf$n, gf$poly[i,], gf$poly[gf$neg[i] + 1,])
      expect_equal(sum1, zero)
      if (!is.na(gf$inv[i]))
      {
        prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], gf$poly[gf$inv[i] + 1,])
        expect_equal(prod1, one)
      }
    }
  }
  check_inverse(create_galois_field(3), 0, 1)
  check_inverse(create_galois_field(4), c(0,0), c(1,0))
  check_inverse(create_galois_field(9), c(0,0), c(1,0))
  check_inverse(create_galois_field(8), c(0,0,0), c(1,0,0))
})

test_that("Distributive", {
  check_distributive <- function(gf)
  {
    for (i in 1:gf$q)
    {
      for (j in 1:gf$q)
      {
        for (k in 1:gf$q)
        {
          sum1 <- poly_sum(gf$p, gf$n, gf$poly[j,], gf$poly[k,])
          prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], sum1)
          prod2 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], gf$poly[j,])
          prod3 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[i,], gf$poly[k,])
          sum2 <- poly_sum(gf$p, gf$n, prod2, prod3)
          expect_equal(prod1, sum2)
        }
      }
    }
  }
  check_distributive(create_galois_field(3))
  check_distributive(create_galois_field(4))
  check_distributive(create_galois_field(9))
  check_distributive(create_galois_field(8))
})

test_that("Roots", {
  check_roots <- function(gf)
  {
    #gf <- create_galois_field(3)
    for (i in 1:gf$q)
    {
      if (!is.na(gf$root[i])){
        prod1 <- poly_prod(gf$p, gf$n, gf$xton, gf$poly[gf$root[i] + 1,], gf$poly[gf$root[i] + 1,])
        expect_equal(gf$poly[i, ], prod1)
      }
    }
  }
  check_roots(create_galois_field(3))
  check_roots(create_galois_field(4))
  check_roots(create_galois_field(9))
  check_roots(create_galois_field(8))
})
