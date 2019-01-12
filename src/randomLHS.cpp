/**
 * @file randomLHS.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LHSCommonDefines.h"
#include "utilityLHS.h"

namespace lhslib 
{
    void randomLHS(int n, int k, bclib::matrix<int> & result, bclib::CRandom<double> & oRandom)
    {
        std::vector<int> orderVector = std::vector<int>(n);
        std::vector<double> randomunif1 = std::vector<double>(n);
        for (int jcol = 0; jcol < k; jcol++)
        {
            for (int irow = 0; irow < n; irow++)
            {
                randomunif1[irow] = oRandom.getNextRandom();
            }
            bclib::findorder<double>(randomunif1, orderVector);
            for (int irow = 0; irow < n; irow++)
            {
                result(irow,jcol) = orderVector[irow];
            }
        }
    }
    
    void randomLHS(int n, int k, bool bPreserveDraw, bclib::matrix<double> & result, bclib::CRandom<double> & oRandom)
    {
        if (n < 1 || k < 1)
        {
            throw std::runtime_error("nsamples are less than 1 (n) or nparameters less than 1 (k)");
        }
        msize_type nsamples = static_cast<msize_type>(n);
        msize_type nparameters = static_cast<msize_type>(k);
        if (result.rowsize() != nsamples || result.colsize() != nparameters)
        {
            throw std::runtime_error("result should be n x k for the lhslib::randomLHS call");
        }
        
        std::vector<double> randomunif1 = std::vector<double>(n);
        std::vector<double> randomunif2;
        std::vector<int> orderVector = std::vector<int>(n);

        if (bPreserveDraw)
        {
            randomunif2 = std::vector<double>(n);
            for (int jcol = 0; jcol < k; jcol++)
            {
                // must be two separate loops for sampling order
                for (int irow = 0; irow < n; irow++)
                {
                    randomunif1[irow] = oRandom.getNextRandom();
                }
                // must be two separate loops for sampling order
                for (int irow = 0; irow < n; irow++)
                {
                    randomunif2[irow] = oRandom.getNextRandom();
                }
                bclib::findorder_zero<double>(randomunif1, orderVector);
                for (int irow = 0; irow < n; irow++)
                {
                    result(irow,jcol) = orderVector[irow] + randomunif2[irow];
                    result(irow,jcol) /= static_cast<double>(n);
                }
            }
        }
        else
        {
            randomunif2 = std::vector<double>(n*k);
            for (int jcol = 0; jcol < k; jcol++)
            {
                for (int irow = 0; irow < n; irow++)
                {
                    randomunif1[irow] = oRandom.getNextRandom();
                }
                bclib::findorder_zero<double>(randomunif1, orderVector);
                for (int irow = 0; irow < n; irow++)
                {
                    result(irow,jcol) = orderVector[irow];
                }
            }
            for (int i = 0; i < n*k; i++)
            {
                randomunif2[i] = oRandom.getNextRandom();
            }
            // TODO: this might not be the right order!!!
            bclib::matrix<double> randomMatrix(n, k, randomunif2);
            for (int jcol = 0; jcol < k; jcol++)
            {
                for (int irow = 0; irow < n; irow++)
                {
                    result(irow,jcol) += randomMatrix(irow, jcol);
                    result(irow,jcol) /= static_cast<double>(n);
                }
            }
        }
    }
} // end namespace
