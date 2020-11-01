/**
 * @file utilityLHS.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
 * 
 * License <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
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

#include "utilityLHS.h"

namespace lhslib
{
    bool isValidLHS(const bclib::matrix<int> & result)
    {
        int total = 0;
        msize_type cols = result.colsize();
        msize_type rows = result.rowsize();
        /*
        * verify that the result is a latin hypercube.  One easy check is to ensure
        * that the sum of the rows is the sum of the 1st N integers.  This check can
        * be fooled in one unlikely way...
        * if a column should be 1 2 3 4 6 8 5 7 9 10
        * the sum would be 10*11/2 = 55
        * the same sum could come from 5 5 5 5 5 5 5 5 5 10
        * but this is unlikely
        */
        // sum each column
        for (msize_type jcol = 0; jcol < cols; jcol++)
        {
            total = 0;
            for (msize_type irow = 0; irow < rows; irow++)
            {
                total += result(irow, jcol);
            }
            if (total != static_cast<int>(rows * (rows + 1) / 2))
            {
                return false;
            }
        }
        return true;
    }
    
    bool isValidLHS(const bclib::matrix<double> & result)
    {
        msize_type n = result.rowsize();
        msize_type k = result.colsize();
        bclib::matrix<int> resultint = bclib::matrix<int>(n, k);
        bclib::matrix<double>::const_iterator it = result.begin();
        bclib::matrix<int>::iterator iti = resultint.begin();
        for (;it != result.end(); ++it, ++iti)
        {
            *iti = 1 + static_cast<int>(floor(static_cast<double>(n) * (*it)));
        }
        bool ret = isValidLHS(resultint);        
        return ret;
    }

    void initializeAvailableMatrix(bclib::matrix<int> & avail)
    {
        // avail is k x n
        for (msize_type irow = 0; irow < avail.rowsize(); irow++)
        {
            for (msize_type jcol = 0; jcol < avail.colsize(); jcol++)
            {
                avail(irow, jcol) = static_cast<int>(jcol + 1);
            }
        }
    }
    
    void runif_std(unsigned int n, std::vector<double> & output, bclib::CRandom<double> & oRandom)
    {
        if (output.size() != n)
        {
            output.resize(n);
        }
        for (unsigned int i = 0; i < n; i++)
        {
            output[i] = oRandom.getNextRandom();
        }
    }

} // end namespace
