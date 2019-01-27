/**
 * @file lhs_r_utilities.h
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

#ifndef LHS_R_UTILITIES_H
#define	LHS_R_UTILITIES_H

#include <Rcpp.h>
#include "LHSCommonDefines.h"

/**
 * @namespace lhs_r a namespace for the lhs methods used in the R interface
 */
namespace lhs_r
{
    /**
     * find the order of an input vector using 0 as the first order
     * @param v the input values
     * @param order the order of the input values
     */
    void findorder_zero(const Rcpp::NumericVector & v, Rcpp::IntegerVector & order);
    /**
     * convert an integer matrix to a numeric latin hypercube sample
     * @param intMat the input matrix to be converted
     * @return a latin hypercube sample
     */
    Rcpp::NumericMatrix convertIntegerToNumericLhs(const bclib::matrix<int> & intMat);
    /**
     * convert a numeric matrix to a numeric latin hypercube sample
     * @param intMat the input matrix to be converted
     * @return a Latin hypercube sample
     */
    Rcpp::NumericMatrix convertMatrixToNumericLhs(const bclib::matrix<double> & intMat);
    /**
     * convert a Rcpp::IntegerMatrix to a numeric latin hypercube sample
     * @param intMat the input matrix to be converted
     * @return a Latin hypercube sample
     */
    Rcpp::NumericMatrix convertIntegerToNumericLhs(const Rcpp::IntegerMatrix & intMat);
    /**
     * a uniform integer sample between min and max
     * @param n the size of the sample
     * @param min_int the minimum integer in the sample
     * @param max_int the maximum integer in the sample
     * @return an integer vector
     */
    Rcpp::IntegerVector runifint(unsigned int n, int min_int, int max_int);
    /**
     * check the arguments are valid
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     */
    void checkArguments(int n, int k);
    /**
     * check that the arguments are valid
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param dup A factor that determines the number of candidate points used in the search.
     */
    void checkArguments(int n, int k, int dup);
    /**
     * check that the arguments are valid
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param maxsweeps the maximum number of sweeps to use in the algorithm
     * @param eps The optimal stopping criterion
     */
    void checkArguments(int n, int k, int maxsweeps, double eps);
    /**
     * develop an lhs sample in the degenerate case
     * @param k number parameters / columns in the lhs
     * @param oRandom a random number generator for the hypercube
     * @return the numeric matrix for the degenerate case
     */
    Rcpp::NumericMatrix degenerateCase(int k, bclib::CRandom<double> & oRandom);

    /**
     * Calculate the distance between points in a matrix
     * @param mat the matrix to use for the calculation
     * @tparam RTYPE the type of SEXP
     * @return the matrix of distances
     */
    template <int RTYPE>
    Rcpp::NumericMatrix calculateDistance(Rcpp::Matrix<RTYPE> & mat)  // non-const because of the matrix row
    {
        Rcpp::NumericMatrix result(mat.rows(), mat.cols());
        for (int i = 0; i < mat.rows() - 1; i++)
        {
            for (int j = i+1; j < mat.rows(); j++)
            {
                typename Rcpp::Matrix<RTYPE>::Row rowi = mat.row(i);
                typename Rcpp::Matrix<RTYPE>::Row rowj = mat.row(j);
                double sum = static_cast<double>(Rcpp::sum((rowi - rowj) * (rowi - rowj)));
                result(i,j) = sqrt(sum);
            }
        }
        return result;
    }

    /**
     * calculate the S optimal criterion
     * @param mat the input matrix
     * @tparam RTYPE the type of SEXP
     * @return the S optimality criterion
     */
    template <int RTYPE>
    double calculateSOptimal(Rcpp::Matrix<RTYPE> & mat)
    {
        //        B[i] <- 1/sum(1/dist(A[, , i]))
        Rcpp::NumericMatrix dist = lhs_r::calculateDistance<RTYPE>(mat);
        Rcpp::NumericMatrix::iterator i;
        for (i = dist.begin(); i != dist.end(); ++i)
        {
            if (*i != 0.0)
            {
                *i = 1.0 / *i;
            }
        }
        double sum = std::accumulate<Rcpp::NumericMatrix::iterator>(dist.begin(), dist.end(), 0.0);
        if (sum > 0)
        {
            return 1.0 / sum;
        }
        else
        {
            throw std::runtime_error("problem with calculateSOptimal");
        }
    }
}

#endif	/* LHS_R_UTILITIES_H */

