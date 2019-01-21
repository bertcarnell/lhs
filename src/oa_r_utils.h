/**
 * @file oa_r_utils.h
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

#ifndef OA_R_UTILS_H
#define	OA_R_UTILS_H

#include <stdexcept>
#include <Rcpp.h>
#include "matrix.h"
#include "rutils.h"

/**
 * @namespace oarutils A namespace for R connection utilities
 */
namespace oarutils {

    /**
     * A method to convert an oacpp::matrix to an Rcpp::IntegerMatrix
     * @tparam T an atomic type that is convertible to <code>int</code> through a <code>static_cast<int>(T t)</code>
     * @param A an orthogonal array matrix
	 * @param rcppA the output Rcpp::IntegerMatrix
     * @return an integer matrix
     */
    template <class T>
    void convertToIntegerMatrix(const bclib::matrix<T> & A, Rcpp::IntegerMatrix & rcppA)
    {
      size_t nrows = A.rowsize();
      size_t ncols = A.colsize();
      if (rcppA.rows() != static_cast<int>(nrows) || rcppA.cols() != static_cast<int>(ncols))
      {
        rcppA = Rcpp::IntegerMatrix(nrows, ncols);
      }
      for (size_t i = 0; i < nrows; i++)
      {
        for (size_t j = 0; j < ncols; j++)
        {
          rcppA(i,j) = static_cast<int>(A(i,j));
        }
      }
    }

    /**
     * A method to convert a bclib::matrix to an Rcpp::NumericMatrix or Rcpp::IntegerMatrix
     * @tparam T an atomic type that matches the Rcpp type
     * @tparam U an Rcpp matrix type
     * @param A a bclib matrix
     * @param rcppA a Rcpp matrix
     * @return
     */
    template <class T, class U>
    void convertToRcppMatrix(const bclib::matrix<T> & A, U & rcppA)
    {
      size_t nrows = A.rowsize();
      size_t ncols = A.colsize();
      if (rcppA.rows() != static_cast<int>(nrows) || rcppA.cols() != static_cast<int>(ncols))
      {
        rcppA = U(nrows, ncols);
      }
      for (size_t i = 0; i < nrows; i++)
      {
        for (size_t j = 0; j < ncols; j++)
        {
          rcppA(i,j) = A(i,j);
        }
      }
    }

    /**
     * A method to convert a Rcpp::NumericMatrix or Rcpp::IntegerMatrix to a bclib::matrix
     * @tparam T an atomic type that matches the Rcpp type
     * @tparam U an Rcpp matrix type
     * @param A a bclib::matrix
     * @param rcppA a Rcpp matrix
     * @return
     */
    template <class T, class U>
    void convertToMatrix(const U & rcppA, bclib::matrix<T> & A)
    {
      int nrows = rcppA.rows();
      int ncols = rcppA.cols();
      if (nrows != static_cast<int>(A.rowsize()) || ncols != static_cast<int>(A.colsize()))
      {
        A = bclib::matrix<T>(static_cast<size_t>(nrows), static_cast<size_t>(ncols));
      }
      for (size_t i = 0; i < static_cast<size_t>(nrows); i++)
      {
        for (size_t j = 0; j < static_cast<size_t>(ncols); j++)
        {
          A(i,j) = rcppA(i,j);
        }
      }
    }

	/**
	 * permute the entries of each column in an orthogonal array
	 * @param oa A Rcpp::IntegerMatrix containing an orthogonal array
	 * @param q The number of unique entries in each column
	 */
    void randomizeOA(Rcpp::IntegerMatrix & oa, int q);

} // end namespace

#endif	/* OA_R_UTILS_H */

