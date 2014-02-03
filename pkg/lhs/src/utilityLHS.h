/**
 * @file utilityLHS.h
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

#ifndef UTILITYLHS_H
#define	UTILITYLHS_H

#include "CommonDefines.h"

namespace lhslib
{
    /**
     * is the Latin hypercube sample valid
     * @param result the latin hypercube sample
     * @return the result of the validity check
     */
	bool isValidLHS(const bclib::matrix<int> & result);
    /**
     * rank a vector of doubles
     * @param toRank the vector of values to rank
     * @param ranks the ranks of the vector of values
     */
	void rank(std::vector<double> & toRank, std::vector<int> & ranks);
    /**
     * rank columns
     * @param toRank the vector of values to rank
     * @param ranks the ranks of the vector of values
     * @param nrow the row that is being operated on
     */
	void rankColumns(std::vector<double> & toRank, std::vector<int> & ranks, int nrow);
    /**
     * Initialize the matrix of available points
     * @param avail the matrix of available points
     */
    void initializeAvailableMatrix(bclib::matrix<int> & avail);

    /**
     * print the Latin hypercube sample
     * @param A the matrix to print
     * @param T the type of matrix to print
     */
	template <class T>
	void lhsPrint(const bclib::matrix<T> & A)
	{
        PRINT_MACRO("\n");
        msize_type cols = A.colsize();
        msize_type rows = A.rowsize();
        for (msize_type irow = 0; irow < rows; irow++)
        {
            for (msize_type jcol = 0; jcol < cols; jcol++)
            {
                PRINT_MACRO("%g ", static_cast<double>(A(irow, jcol)));
            }
            PRINT_MACRO("\n");
        }
	}

    /**
     * Sum of the inverse distance between points
     * @param A the matrix to sum
     * @return the sum of the inverse distance between points
     */
	template <class T>
	double sumInvDistance(const bclib::matrix<T> & A)
	{ 
        msize_type nr = A.rowsize();
        msize_type nc = A.colsize();
		T oneDistance;
        T diff;
		double totalInvDistance = 0.0;
		/* iterate the row of the first point from 0 to N-2 */
		for (msize_type irow = 0; irow < nr - 1; irow++)
		{
			/* iterate the row the second point from i+1 to N-1 */
			for (msize_type jrow = (irow + 1); jrow < nr; jrow++)
			{
				oneDistance = static_cast<T>(0);
				/* iterate through the columns, summing the squared differences */
				for (msize_type kcol = 0; kcol < nc; kcol++)
				{
					/* calculate the square of the difference in one dimension between the
					* points */
                    diff = A(irow,kcol) - A(jrow,kcol);
					oneDistance += diff * diff;
				}
				/* sum the inverse distances */
				totalInvDistance += (1.0 / std::sqrt(static_cast<double>(oneDistance)));
			}
		}
		return totalInvDistance;
	}
    
    /**
     * Copy a matrix
     * @param copyTo the matrix to oopy to
     * @param copyFrom the matrix to copy from
     */
    template <class T>
    void copyMatrix(bclib::matrix<T> & copyTo, const bclib::matrix<T> & copyFrom)
    {
        if (copyFrom.rowsize() != copyTo.rowsize() ||
                copyFrom.colsize() != copyTo.colsize())
        {
            throw std::runtime_error("Matrices are not compatible for a copy");
        }
        for (msize_type row = 0; row < copyFrom.rowsize(); row++)
        {
            for (unsigned int col = 0; col < copyFrom.colsize(); col++)
            {
                copyTo(row, col) = copyFrom(row, col);
            }
        }
    }
} // end namespace

#endif	/* UTILITYLHS_H */

