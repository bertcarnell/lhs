/**
 * @file oa_r_utils.cpp
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

#include "oa_r_utils.h"

namespace oarutils {

    void randomizeOA(Rcpp::IntegerMatrix & oa, int q)
    {
        // get the random number scope from R
        Rcpp::RNGScope scope;
        size_t rows = oa.rows();
        size_t cols = oa.cols();
        Rcpp::NumericVector perm;
        std::vector<int> ranks(q);
        // Permute the symbols in each column
        for (size_t j = 0; j < cols; j++)
        {
            perm = Rcpp::runif(q);
            oacpp::rutils::findranks_zero<double>(Rcpp::as<std::vector<double> >(perm), ranks);
            for (size_t i = 0; i < rows; i++)
            {
                oa(i,j) = ranks[oa(i,j)];
            }
        }
    }

} // end namespace
