/**
 * @file optimumLHS.cpp
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
/*
 * Arrays are passed into this routine to allow R to allocate and deallocate
 * memory within the wrapper function.
 *
 * Dimensions:  oldHypercube    N x K
 *              optimalityRecordLength = N choose 2 + 1
 * Parameters:
 *              N:         The number of points to be sampled
 *              K:         The number of dimensions (or variables) needed
 *              maxSweeps: The maximum number of times the exchange algorithm
 *                         is applied across the columns.  Therefor if
 *                         MAXSWEEPS =5 and K = 6 then 30 exchange operations
 *                         could be used.
 *              eps:       The minimum fraction gained in optimality that is
 *                         desired to continue the iterations as a fraction of
 *                         the gain from the first interchange
 * References:  Please see the package documentation
 *
 */

namespace lhslib
{
/*
 * Return an optimized hypercube according to the criteria given
 *
 */
    void optimumLHS(int n, int k, int maxSweeps, double eps, bclib::matrix<int> & outlhs,
                    int optimalityRecordLength, bclib::CRandom<double> & oRandom, bool bVerbose)
    {
        if (n < 1 || k < 1 || maxSweeps < 1 || eps <= 0)
        {
            throw std::runtime_error("nsamples or nparameters or maxSweeps are less than 1 or eps <= 0");
        }
        unsigned int nOptimalityRecordLength = static_cast<unsigned int>(optimalityRecordLength);
        msize_type nsamples = static_cast<msize_type>(n);
        msize_type nparameters = static_cast<msize_type>(k);
        unsigned int nMaxSweeps = static_cast<unsigned int>(maxSweeps);
        double eps_change = eps;

        int extraColumns = 0;
        double gOptimalityOld;
        double optimalityChangeOld = 0.0;
        double optimalityChange;
        int test;
        unsigned int iter, posit, optimalityRecordIndex;

        if (outlhs.rowsize() != nsamples || outlhs.colsize() != nparameters)
        {
            outlhs = bclib::matrix<int>(nsamples, nparameters);
        }
        //matrix_unsafe<int> oldHypercube_new = matrix_unsafe<int>(nsamples, nparameters, oldHypercube, true);
        bclib::matrix<int> newHypercube = bclib::matrix<int>(nsamples, nparameters);
        std::vector<double> optimalityRecord = std::vector<double>(nOptimalityRecordLength);
        std::vector<unsigned int> interchangeRow1 = std::vector<unsigned int>(nOptimalityRecordLength);
        std::vector<unsigned int> interchangeRow2 = std::vector<unsigned int>(nOptimalityRecordLength);

        // fill the oldHypercube with a random lhs sample
        std::vector<double> randomUnif(nsamples);
        std::vector<int> orderedUnif(nsamples);
        for (msize_type jcol = 0; jcol < nparameters; jcol++)
        {
            // fill a vector with a random sample to order
            for (msize_type irow = 0; irow < nsamples; irow++)
            {
                randomUnif[irow] = oRandom.getNextRandom();
            }
            bclib::findorder<double>(randomUnif, orderedUnif);
            for (msize_type irow = 0; irow < nsamples; irow++)
            {
                outlhs(irow,jcol) = orderedUnif[irow];
            }
        }
        
        /* find the initial optimality measure */
        gOptimalityOld = sumInvDistance<int>(outlhs);

        if (bVerbose)
        {
            PRINT_MACRO << "Beginning Optimality Criterion " << gOptimalityOld << " \n"; // LCOV_EXCL_LINE
        }

#if PRINT_RESULT
        lhsPrint<int>(outlhs, 1);
#endif

        test = 0;
        iter = 0;

        while (test == 0)
        {
            if (iter == nMaxSweeps) 
            {
                break;
            }
            iter++;
            /* iterate over the columns */
            for (msize_type j = 0; j < nparameters; j++)
            {
                optimalityRecordIndex = 0;
                /* iterate over the rows for the first point from 0 to N-2 */
                for (msize_type i = 0; i < (nsamples - 1); i++)
                {
                    /* iterate over the rows for the second point from i+1 to N-1 */
                    for (msize_type kindex = (i + 1); kindex < nsamples; kindex++)
                    {
                        /* put the values from oldHypercube into newHypercube */
                        copyMatrix<int>(newHypercube, outlhs);

                        /* exchange two values (from the ith and kth rows) in the jth column
                        * and place them in the new matrix */
                        newHypercube(i, j) = outlhs(kindex, j);
                        newHypercube(kindex, j) = outlhs(i, j);

                        /* store the optimality of the newly created matrix and the rows that
                        * were interchanged */
                        optimalityRecord[optimalityRecordIndex] = sumInvDistance<int>(newHypercube);
                        interchangeRow1[optimalityRecordIndex] = static_cast<unsigned int>(i);
                        interchangeRow2[optimalityRecordIndex] = static_cast<unsigned int>(kindex);
                        optimalityRecordIndex++;
                    }
                }
                /* once all combinations of the row interchanges have been completed for
                * the current column j, store the old optimality measure (the one we are
                * trying to beat) */
                optimalityRecord[optimalityRecordIndex] = gOptimalityOld;
                interchangeRow1[optimalityRecordIndex] = 0;
                interchangeRow2[optimalityRecordIndex] = 0;

                /* Find which optimality measure is the lowest for the current column.
                * In other words, which two row interchanges made the hypercube better in
                * this column */
                posit = 0;
                for (vsize_type kindex = 0; kindex < nOptimalityRecordLength; kindex++)
                {
                    if (optimalityRecord[kindex] < optimalityRecord[posit]) 
                    {
                        posit = static_cast<unsigned int>(kindex);
                    }
                }

                /* If the new minimum optimality measure is better than the old measure */
                if (optimalityRecord[posit] < gOptimalityOld)
                {
                    /* put oldHypercube in newHypercube */
                    copyMatrix(newHypercube, outlhs);

                    /* Interchange the rows that were the best for this column */
                    newHypercube(interchangeRow1[posit], j) = outlhs(interchangeRow2[posit], j);
                    newHypercube(interchangeRow2[posit], j) = outlhs(interchangeRow1[posit], j);

                    /* put newHypercube back in oldHypercube for the next iteration */
                    copyMatrix(outlhs, newHypercube);

                    /* if this is not the first column we have used for this sweep */
                    if (j > 0)
                    {
                        /* check to see how much benefit we gained from this sweep */
                        optimalityChange = std::fabs(optimalityRecord[posit] - gOptimalityOld);
                        if (optimalityChange < eps_change * optimalityChangeOld)
                        {
                            test = 1;
                            if (bVerbose)
                            {
                                PRINT_MACRO << "Algorithm stopped when the change in the inverse distance measure was smaller than " << ((eps_change)* optimalityChangeOld) << " \n"; // LCOV_EXCL_LINE
                            }
                        }
                    }
                    /* if this is first column of the sweep, then store the benefit gained */
                    else
                    {
                        optimalityChangeOld = std::fabs(optimalityRecord[posit] - gOptimalityOld);
                    }

                    /* replace the old optimality measure with the current one */
                    gOptimalityOld = optimalityRecord[posit];
                }
                /* if the new and old optimality measures are equal */
                else if (optimalityRecord[posit] == gOptimalityOld)
                {
                    test = 1;
                    if (bVerbose)
                    {
                        PRINT_MACRO << "Algorithm stopped when changes did not improve design optimality\n"; // LCOV_EXCL_LINE
                    }
                }
                /* if the new optimality measure is worse */
                else if (optimalityRecord[posit] > gOptimalityOld) // LCOV_EXCL_START
                {
                    ERROR_MACRO << "Unexpected Result: Algorithm produced a less optimal design\n";
                    test = 1;
                } // LCOV_EXCL_STOP
                /* if there is a reason to exit... */
                if (test == 1) 
                {
                    break;
                }
                extraColumns++;
            }
        }

        /* if we made it through all the sweeps */
        if (iter == nMaxSweeps)
        {
            if (bVerbose)
            {
                PRINT_MACRO << nMaxSweeps << " full sweeps completed\n"; // LCOV_EXCL_LINE
            }
        }
        /* if we didn't make it through all of them */
        else
        {
            if (bVerbose)
            {
                PRINT_MACRO << "Algorithm used " << (iter-1) << " sweep(s) and " << extraColumns << " extra column(s)\n"; // LCOV_EXCL_LINE
            }
        }

        if (bVerbose)
        {
            PRINT_MACRO << "Final Optimality Criterion " << gOptimalityOld << " \n"; // LCOV_EXCL_LINE
        }

    //#if _DEBUG
        bool btest = isValidLHS(outlhs);

        if (!btest)
        {
            /* the error function should send an error message through R */
            ERROR_MACRO << "Invalid Hypercube\n"; // LCOV_EXCL_LINE
        }
    //#endif

#if PRINT_RESULT
        lhsPrint<int>(outlhs, 1);
#endif
        
    }
} // end namespace
