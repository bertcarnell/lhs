/**
 * @file improvedLHS.cpp
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

#include "LHSCommonDefines.h"
#include "utilityLHS.h"

/*
 * Arrays are passed into this routine to allow R to allocate and deallocate
 * memory within the wrapper function.
 * The R internal random numer generator is used so that R can set.seed for
 * testing the functions.
 * This code uses ISO C90 comment styles and layout
 * Dimensions:  result  K x N
 *              avail   K x N
 *              point1  K x DUP(N-1)
 *              list1   DUP(N-1)
 *              vec     K
 * Parameters:
 *              N: The number of points to be sampled
 *              K: The number of dimensions (or variables) needed
 *              dup: The duplication factor which affects the number of points
 *                   that the optimization algorithm has to choose from
 * References:  Please see the package documentation
 *
 */
namespace lhslib
{
    void improvedLHS(int n, int k, int dup, bclib::matrix<int> & result, bclib::CRandom<double> & oRandom)
    {
        if (n < 1 || k < 1 || dup < 1)
        {
            throw std::runtime_error("number of samples (n), number of parameters (k), and duplication must be positive");
        }
        msize_type nsamples = static_cast<msize_type>(n);
        msize_type nparameters = static_cast<msize_type>(k);
        msize_type duplication = static_cast<msize_type>(dup);
        if (nsamples != result.rowsize() || nparameters != result.colsize())
        {
            throw std::runtime_error("result should be n x k for the lhslib::improvedLHS call");
        }
        // now transpose the matrix for future calls
        result.transpose(); // now it is k x n
        // ********** matrix_unsafe<int> m_result = matrix_unsafe<int>(nparameters, nsamples, result);
        /* the length of the point1 columns and the list1 vector */
        msize_type len = duplication * (nsamples - 1);
        /* create memory space for computations */
        bclib::matrix<int> avail = bclib::matrix<int>(nparameters, nsamples);
        bclib::matrix<int> point1 = bclib::matrix<int>(nparameters, len);
        std::vector<int> list1 = std::vector<int>(len);
        std::vector<int> vec = std::vector<int>(nparameters);
        /* optimum spacing between points */
        double opt = static_cast<double>(nsamples) / ( std::pow(static_cast<double>(nsamples), (1.0 / static_cast<double>(nparameters))));
        /* the square of the optimum spacing between points */
        double opt2 = opt * opt;

        /* index of the current candidate point */
        vsize_type point_index;
        /* index of the optimum point */
        unsigned int best;
        /* the squared distance between points */
        unsigned int distSquared;
        /*
        * the minimum difference between the squared distance and the squared
        * optimum distance
        */
        double min_all;
        /*  The minumum candidate squared distance between points */
        unsigned int min_candidate;

        /* initialize the avail matrix */
        initializeAvailableMatrix(avail);

        /*
        * come up with an array of K integers from 1 to N randomly
        * and put them in the last column of result
        */
        for (msize_type irow = 0; irow < nparameters; irow++)
        {
            result(irow, nsamples-1) = static_cast<int>(std::floor(oRandom.getNextRandom() * static_cast<double>(nsamples) + 1.0));
        }

        /*
        * use the random integers from the last column of result to place an N value
        * randomly through the avail matrix
        */
        for (msize_type irow = 0; irow < nparameters; irow++)
        {
            avail(irow, static_cast<msize_type>(result(irow, nsamples-1) - 1)) = static_cast<int>(nsamples);
        }

        /* move backwards through the result matrix columns.*/
        for (msize_type ucount = nsamples - 1; ucount > 0; ucount--)
        {
            //unsigned int ucount = static_cast<unsigned int>(count);
            for (msize_type irow = 0; irow < nparameters; irow++)
            {
                for (msize_type jcol = 0; jcol < duplication; jcol++)
                {
                    /* create the list1 vector */
                    for (vsize_type j = 0; j < ucount; j++)
                    {
                        list1[j + ucount*jcol] = avail(irow, j);
                    }
                }
                /* create a set of points to choose from. Note, need to use int*/
                /* Note: can't do col = count*duplication - 1; col >= 0 because it throws a warning at W4 */
                for (msize_type ujcol = ucount * duplication; ujcol > 0; ujcol--)
                {
                    //unsigned int ujcol = static_cast<unsigned int>(jcol);
                    point_index = static_cast<vsize_type>(std::floor(oRandom.getNextRandom() * static_cast<double>(ujcol)));
                    point1(irow, ujcol-1) = list1[point_index];
                    list1[point_index] = list1[ujcol-1];
                }
            }
            min_all = DBL_MAX;
            best = 0;
            for (msize_type jcol = 0; jcol < duplication * ucount - 1; jcol++)
            {
                min_candidate = UINT_MAX;
                for (msize_type j = ucount; j < nsamples; j++)
                {
                    distSquared = 0;
                    /*
                    * find the distance between candidate points and the points already
                    * in the sample
                    */
                    for (msize_type kindex = 0; kindex < nparameters; kindex++)
                    {
                        vec[kindex] = point1(kindex, jcol) - result(kindex, j);
                        distSquared += vec[kindex] * vec[kindex];
                    }
                    /* original code compared dist1 to opt, but using the square root
                    * function and recasting distSquared to a double was unnecessary.
                    * dist1 = sqrt((double) distSquared);
                    * if (min_candidate > dist1) min_candidate = dist1;
                    */

                    /*
                    * if the distSquard value is the smallest so far place it in
                    * min candidate
                    */
                    if (min_candidate > distSquared) 
                    {
                        min_candidate = distSquared;
                    }
                }
                /*
                * if the difference between min candidate and opt2 is the smallest so
                * far, then keep that point as the best.
                */
                if (std::fabs(static_cast<double>(min_candidate) - opt2) < min_all)
                {
                    min_all = std::fabs(static_cast<double>(min_candidate) - opt2);
                    best = static_cast<unsigned int>(jcol);
                }
            }

            /* take the best point out of point1 and place it in the result */
            for (msize_type irow = 0; irow < nparameters; irow++)
            {
                result(irow, ucount - 1) = point1(irow, best);
            }
            /* update the numbers that are available for the future points */
            for (msize_type irow = 0; irow < nparameters; irow++)
            {
                for (msize_type jcol = 0; jcol < nsamples; jcol++)
                {
                    if (avail(irow, jcol) == result(irow, ucount - 1))
                    {
                        avail(irow, jcol) = avail(irow, ucount-1);
                    }
                }
            }
        }

        /*
        * once all but the last points of result are filled in, there is only
        * one choice left
        */
        for (msize_type jrow = 0; jrow < nparameters; jrow++)
        {
            result(jrow, 0u) = avail(jrow, 0u);
        }
        
        result.transpose();
        
    //#if _DEBUG
        bool test = isValidLHS(result);

        if (!test)
        {
            throw std::runtime_error("Invalid Hypercube\n"); // LCOV_EXCL_LINE
        }
    //#endif

    #if PRINT_RESULT
        lhsPrint(result, 0);
    #endif
    }
} // end namespace
