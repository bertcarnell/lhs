/**
 * @file maximinLHS.cpp
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
 * The R internal random number generator is used that R can set.seed for
 * testing the functions.
 * Dimensions:  result  K x N
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
    void maximinLHS(int n, int k, int dup, bclib::matrix<int> & result, bclib::CRandom<double> & oRandom)
    {
        if (n < 1 || k < 1 || dup < 1)
        {
            throw std::runtime_error("nsamples are less than 1 (n) or nparameters less than 1 (k) or duplication is less than 1");
        }
        msize_type nsamples = static_cast<msize_type>(n);
        msize_type nparameters = static_cast<msize_type>(k);
        unsigned int duplication = static_cast<unsigned int>(dup);
        if (result.rowsize() != nsamples || result.colsize() != nparameters)
        {
            throw std::runtime_error("result should be n x k for the lhslib::maximinLHS call");
        }
        result.transpose();
        // *****  matrix_unsafe<int> m_result = matrix_unsafe<int>(nparameters, nsamples, result);
        /* the length of the point1 columns and the list1 vector */
        msize_type len = duplication * (nsamples - 1);
        /* create memory space for computations */
        bclib::matrix<int> avail = bclib::matrix<int>(nparameters, nsamples);
        bclib::matrix<int> point1 = bclib::matrix<int>(nparameters, len);
        std::vector<int> list1 = std::vector<int>(len);
        std::vector<int> vec = std::vector<int>(nparameters);
        /* squared distance between corner (1,1,1,..) and (N,N,N,...) */
        double squaredDistanceBtwnCorners = static_cast<double>(nparameters * (nsamples - 1) * (nsamples - 1));

        /* index of the current candidate point */
        vsize_type point_index;
        /* index of the optimum point */
        unsigned int best;
        /* the squared distance between points */
        unsigned int distSquared;
        /* the minimum squared distance between points */
        double minSquaredDistBtwnPts;
        /*  The minumum candidate squared difference between points */
        unsigned int minCandidateSquaredDistBtwnPts;

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
        for (unsigned int irow = 0; irow < nparameters; irow++)
        {
            avail(irow, static_cast<unsigned int>(result(irow, nsamples - 1) - 1)) = static_cast<int>(nsamples);
        }

        /* move backwards through the result matrix columns */
        for (vsize_type ucount = nsamples - 1; ucount > 0; ucount--)
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
                /* create a set of points to choose from */
                for (msize_type jcol = ucount * duplication; jcol > 0; jcol--)
                {
                    point_index = static_cast<vsize_type>(std::floor(oRandom.getNextRandom() * static_cast<double>(jcol)));
                    point1(irow, jcol-1) = list1[point_index];
                    list1[point_index] = list1[jcol - 1];
                }
            }
            minSquaredDistBtwnPts = DBL_MIN;
            best = 0;
            for (msize_type jcol = 0; jcol < duplication * ucount - 1; jcol++)
            {
                /* set min candidate equal to the maximum distance to start */
                minCandidateSquaredDistBtwnPts = static_cast<unsigned int>(std::ceil(squaredDistanceBtwnCorners));
                for (msize_type j = ucount; j < nsamples; j++)
                {
                    distSquared = 0;
                    /*
                    * find the distance between candidate points and the points already
                    * in the sample
                    */
                    for (msize_type kindex= 0; kindex < nparameters; kindex++)
                    {
                        vec[kindex] = point1(kindex, jcol) - result(kindex, j);
                        distSquared += vec[kindex] * vec[kindex];
                    }
                    /*
                    * if the distance squared value is the smallest so far, place it in the
                    * min candidate
                    */
                    if (minCandidateSquaredDistBtwnPts > distSquared) 
                    {
                        minCandidateSquaredDistBtwnPts = distSquared;
                    }
                }
                /*
                * if the candidate point is the largest minimum distance between points so
                * far, then keep that point as the best.
                */
                if (static_cast<double>(minCandidateSquaredDistBtwnPts) > minSquaredDistBtwnPts)
                {
                    minSquaredDistBtwnPts = static_cast<double>(minCandidateSquaredDistBtwnPts);
                    best = static_cast<unsigned int>(jcol);
                }
            }

            /* take the best point out of point1 and place it in the result */
            for (msize_type irow = 0; irow < nparameters; irow++)
            {
                result(irow, ucount-1) = point1(irow, best);
            }
            /* update the numbers that are available for the future points */
            for (msize_type irow = 0; irow < nparameters; irow++)
            {
                for (msize_type jcol = 0; jcol < nsamples; jcol++)
                {
                    if (avail(irow, jcol) == result(irow, ucount-1))
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
        for (msize_type irow = 0; irow < nparameters; irow++)
        {
            result(irow, 0u) = avail(irow, 0u);
        }

        result.transpose();
    //#ifdef _DEBUG
        bool test = isValidLHS(result);

        if (!test)
        {
            /* the error function should send an error message through R */
            throw std::runtime_error("Invalid Hypercube\n"); // LCOV_EXCL_LINE
        }
    //#endif

    #if PRINT_RESULT
        lhsPrint(result, 0);
    #endif
    }
} // end namespace
