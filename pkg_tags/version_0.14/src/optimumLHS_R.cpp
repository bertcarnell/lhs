/*
 *
 * optimumLHS_R.cpp: A C++ routine for creating Optimum Latin Hypercube Samples
 *                 used in the LHS package
 * Copyright (C) 2012  Robert Carnell
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "defines.h"

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

/*
 * Return an optimized hypercube according to the criteria given
 *
 */
void optimumLHS_C(int* N, int* K, int* maxSweeps, double* eps, int* oldHypercube,
                  int* optimalityRecordLength, int* bVerbose)
{
	size_t nOptimalityRecordLength = static_cast<size_t>(*optimalityRecordLength);
	size_t nsamples = static_cast<size_t>(*N);
	size_t nparameters = static_cast<size_t>(*K);
	bool isVerbose = (*bVerbose == 0)? false : true; 
	size_t nMaxSweeps = static_cast<size_t>(*maxSweeps);
	double eps_change = *eps;

	int extraColumns = 0;
	double gOptimalityOld;
	double optimalityChangeOld = 0.0;
	double optimalityChange;
	int test;
	size_t iter, posit, optimalityRecordIndex;

	matrix_unsafe<int> oldHypercube_new = matrix_unsafe<int>(nsamples, nparameters, oldHypercube, true);
	matrix<int> newHypercube = matrix<int>(nsamples, nparameters, true);
	std::vector<double> optimalityRecord = std::vector<double>(nOptimalityRecordLength);
	std::vector<size_t> interchangeRow1 = std::vector<size_t>(nOptimalityRecordLength);
	std::vector<size_t> interchangeRow2 = std::vector<size_t>(nOptimalityRecordLength);

	/* find the initial optimality measure */
	gOptimalityOld = utilityLHS::sumInvDistance<int>(oldHypercube_new.values, static_cast<int>(nsamples), static_cast<int>(nparameters));

	if (isVerbose)
		PRINT_MACRO("Beginning Optimality Criterion %f \n", gOptimalityOld);

#if PRINT_RESULT
	utilityLHS::lhsPrint<int>(nsamples, nparameters, oldHypercube, 1);
#endif

	test = 0;
	iter = 0;

	while (test == 0)
	{
		if (iter == nMaxSweeps) break;
		iter++;
		/* iterate over the columns */
		for (size_t j = 0; j < nparameters; j++)
		{
			optimalityRecordIndex = 0;
			/* iterate over the rows for the first point from 0 to N-2 */
			for (size_t i = 0; i < (nsamples - 1); i++)
			{
				/* iterate over the rows for the second point from i+1 to N-1 */
				for (size_t k = (i + 1); k < nsamples; k++)
				{
				/* put the values from oldHypercube into newHypercube */
					for (size_t row = 0; row < nsamples; row++)
					{
						for (size_t col = 0; col < nparameters; col++)
						{
							newHypercube(row, col) = oldHypercube_new(row, col);
						}
					}
					/* exchange two values (from the ith and kth rows) in the jth column
					* and place them in the new matrix */
					newHypercube(i, j) = oldHypercube_new(k, j);
					newHypercube(k, j) = oldHypercube_new(i, j);

					/* store the optimality of the newly created matrix and the rows that
					* were interchanged */
					optimalityRecord[optimalityRecordIndex] = utilityLHS::sumInvDistance<int>(newHypercube.values, nsamples, nparameters);
					interchangeRow1[optimalityRecordIndex] = i;
					interchangeRow2[optimalityRecordIndex] = k;
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
			for (size_t k = 0; k < nOptimalityRecordLength; k++)
			{
				if (optimalityRecord[k] < optimalityRecord[posit]) posit = k;
			}

			/* If the new minimum optimality measure is better than the old measure */
			if (optimalityRecord[posit] < gOptimalityOld)
			{
				/* put oldHypercube in newHypercube */
				for (size_t row = 0; row < nsamples; row++)
				{
					for (size_t col = 0; col < nparameters; col++)
					{
						newHypercube(row, col) = oldHypercube_new(row, col);
					}
				}
				/* Interchange the rows that were the best for this column */
				newHypercube(interchangeRow1[posit], j) = oldHypercube_new(interchangeRow2[posit], j);
				newHypercube(interchangeRow2[posit], j) = oldHypercube_new(interchangeRow1[posit], j);

				/* put newHypercube back in oldHypercube for the next iteration */
				for (size_t row = 0; row < nsamples; row++)
				{
					for (size_t col = 0; col < nparameters; col++)
					{
						oldHypercube_new(row, col) = newHypercube(row, col);
					}
				}

				/* if this is not the first column we have used for this sweep */
				if (j > 0)
				{
					/* check to see how much benefit we gained from this sweep */
					optimalityChange = std::fabs(optimalityRecord[posit] - gOptimalityOld);
					if (optimalityChange < eps_change * optimalityChangeOld)
					{
						test = 1;
						if (isVerbose)
							PRINT_MACRO("Algorithm stopped when the change in the inverse distance measure was smaller than %f \n", ((eps_change) * optimalityChangeOld));
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
				if (isVerbose)
					PRINT_MACRO("Algorithm stopped when changes did not impove design optimality\n");
			}
			/* if the new optimality measure is worse */
			else if (optimalityRecord[posit] > gOptimalityOld)
			{
				ERROR_MACRO("Unexpected Result: Algorithm produced a less optimal design\n");
				test = 1;
			}
			/* if there is a reason to exit... */
			if (test == 1) break;
			extraColumns++;
		}
	}

	/* if we made it through all the sweeps */
	if (iter == nMaxSweeps)
	{
		if (isVerbose)
			PRINT_MACRO("%d full sweeps completed\n", nMaxSweeps);
	}
	/* if we didn't make it through all of them */
	else
	{
		if (isVerbose)
			PRINT_MACRO("Algorithm used %d sweep(s) and %d extra column(s)\n", iter-1, extraColumns);
	}

	if (isVerbose)
		PRINT_MACRO("Final Optimality Criterion %f \n", gOptimalityOld);

#if _DEBUG
	test = utilityLHS::lhsCheck(static_cast<int>(nsamples), static_cast<int>(nparameters), oldHypercube_new.values, 1);

	if (test == 0)
	{
		/* the error function should send an error message through R */
		ERROR_MACRO("Invalid Hypercube\n");
	}
#endif

#if PRINT_RESULT
	utilityLHS::lhsPrint<int>(nsamples, nparameters, oldHypercube_new.values, 1);
#endif
}
