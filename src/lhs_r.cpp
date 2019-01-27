/**
 * @file lhs_r.cpp
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

#include "lhs_r.h"

RcppExport SEXP /*double matrix*/ improvedLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k,
        SEXP /*int*/ dup)
{
  BEGIN_RCPP
    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP ||
            TYPEOF(dup) != INTSXP)
    {
        Rcpp_error("n, k, and dup should be integers");
    }

    Rcpp::RNGScope tempRNG;

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    int m_dup = Rcpp::as<int>(dup);

    lhs_r::checkArguments(m_n, m_k, m_dup);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    if (m_n == 1)
    {
        return lhs_r::degenerateCase(m_k, oRStandardUniform);
    }

    bclib::matrix<int> intMat = bclib::matrix<int>(m_n, m_k);
    lhslib::improvedLHS(m_n, m_k, m_dup, intMat, oRStandardUniform);
    Rcpp::NumericMatrix result = lhs_r::convertIntegerToNumericLhs(intMat);

    return result;
  END_RCPP
}

RcppExport SEXP /*double matrix*/ maximinLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k,
        SEXP /*int*/ dup)
{
  BEGIN_RCPP
    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP ||
            TYPEOF(dup) != INTSXP)
    {
        Rcpp_error("n, k, and dup should be integers");
    }

    Rcpp::RNGScope tempRNG;

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    int m_dup = Rcpp::as<int>(dup);

    lhs_r::checkArguments(m_n, m_k, m_dup);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    if (m_n == 1)
    {
        return lhs_r::degenerateCase(m_k, oRStandardUniform);
    }

    bclib::matrix<int> intMat = bclib::matrix<int>(m_n, m_k);
    lhslib::maximinLHS(m_n, m_k, m_dup, intMat, oRStandardUniform);
    Rcpp::NumericMatrix result = lhs_r::convertIntegerToNumericLhs(intMat);

    return result;
  END_RCPP
}

RcppExport SEXP /*double matrix*/ optimumLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k,
        SEXP /*int*/ maxsweeps, SEXP /*double*/ eps, SEXP /*bool*/ bVerbose)
{
  BEGIN_RCPP
    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP || TYPEOF(maxsweeps) != INTSXP ||
            TYPEOF(eps) != REALSXP || TYPEOF(bVerbose) != LGLSXP)
    {
      Rcpp_error("n, k, and maxsweeps should be integers, eps should be a real, and bVerbose should be a logical");
    }

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    int m_maxsweeps = Rcpp::as<int>(maxsweeps);
    double m_eps = Rcpp::as<double>(eps);
    bool m_bVerbose = Rcpp::as<bool>(bVerbose);

    lhs_r::checkArguments(m_n, m_k, m_maxsweeps, m_eps);
    Rcpp::RNGScope tempRNG;
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    if (m_n == 1)
    {
        return lhs_r::degenerateCase(m_k, oRStandardUniform);
    }

    int jLen = static_cast<int>(::Rf_choose(static_cast<double>(m_n), 2.0) + 1.0);
    bclib::matrix<int> intMat = bclib::matrix<int>(m_n, m_k);

    lhslib::optimumLHS(m_n, m_k, m_maxsweeps, m_eps, intMat,
            jLen, oRStandardUniform, m_bVerbose);

    Rcpp::NumericMatrix result = lhs_r::convertIntegerToNumericLhs(intMat);

    return result;
  END_RCPP
}

RcppExport SEXP /*double matrix*/ optSeededLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k,
        SEXP /*int*/ maxsweeps, SEXP /*double*/ eps, SEXP /*numeric matrix*/ inlhs,
        SEXP /*bool*/ bVerbose)
{
  BEGIN_RCPP
    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP || TYPEOF(maxsweeps) != INTSXP ||
            TYPEOF(eps) != REALSXP || TYPEOF(bVerbose) != LGLSXP)
    {
      Rcpp_error("n, k, and maxsweeps should be integers, eps should be a real, and bVerbose should be a logical");
    }

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    int m_maxsweeps = Rcpp::as<int>(maxsweeps);
    double m_eps = Rcpp::as<double>(eps);
    bool m_bVerbose = Rcpp::as<bool>(bVerbose);

    lhs_r::checkArguments(m_n, m_k, m_maxsweeps, m_eps);
    Rcpp::NumericMatrix m_inlhs(inlhs);
    if (m_inlhs.ncol() != m_k || m_inlhs.nrow() != m_n)
    {
      Rcpp_error("input matrix does not match the n and k arguments");
    }
    if (m_n == 1)
    {
        return m_inlhs;
    }

    int jLen = static_cast<int>(::Rf_choose(static_cast<double>(m_n), 2.0) + 1.0);
    //std::vector<double> mv_inlhs = Rcpp::as<std::vector<double> >(m_inlhs); // this probably unrolled the matrix columnwise
    //bclib::matrix<double> mm_inlhs = bclib::matrix<double>(m_n, m_k, mv_inlhs); // and this was row wise
    bclib::matrix<double> mm_inlhs = bclib::matrix<double>(m_n, m_k);
    for (int i = 0; i < m_n; i++)
    {
        for (int j = 0; j < m_k; j++)
        {
            mm_inlhs(i,j) = m_inlhs(i,j);
        }
    }

    lhslib::optSeededLHS(m_n, m_k, m_maxsweeps, m_eps, mm_inlhs,
            jLen, m_bVerbose);

    Rcpp::NumericMatrix result = lhs_r::convertMatrixToNumericLhs(mm_inlhs);

    return result;
  END_RCPP
}

RcppExport SEXP randomLHS_cpp(SEXP n, SEXP k, SEXP preserveDraw)
{
  BEGIN_RCPP
    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP ||
            TYPEOF(preserveDraw) != LGLSXP)
    {
      Rcpp_error("n and k should be integers, preserveDraw should be a logical");
    }

    Rcpp::RNGScope tempRNG;

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    bool bPreserveDraw = Rcpp::as<bool>(preserveDraw);

    lhs_r::checkArguments(m_n, m_k);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    if (m_n == 1)
    {
        return lhs_r::degenerateCase(m_k, oRStandardUniform);
    }

    bclib::matrix<double> result = bclib::matrix<double>(m_n, m_k);
    lhslib::randomLHS(m_n, m_k, bPreserveDraw, result, oRStandardUniform);

    Rcpp::NumericMatrix rresult(m_n, m_k);
    for (int irow = 0; irow < m_n; irow++)
    {
        for (int jcol = 0; jcol < m_k; jcol++)
        {
            rresult(irow, jcol) = result(irow, jcol);
        }
    }

    return rresult;
  END_RCPP
}

RcppExport SEXP geneticLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, SEXP /*int*/ pop,
        SEXP /*int*/ gen, SEXP /*double*/ pMut, SEXP criterium,
        SEXP /*bool*/ bVerbose)
{
  BEGIN_RCPP
    Rcpp::RNGScope tempRNG;

    int m_n = Rcpp::as<int>(n);
    int m_k = Rcpp::as<int>(k);
    int m_pop = Rcpp::as<int>(pop);
    int m_gen = Rcpp::as<int>(gen);
    double m_pMut = Rcpp::as<double>(pMut);
    std::string m_criterium = Rcpp::as<std::string>(criterium);
    bool m_bVerbose = Rcpp::as<bool>(bVerbose);

    lhs_r::checkArguments(m_n, m_k);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    if (m_n == 1)
    {
        return lhs_r::degenerateCase(m_k, oRStandardUniform);
    }

    bclib::matrix<double> mat = bclib::matrix<double>(m_n, m_k);
    lhslib::geneticLHS(m_n, m_k, m_pop, m_gen, m_pMut, m_criterium, m_bVerbose, mat, oRStandardUniform);

    Rcpp::NumericMatrix rresult(m_n, m_k);
    for (int irow = 0; irow < m_n; irow++)
    {
        for (int jcol = 0; jcol < m_k; jcol++)
        {
            rresult(irow, jcol) = mat(irow, jcol);
        }
    }

    return rresult;
  END_RCPP
}
