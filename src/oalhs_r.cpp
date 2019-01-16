/**
 * @file oalhs_r.cpp
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

#include "oalhs_r.h"

RcppExport SEXP /*double matrix*/ oa_to_lhs(SEXP /*int*/ n, SEXP /*int*/ k,
                                            SEXP /*int matrix*/ oa, SEXP /*bool*/ bverbose)
{
  BEGIN_RCPP
    Rcpp::IntegerMatrix intoa(oa);

    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP)
    {
      Rcpp_error("n and k should be integers");
    }
    if (TYPEOF(bverbose) != LGLSXP)
    {
      Rcpp_error("bverbose should be a logical");
    }

    int nlocal = Rcpp::as<int>(n);
    int klocal = Rcpp::as<int>(k);
    bclib::matrix<int>::size_type m_n = static_cast<bclib::matrix<int>::size_type>(nlocal);
    bclib::matrix<int>::size_type m_k = static_cast<bclib::matrix<int>::size_type>(klocal);
    bool bverbose_local = Rcpp::as<bool>(bverbose);

    if (nlocal == NA_INTEGER || klocal == NA_INTEGER ||
        bverbose_local == NA_LOGICAL)
    {
      Rcpp_error("n, k, and bverbose are not permitted to be NA");
    }

    bclib::matrix<int> oa_local = bclib::matrix<int>(m_n, m_k);
    oarutils::convertToMatrix(intoa, oa_local);
    bclib::matrix<int> intlhs_local = bclib::matrix<int>(m_n, m_k);
    bclib::matrix<double> lhs_local = bclib::matrix<double>(m_n, m_k);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();
    Rcpp::NumericMatrix rcppA(nlocal, klocal);

    oalhslib::oaLHS(nlocal, klocal, oa_local, intlhs_local, lhs_local,
                    bverbose_local, oRStandardUniform);

    oarutils::convertToRcppMatrix<double, Rcpp::NumericMatrix>(lhs_local, rcppA);
    return(rcppA);

  END_RCPP
}

RcppExport SEXP /*double matrix*/ create_oalhs(SEXP /*int*/ n, SEXP /*int*/ k,
                                               SEXP /*bool*/ bChooseLargerDesign,
                                               SEXP /*bool*/ bverbose)
{
  BEGIN_RCPP

    if (TYPEOF(n) != INTSXP || TYPEOF(k) != INTSXP)
    {
      Rcpp_error("n and k should be integers");
    }
    if (TYPEOF(bverbose) != LGLSXP || TYPEOF(bChooseLargerDesign) != LGLSXP)
    {
      Rcpp_error("bverbose should be a logical and bChooseLargerDesign should be logical");
    }

    int nlocal = Rcpp::as<int>(n);
    int klocal = Rcpp::as<int>(k);
    bclib::matrix<int>::size_type m_n = static_cast<bclib::matrix<int>::size_type>(nlocal);
    bclib::matrix<int>::size_type m_k = static_cast<bclib::matrix<int>::size_type>(klocal);
    bool bverbose_local = Rcpp::as<bool>(bverbose);
    bool bChooseLargerDesign_local = Rcpp::as<bool>(bChooseLargerDesign);


    if (nlocal == NA_INTEGER || klocal == NA_INTEGER ||
        bverbose_local == NA_LOGICAL || bChooseLargerDesign_local == NA_LOGICAL)
    {
      Rcpp_error("n, k, bChooseLargerDesign, and bverbose are not permitted to be NA");
    }

    bclib::matrix<double> oalhs_local = bclib::matrix<double>(m_n, m_k);
    Rcpp::NumericMatrix rcppA(nlocal, klocal);
    lhs_r::RStandardUniform oRStandardUniform = lhs_r::RStandardUniform();

    oalhslib::generateOALHS(nlocal, klocal, oalhs_local, bChooseLargerDesign_local,
                            bverbose_local, oRStandardUniform);

    oarutils::convertToRcppMatrix<double, Rcpp::NumericMatrix>(oalhs_local, rcppA);
    return(rcppA);
  END_RCPP
}
