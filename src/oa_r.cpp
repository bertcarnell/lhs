/**
 * @file oa_r.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 *
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "oa_r.h"

RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q,
        SEXP /*int*/ ncol, SEXP /*bool*/ bRandom)
{
  BEGIN_RCPP
    Rcpp::IntegerMatrix rcppA(1,1); // need to initialize
    oacpp::COrthogonalArray oa;

    if (TYPEOF(q) != INTSXP || TYPEOF(ncol) != INTSXP)
    {
      Rcpp_error("q, ncol, and n should be integers");
    }
    if (TYPEOF(type) != STRSXP || TYPEOF(bRandom) != LGLSXP)
    {
      Rcpp_error("type should be a character and bRandom should be a logical");
    }

    Rcpp::IntegerVector ivq(q);
    Rcpp::IntegerVector ivncol(ncol);
    Rcpp::LogicalVector lvbRandom(bRandom);
    if (ivq.size() > 1 || ivncol.size() > 1 || lvbRandom.size() > 1)
    {
      Rcpp_error("q, ncol, and bRandom can only be of length 1");
    }

    int qlocal = Rcpp::as<int>(q);
    int ncollocal = Rcpp::as<int>(ncol);
    int nlocal = 0;
    std::string stype = Rcpp::as<std::string>(type);
    bool bRandomLocal = Rcpp::as<bool>(bRandom);

    if (qlocal == NA_INTEGER || ncollocal == NA_INTEGER ||
            bRandomLocal == NA_LOGICAL)
    {
      Rcpp_error("q, ncol, and bRandom are not permitted to be NA");
    }

    if (stype == typeConstants::BOSE)
    {
        oa.bose(qlocal, ncollocal, &nlocal);
    }
    else if (stype == typeConstants::BOSEBUSH)
    {
        oa.bosebush(qlocal, ncollocal, &nlocal);
    }
    else if (stype == typeConstants::BUSH)
    {
        oa.bush(qlocal, ncollocal, &nlocal);
    }
    else if (stype == typeConstants::ADDELKEMP3)
    {
        oa.addelkemp3(qlocal, ncollocal, &nlocal);
    }
    else if (stype == typeConstants::ADDELKEMP)
    {
        oa.addelkemp(qlocal, ncollocal, &nlocal);
    }
    else
    {
        std::stringstream sstype;
        sstype << stype << " is an Unrecognized orthogonal array algorithm";
        const std::string ssstype = sstype.str();
        Rcpp_error(ssstype.c_str());
    }

    if (oa.getReturnCode() == WARNING_CHECK)
    {
        Rcpp::warning(oa.getMessage().c_str());
    }

    oarutils::convertToIntegerMatrix<int>(oa.getoa(), rcppA);
    if (bRandomLocal)
    {
        oarutils::randomizeOA(rcppA, qlocal);
    }
    return rcppA;
  END_RCPP
}

RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1,
        SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*bool*/ bRandom)
{
  BEGIN_RCPP
    Rcpp::IntegerMatrix rcppA(1,1); // need to initialize
    oacpp::COrthogonalArray oa;

    if (TYPEOF(q) != INTSXP || TYPEOF(ncol) != INTSXP ||
            TYPEOF(int1) != INTSXP)
    {
      Rcpp_error("q, int1, and ncol should be integers");
    }
    if (TYPEOF(type) != STRSXP || TYPEOF(bRandom) != LGLSXP)
    {
      Rcpp_error("type should be a character and bRandom should be a logical");
    }

    Rcpp::IntegerVector ivint1(int1);
    Rcpp::IntegerVector ivq(q);
    Rcpp::IntegerVector ivncol(ncol);
    Rcpp::LogicalVector lvbRandom(bRandom);
    Rcpp::CharacterVector cvtype(type);

    if (ivq.size() > 1 || ivncol.size() > 1 || lvbRandom.size() > 1 ||
            ivint1.size() > 1 || cvtype.size() > 1)
    {
        ::Rf_error("q, ncol, type, and bRandom can only be of length 1");
    }

    int qlocal = Rcpp::as<int>(q);
    int ncollocal = Rcpp::as<int>(ncol);
    int nlocal = 0;
    int int1local = Rcpp::as<int>(int1);
    bool bRandomLocal = Rcpp::as<bool>(bRandom);

    if (qlocal == NA_INTEGER || ncollocal == NA_INTEGER ||
            int1local == NA_INTEGER || bRandomLocal == NA_LOGICAL)
    {
        if (cvtype[0] == typeConstants::BOSEBUSHL)
        {
            Rcpp_error("q, lambda, and bRandom are not permitted to be NA");
        }
        else if (cvtype[0] == typeConstants::BUSHT)
        {
            Rcpp_error("q, str, and bRandom are not permitted to be NA");
        }
        else if (cvtype[0] == typeConstants::ADDELKEMPN)
        {
            Rcpp_error("q, akn, and bRandom are not permitted to be NA");
        }
        else
        {
            std::stringstream sstype;
            sstype << cvtype[0] << " is an Unrecognized orthogonal array algorithm";
      			const std::string ssstype = sstype.str();
			      Rcpp_error(ssstype.c_str());
        }
    }

    if (cvtype[0] == typeConstants::BOSEBUSHL)
    {
        // int1 is lambda
        oa.bosebushl(int1local, qlocal, ncollocal, &nlocal);
    }
    else if (cvtype[0] == typeConstants::BUSHT)
    {
        // int1 is str
        oa.busht(int1local, qlocal, ncollocal, &nlocal);
    }
    else if (cvtype[0] == typeConstants::ADDELKEMPN)
    {
        // int1 is akn
        oa.addelkempn(int1local, qlocal, ncollocal, &nlocal);
    }
    else
    {
        std::stringstream sstype;
        sstype << cvtype[0] << " is an Unrecognized orthogonal array algorithm";
        const std::string ssstype = sstype.str();
        Rcpp_error(ssstype.c_str());
    }

    if (oa.getReturnCode() == WARNING_CHECK)
    {
        Rcpp::warning(oa.getMessage().c_str());
    }

    oarutils::convertToIntegerMatrix<int>(oa.getoa(), rcppA);
    if (bRandomLocal)
    {
        oarutils::randomizeOA(rcppA, qlocal);
    }
    return rcppA;
  END_RCPP
}

RcppExport SEXP /*List*/ create_galois_field(SEXP /*int*/ q)
{
  BEGIN_RCPP
    int qlocal = Rcpp::as<int>(q);

    oacpp::GaloisField gf = oacpp::GaloisField(qlocal);

    /** prime modulus exponent q = p^n --- Polynomial vector length */
    Rcpp::IntegerVector n = Rcpp::IntegerVector::create(gf.n);
    /** prime modulus q = p^n*/
    Rcpp::IntegerVector p = Rcpp::IntegerVector::create(gf.p);
    /** the order of the field q = p^n --- field element vector length */
    Rcpp::IntegerVector q = Rcpp::IntegerVector::create(gf.q);
    /** characteristic polynomial of length u_n */
    Rcpp::IntegerVector xton(gf.xton.begin(), gf.xton.end());
    /** Indicator of which row of poly is the multiplicative inverse of this row of length u_q */
    Rcpp::IntegerVector inv(gf.inv.begin(), gf.inv.end());
    /** row number of which row of poly is the negative (additive inverse) of this row of length u_q */
    Rcpp::IntegerVector neg(gf.neg.begin(), gf.neg.end());
    /** root */
    Rcpp::IntegerVector root(gf.root.begin(), gf.root.end());
    /** sum field of dimension u_q x u_q*/
    Rcpp::IntegerMatrix plus(gf.q, gf.q);
    oarutils::convertToIntegerMatrix<int>(gf.plus, plus);
    /** product field of dimension u_q x u_q*/
    Rcpp::IntegerMatrix times(gf.q, gf.q);
    oarutils::convertToIntegerMatrix<int>(gf.times, times);
    /** polynomial field of dimension u_q x u_n */
    Rcpp::IntegerMatrix poly(gf.q, gf.n);
    oarutils::convertToIntegerMatrix<int>(gf.poly, poly);

    Rcpp::List gf_S3 = Rcpp::List::create(n, p, q, xton, inv, neg, root, plus, times, poly);

    return gf_S3;
  END_RCPP
}


  /**
   * Multiplication in polynomial representation
   *
   * @param p modulus
   * @param u_n length of p1 and p2
   * @param xton characteristic polynomial
   * @param p1 polynomial 1
   * @param p2 polynomial 2
   * @param prod the product of the polynomials
   */
RcppExport SEXP /*IntegerVector*/ poly_prod(SEXP /*int*/ p, SEXP /*int*/ n,
                                            SEXP /*int vector*/ xton,
                                            SEXP /*int vector*/ p1,
                                            SEXP /*int vector*/ p2)
{
  BEGIN_RCPP
    int plocal = Rcpp::as<int>(p);
    int nlocal = Rcpp::as<int>(n);
    size_t u_n = static_cast<size_t>(nlocal);
    std::vector<int> xton_ref = Rcpp::as<std::vector<int> >(xton);
    std::vector<int> p1_ref = Rcpp::as<std::vector<int> >(p1);
    std::vector<int> p2_ref = Rcpp::as<std::vector<int> >(p2);
    std::vector<int> prod_ref = std::vector<int>(p1_ref.size());

    oacpp::GaloisField::polyProd(plocal, u_n, xton_ref, p1_ref, p2_ref, prod_ref);

    Rcpp::IntegerVector prod_res(prod_ref.begin(), prod_ref.end());

    return prod_res;
  END_RCPP
}

  /**
   * Addition in polynomial representation
   *
   * @param p modulus
   * @param u_n the length of p1 and p2
   * @param p1 polynomial 1
   * @param p2 polynomial 2
   * @param sum the sum of the polynomials
   */
RcppExport SEXP /*IntegerVector*/ poly_sum(SEXP /*int*/ p, SEXP /*int*/ n,
                                            SEXP /*int vector*/ p1,
                                            SEXP /*int vector*/ p2)
{
  BEGIN_RCPP
    int plocal = Rcpp::as<int>(p);
    int nlocal = Rcpp::as<int>(n);
    size_t u_n = static_cast<size_t>(nlocal);
    std::vector<int> p1_ref = Rcpp::as<std::vector<int> >(p1);
    std::vector<int> p2_ref = Rcpp::as<std::vector<int> >(p2);
    std::vector<int> sum_ref = std::vector<int>(p1_ref.size());

    oacpp::GaloisField::polySum(plocal, u_n, p1_ref, p2_ref, sum_ref);

    Rcpp::IntegerVector sum_res(sum_ref.begin(), sum_ref.end());

    return sum_res;
  END_RCPP
}

/**
   * Convert polynomial to integer in <code>0..q-1</code>
   *
   * @param p polynomial multiplier
   * @param n the length of poly
   * @param poly the polynomial
   * @return an integer
   */
RcppExport SEXP /*IntegerVector*/ poly2int(SEXP /*int*/ p, SEXP /*int*/ n,
                                           SEXP /*int vector*/ poly)
{
  BEGIN_RCPP
    int plocal = Rcpp::as<int>(p);
    int nlocal = Rcpp::as<int>(n);
    std::vector<int> poly_ref = Rcpp::as<std::vector<int> >(poly);
    Rcpp::IntegerVector res(1);

    res[0] = oacpp::GaloisField::poly2int(plocal, nlocal, poly_ref);

    return res;
  END_RCPP
}

