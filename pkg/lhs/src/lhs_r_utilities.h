/* 
 * File:   lhs_r_utilities.h
 * Author: carnellr
 *
 * Created on November 28, 2013, 10:05 PM
 */

#ifndef LHS_R_UTILITIES_H
#define	LHS_R_UTILITIES_H

#include <Rcpp.h>
#include "CommonDefines.h"

namespace lhs_r
{
    void findorder_zero(const Rcpp::NumericVector & v, Rcpp::IntegerVector & order);
    Rcpp::NumericMatrix convertIntegerToNumericLhs(const bclib::matrix<int> & intMat);
    Rcpp::NumericMatrix convertMatrixToNumericLhs(const bclib::matrix<double> & intMat);
    Rcpp::IntegerVector runifint(unsigned int n, int min_int, int max_int);
    void checkArguments(int n, int k);
    void checkArguments(int n, int k, int dup);
    void checkArguments(int n, int k, int maxsweeps, double eps);
    Rcpp::NumericMatrix degenerateCase(int k);

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
                int sum = Rcpp::sum((rowi - rowj) * (rowi - rowj));
                result(i,j) = sqrt(static_cast<double>(sum));
            }
        }
        return result;
    }

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
            throw Rcpp::exception("problem with calculateSOptimal");
        }
    }
}

#endif	/* LHS_R_UTILITIES_H */

