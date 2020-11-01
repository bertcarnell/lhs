/**
 * @file utilityLHS.h
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

#ifndef UTILITYLHS_H
#define	UTILITYLHS_H

#include "LHSCommonDefines.h"

namespace lhslib
{
    /**
     * is the Latin hypercube sample valid
     * @param result the latin hypercube sample with integer values
     * @return the result of the validity check
     */
	bool isValidLHS(const bclib::matrix<int> & result);
    /**
     * is the Latin hypercube sample valid?
     * @param result the latin hypercube sample
     * @return the result of the validity check
     */
    bool isValidLHS(const bclib::matrix<double> & result);
    
    /**
     * rank a vector of objects
     * @param toRank the vector of objects to rank
     * @param ranks the ranks of the vector of values
     * @tparam the type of element in the vectors
     */
    template <class T>
    void rank(const std::vector<T> & toRank, std::vector<int> & ranks)
    {
        if (toRank.size() != ranks.size())
        {
            ranks.resize(toRank.size(), 0);
        }
        typename std::vector<T>::const_iterator toRank_it1;
        typename std::vector<T>::const_iterator toRank_it2;
        std::vector<int>::iterator ranks_it;
        for (toRank_it1 = toRank.begin(), ranks_it = ranks.begin();
                toRank_it1 != toRank.end() && ranks_it != ranks.end();
                ++toRank_it1, ++ranks_it)
        {
            *ranks_it = 0;
            for (toRank_it2 = toRank.begin(); toRank_it2 != toRank.end(); ++toRank_it2)
            {
                if (*toRank_it1 < *toRank_it2)
                {
                    (*ranks_it)++;
                }
            }
        }
    }
    
    /**
     * Initialize the matrix of available points
     * @param avail the matrix of available points
     */
    void initializeAvailableMatrix(bclib::matrix<int> & avail);

    /**
     * print the Latin hypercube sample
     * @param A the matrix to print
     * @tparam T the type of matrix to print
     */
	template <class T>
	void lhsPrint(const bclib::matrix<T> & A)
	{
        PRINT_MACRO << "\n";
        msize_type cols = A.colsize();
        msize_type rows = A.rowsize();
        for (msize_type irow = 0; irow < rows; irow++)
        {
            for (msize_type jcol = 0; jcol < cols; jcol++)
            {
                PRINT_MACRO << A(irow, jcol) << ", ";
            }
            PRINT_MACRO << "\n";
        }
	}

    /**
     * calculate the squared distance between two values.
     * A type of <code>std::binar_function</code>.
     * @tparam T the type of values for the Arg1, Arg2, and return
     */
    template <class T>
    struct squareDifference : public std::binary_function<T, T, T> /*arg1, arg2, return */
    {
        /**
         * Calculate the squared distance between two values
         * @param x Arg1
         * @param y Arg2
         * @return the <code>(x-y)*(x-y)</code>
         */
        T operator()(const T & x, const T & y) const
        { 
            return (x-y) * (x-y); 
        }
    };
    
    /**
     * Calculate the total squared distance between two vectors
     * @param A the first vector
     * @param B the second vector
     * @tparam T the type of the objects in the vector
     * @return the total squared distance
     */
    template <class T>
    T calculateDistanceSquared(const std::vector<T> & A, const std::vector<T> & B)
    {
        if (A.size() != B.size())
        {
            throw std::runtime_error("Inputs of a different size");
        }
        // sum = sum + (a-b)*(a-b)
        T sum = std::inner_product(A.begin(), A.end(), B.begin(), static_cast<T>(0), std::plus<T>(), squareDifference<T>());
        return sum;
    }

    /**
     * Calculate the distance squared between two sequence of numbers
     * 
     * this was primarily implemented to be able to calculate distances between rows
     * of a matrix without having to copy those rows out
     * 
     * @param Abegin the beginning of the first iterator
     * @param Aend the end of the first iterator
     * @param Bbegin the beginning of the second iterator
     * @tparam T the type of object de-referenced by the iterator
     * @tparam ISROWWISE a boolean to indicate if the iterator operates row-wise in the matrix
     * @return the distance squared
     */
    template <class T, bool ISROWWISE>
    T calculateDistanceSquared(const typename bclib::matrixConstIter<T,ISROWWISE> Abegin, 
            const typename bclib::matrixConstIter<T,ISROWWISE> Aend, 
            const typename bclib::matrixConstIter<T,ISROWWISE> Bbegin)
    {
        // sum = sum + (a-b)*(a-b)
        T sum = std::inner_product(Abegin, Aend, Bbegin, static_cast<T>(0), std::plus<T>(), squareDifference<T>());
        return sum;
    }
    
    /**
     * Calculate the distance between the rows of a matrix
     * @param mat the matrix to calculate distances on
     * @param result the matrix to hold the results of the calculation
     * @tparam T the type of object in the matrix
     */
    template <class T>
    void calculateDistance(const bclib::matrix<T> & mat, bclib::matrix<double> & result)
    {
        msize_type m_rows = mat.rowsize();
        if (result.rowsize() != m_rows || result.colsize() != m_rows)
        {
            result = bclib::matrix<double>(m_rows, m_rows);
        }
        for (msize_type i = 0; i < m_rows - 1; i++)
        {
            for (msize_type j = i+1; j < m_rows; j++)
            {
                typename bclib::matrix<T>::const_rowwise_iterator rowi_begin = mat.rowwisebegin(i);
                typename bclib::matrix<T>::const_rowwise_iterator rowi_end = mat.rowwiseend(i);
                typename bclib::matrix<T>::const_rowwise_iterator rowj_begin = mat.rowwisebegin(j);
                T sum = calculateDistanceSquared<T, true>(rowi_begin, rowi_end, rowj_begin);
                result(i,j) = sqrt(static_cast<double>(sum));
            }
        }
    }

    /**
     * A unary_function to invert a number in a STL algorithm
     * @tparam T the type of number to invert
     * @tparam W the type of the result.  (normally a double or float)
     */
    template <class T, class W>
    struct invert : public std::unary_function<T, W> /*arg1, return */
    {
        /**
         * A unary_function to invert a number
         * @param x the object to invert
         * @return the inverse of x
         */
        W operator()(const T & x) const
        {
            if (x != static_cast<T>(0))
            {
                return 1.0 / static_cast<W>(x);
            }
            else
            {
                return static_cast<W>(x);
            }
        }
    };

    /**
     * sum of the inverse distance between points in a matrix
     * @param A the matrix
     * @tparam T the type of object contained in the matrix
     * @return the sum of the inverse distance between points
     */
 	template <class T>
	double sumInvDistance(const bclib::matrix<T> & A)
    {
        // create a matrix to hold the distances
        bclib::matrix<double> dist = bclib::matrix<double>(A.rowsize(), A.rowsize());
        // calculate the distances between the rows of A
        calculateDistance<T>(A, dist);
        // invert all the distances
        std::transform<bclib::matrix<double>::iterator>(dist.begin(), dist.end(), 
                dist.begin(), invert<double, double>());
        // sum the inverted 
        double totalInvDistance = std::accumulate<bclib::matrix<double>::iterator>(dist.begin(), dist.end(), 0.0);
		return totalInvDistance;
    }

    /**
     * Sum of the inverse distance between points
     * @param A the matrix to sum
     * @tparam T the type of object in the matrix
     * @return the sum of the inverse distance between points
     */
	template <class T>
	double sumInvDistance_deprecated(const bclib::matrix<T> & A)
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
                if (oneDistance != 0)
                {
                    totalInvDistance += (1.0 / sqrt(static_cast<double>(oneDistance)));
                }
			}
		}
		return totalInvDistance;
	}
    
    /**
     * Copy a matrix
     * @param copyTo the matrix to copy to
     * @param copyFrom the matrix to copy from
     * @tparam the type of object contained in the matrix
     */
    template <class T>
    void copyMatrix(bclib::matrix<T> & copyTo, const bclib::matrix<T> & copyFrom)
    {
        if (copyFrom.rowsize() != copyTo.rowsize() ||
                copyFrom.colsize() != copyTo.colsize() ||
                copyFrom.isTransposed() != copyTo.isTransposed())
        {
            throw std::runtime_error("Matrices are not compatible for a copy");
        }
        std::copy<typename bclib::matrix<T>::const_iterator, typename bclib::matrix<T>::iterator>(copyFrom.begin(), copyFrom.end(), copyTo.begin());
    }
    
    /**
     * Calculate the S optimality measure
     * @param mat the matrix to calculate S optimality for
     * @tparam the type of object contained in the matrix
     * @return the S optimality measure
     */
    template <class T>
    double calculateSOptimal(const bclib::matrix<T> & mat)
    {
        //        B[i] <- 1/sum(1/dist(A[, , i]))
        double sum = sumInvDistance<T>(mat);
        return 1.0 / sum;
    }

    /**
     * Create a vector of random values on (0,1)
     * @param n the number of random values
     * @param output the output vector of random values
     * @param oRandom the pseudo random number generator
     */
    void runif_std(unsigned int n, std::vector<double> & output, bclib::CRandom<double> & oRandom);

    /**
     * Create a vector of random integer like values
     * @param n the length of the random vector
     * @param min the minimum integer value
     * @param max the maximum integer value
     * @param output the output vector of values
     * @param oRandom the pseudo random number generator.
     * @tparam T1 the integer valued type like <code>int, unsigned int, long, long long, unsigned long</code>
     */
    template <class T1>
    void runifint(unsigned int n, T1 min, T1 max, std::vector<T1> & output, bclib::CRandom<double> & oRandom)
    {
        if (output.size() != n)
        {
            output.resize(n);
        }
        std::vector<double> r = std::vector<double>(n);
        runif_std(n, r, oRandom);
        typename std::vector<T1>::iterator output_it;
        std::vector<double>::iterator r_it;
        double range = static_cast<double>(max) + 1.0 - static_cast<double>(min);
        for (output_it = output.begin(), r_it = r.begin();
                output_it != output.end() && r_it != r.end(); ++output_it, ++r_it)
        {
            *output_it = min + static_cast<T1>(floor((*r_it) * range));
        }
    }

    /**
     * Create a random integer like values
     * @param min the minimum integer value
     * @param max the maximum integer value
     * @param output the output value
     * @param oRandom the pseudo random number generator
     * @tparam T1 the integer valued type like <code>int, unsigned int, long, long long, unsigned long</code>
     */
    template <class T1>
    void runifint(T1 min, T1 max, T1 * output, bclib::CRandom<double> & oRandom)
    {
        double r = oRandom.getNextRandom();
        double range = static_cast<double>(max) + 1.0 - static_cast<double>(min);
        *output = min + static_cast<T1>(floor((r * range)));
    }
    
} // end namespace

#endif	/* UTILITYLHS_H */

