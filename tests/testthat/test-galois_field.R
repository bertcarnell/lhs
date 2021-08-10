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





#   void GaloisFieldTest::testGaloisField()
#   {
#     oacpp::GaloisField gf = oacpp::GaloisField(3);
#
#     // q = p^n
#     // 3 = 3^1
#     bclib::Assert(gf.n == 1);
#     bclib::Assert(gf.p == 3);
#     bclib::Assert(gf.q == 3);
#     checkField(gf);
#
#     gf = oacpp::GaloisField(9);
#
#     // q = p^n
#     // 9 = 3^2
#     bclib::Assert(gf.n == 2);
#     bclib::Assert(gf.p == 3);
#     bclib::Assert(gf.q == 9);
#     // characteristic polynomial of degree n-1=1
#     // 1 + 2x
#     bclib::Assert(gf.xton[0] == 1 && gf.xton[1] == 2);
#     // polynomial field (a,b) a*1 + b*x
#     // 0,0 1,0 2,0 0,1 1,1 2,1 0,2 1,2 2,2
#     // 0, 1, 2, x, 1+x 2+x 2x, 1+2x, 2+2x
#     bclib::Assert(gf.poly.rowsize() == 9 && gf.poly.colsize() == 2);
#     bclib::Assert(gf.poly(0, 0) == 0 && gf.poly(8, 1) == 2);
#
#     checkField(gf);
#
#     gf = oacpp::GaloisField(2);
#     checkField(gf);
#     gf = oacpp::GaloisField(4);
#     checkField(gf);
#     gf = oacpp::GaloisField(8);
#     checkField(gf);
#     gf = oacpp::GaloisField(16);
#     checkField(gf);
#     gf = oacpp::GaloisField(32);
#     checkField(gf);
#     gf = oacpp::GaloisField(27);
#     checkField(gf);
#     gf = oacpp::GaloisField(5);
#     checkField(gf);
#     gf = oacpp::GaloisField(25);
#     checkField(gf);
#     gf = oacpp::GaloisField(7);
#     checkField(gf);
#     gf = oacpp::GaloisField(11);
#     checkField(gf);
#
#     ASSERT_NOTHROW(gf = oacpp::GaloisField(3));
#     ASSERT_THROW(gf = oacpp::GaloisField(-3));
#     ASSERT_THROW(gf = oacpp::GaloisField(1));
#     ASSERT_THROW(gf = oacpp::GaloisField(100));
#     ASSERT_THROW(gf = oacpp::GaloisField(oacpp::primes::ipow(2, 30)));
#   }
#
#   void GaloisFieldTest::testPolySum()
#   {
#     std::vector<int> sum = std::vector<int>();
#
#     oacpp::GaloisField gf = oacpp::GaloisField(3);
#     sum = helpersum(0, 1, gf);
#     bclib::Assert(sum[0] == 1);
#
#     gf = oacpp::GaloisField(9);
#     // characteristic polynomial of degree n-1=1
#     // 1 + 2x
#     // polynomial field (a,b) a*1 + b*x
#     // 0,0 1,0 2,0 0,1 1,1 2,1 0,2 1,2 2,2
#     // 0, 1, 2, x, 1+x 2+x 2x, 1+2x, 2+2x
#
#     // 0,0 plus 1,0
#     // 0 + 1 % 3 == 1 which is 1,0 in the vector
#     sum = helpersum(0, 1, gf);
#     bclib::Assert(sum[0] == 1 && sum[1] == 0);
#     // 2,2 plus 2,0
#     // 2+2x + 2 = 4+2x = 4%%3 + 2x = 1 + 2x
#     sum = helpersum(8, 2, gf);
#     bclib::Assert(sum[0] == 1 && sum[1] == 2);
#
#     gf = oacpp::GaloisField(8);
#     // n=3, p=2, q=8
#     // characteristic polynomial 1 + x^2
#     // polynomial field:
#       // 0, 1, x, 1+x, x^2, 1+x^2, x+x^2, 1+x+x^2
#     sum = helpersum(0, 1, gf);
#     bclib::Assert(sum[0] == 1 && sum[1] == 0 && sum[2] == 0);
#     // x+x^2 + 1+x+x^2 = 1+2x+2x^2 = 1
#     sum = helpersum(6, 7, gf);
#     bclib::Assert(sum[0] == 1 && sum[1] == 0 && sum[2] == 0);
#   }
#
#   void GaloisFieldTest::testPolyProd()
#   {
#     oacpp::GaloisField gf = oacpp::GaloisField(3);
#     std::vector<int> prod = std::vector<int>(gf.u_n);
#
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
#     bclib::Assert(prod == gf.poly.getrow(0));
#
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(2), prod); // 1*2 %% 3
#     bclib::Assert(prod == gf.poly.getrow(2));
#
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(2), prod); // 2*2 %% 3
#     bclib::Assert(prod == gf.poly.getrow(1));
#
#     gf = oacpp::GaloisField(9);
#     prod.clear();
#     prod.resize(gf.u_n);
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
#     bclib::Assert(prod == gf.poly.getrow(0));
#
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(8), prod); // 1*(2+2x) %% 1+2x
#     bclib::Assert(prod == gf.poly.getrow(8));
#
#     oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(3), prod); // 2*x %% 1+2x
#     bclib::Assert(prod == gf.poly.getrow(6));
#   }
# }
#
