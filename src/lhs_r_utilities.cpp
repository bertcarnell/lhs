/**
 * @file lhs_r_utilities.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
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

#include "lhs_r_utilities.h"

namespace lhs_r
{
    void findorder_zero(const Rcpp::NumericVector & v, Rcpp::IntegerVector & order)
    {
        std::vector<double> vlocal = Rcpp::as<std::vector<double> >(v);
        std::vector<int> orderlocal(v.size());
        bclib::findorder_zero(vlocal, orderlocal);
        order = Rcpp::IntegerVector::import(orderlocal.begin(), orderlocal.end());
        // TODO: could we have done orderlocal = Rcpp::as<std::vector<int> >(order); ??
    }

    Rcpp::NumericMatrix convertIntegerToNumericLhs(const bclib::matrix<int> & intMat)
    {
        bclib::matrix<int>::size_type rows;
        bclib::matrix<int>::size_type cols;
        rows = intMat.rowsize();
        cols = intMat.colsize();
        Rcpp::NumericMatrix result(rows, cols);
        Rcpp::NumericVector eps = Rcpp::runif(static_cast<int>(rows*cols));
        unsigned int counter = 0;
        // I think this is right (iterate over rows within columns
        for (bclib::matrix<int>::size_type col = 0; col < cols; col++)
        {
            for (bclib::matrix<int>::size_type row = 0; row < rows; row++)
            {
                result(row, col) = static_cast<double>(intMat(row, col) - 1) + eps[counter];
                result(row, col) /= static_cast<double>(rows);
                counter++;
            }
        }

        return result;
    }

    Rcpp::NumericMatrix convertIntegerToNumericLhs(const Rcpp::IntegerMatrix & intMat)
    {
        int n = intMat.rows();
        int k = intMat.cols();
        Rcpp::NumericMatrix result(n, k);
        Rcpp::NumericVector eps = Rcpp::runif(static_cast<int>(n*k));
        unsigned int counter = 0;
        // I think this is right (iterate over rows within columns
        for (bclib::matrix<int>::size_type col = 0; col < static_cast<unsigned int>(k); col++)
        {
            for (bclib::matrix<int>::size_type row = 0; row < static_cast<unsigned int>(n); row++)
            {
                result(row, col) = static_cast<double>(intMat(row, col) - 1) + eps[counter];
                result(row, col) /= static_cast<double>(n);
                counter++;
            }
        }

        return result;
    }

    Rcpp::NumericMatrix convertMatrixToNumericLhs(const bclib::matrix<double> & intMat)
    {
        //std::vector<double>::iterator i = intMat.getDataVector().begin();  this iterator is row wise, but numeric matrix may be columnwise
        bclib::matrix<int>::size_type rows = intMat.rowsize();
        bclib::matrix<int>::size_type cols = intMat.colsize();
        //Rcpp::NumericMatrix result(rows, cols, i);

        Rcpp::NumericMatrix result(rows, cols);
        for (bclib::matrix<int>::size_type i = 0; i < rows; i++)
        {
            for (bclib::matrix<int>::size_type j = 0; j < cols; j++)
            {
                result(i, j) = intMat(i, j);
            }
        }

        return result;
    }

    Rcpp::IntegerVector runifint(unsigned int n, int min_int, int max_int)
    {
        Rcpp::NumericVector r = Rcpp::runif(n);
        Rcpp::IntegerVector intv(n);
        Rcpp::IntegerVector::iterator intv_it;
        Rcpp::NumericVector::iterator r_it;
        double range = static_cast<double>(max_int + 1 - min_int);
        for (intv_it = intv.begin(), r_it = r.begin();
                intv_it != intv.end() && r_it != r.end(); ++intv_it, ++r_it)
        {
            *intv_it = min_int + static_cast<int>(floor(static_cast<double>(*r_it) * range));
        }
        return intv;
    }

    void checkArguments(int n, int k)
    {
        if (n == NA_INTEGER || k == NA_INTEGER)
        {
            throw std::invalid_argument("Invalid Argument: n and k may not be NA or NaN");
        }
        else if (n < 1 || k < 1)
        {
            std::stringstream msg;
            msg << "Invalid Argument: n and k must be integers > 0, n=" << n << " k=" << k << "\n";
			const std::string smsg = msg.str();
            throw std::invalid_argument(smsg.c_str());
        }
    }

    void checkArguments(int n, int k, int dup)
    {
        checkArguments(n, k);
        if (dup == NA_INTEGER)
        {
            throw std::invalid_argument("Invalid Argument: dup may not be NA or NaN");
        }
        if (dup < 1)
        {
            std::stringstream msg;
            msg << "Invalid Argument: dup must be an integer > 0, dup=" << dup << "\n";
			const std::string smsg = msg.str();
            throw std::invalid_argument(smsg.c_str());
        }
    }

    void checkArguments(int n, int k, int maxsweeps, double eps)
    {
        std::stringstream msg;
        checkArguments(n, k);
        if (maxsweeps == NA_INTEGER)
        {
            throw std::invalid_argument("Invalid Argument: maxsweeps may not be NA or NaN");
        }
        else if (!R_FINITE(eps))
        {
            throw std::invalid_argument("Invalid Argument: eps may not be Na, NaN, or +-Inf");
        }
        else if (maxsweeps < 1)
        {
            msg << "Invalid Argument: maxsweeps must be an integer > 0, maxsweeps=" << maxsweeps << "\n";
			const std::string smsg = msg.str();
            throw std::invalid_argument(smsg.c_str());
        }
        else if (eps <= 0 || eps >= 1)
        {
            msg << "Invalid Argument: eps must be a double on the interval (0,1), eps=" << eps << "\n";
			const std::string smsg = msg.str();
			throw std::invalid_argument(smsg.c_str());
		}
    }

    Rcpp::NumericMatrix degenerateCase(int k, bclib::CRandom<double> & oRandom)
    {
        Rcpp::NumericMatrix Z(1, k);
        for (int i = 0; i < k; i++)
        {
          Z(0, i) = oRandom.getNextRandom();
        }
        return Z;
    }
} // end namespace
