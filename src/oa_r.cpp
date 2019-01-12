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
        Rcpp_error(sstype.str().c_str());
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
            Rcpp_error(sstype.str().c_str());
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
        Rcpp_error(sstype.str().c_str());
    }
    oarutils::convertToIntegerMatrix<int>(oa.getoa(), rcppA);
    if (bRandomLocal)
    {
        oarutils::randomizeOA(rcppA, qlocal);
    }
    return rcppA;
  END_RCPP
}

