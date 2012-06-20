/*
 *
 * optimumLHS_R.c: A C routine for creating Optimum Latin Hypercube Samples
 *                 used in the LHS package
 * Copyright (C) 2006  Robert Carnell
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
 * This code uses ISO C90 comment styles and layout
 *
 * "oldHypercube", "newHypercube", and "matrix" are matricies but are treated as one
 * dimensional arrays to facilitate passing them from R.
 * Dimensions:  oldHypercube    N x K
 *              newHypercube    N x K
 *              optimalityRecord, interchangeRow1, interchangeRow2, optimalityRecordLength = N choose 2 + 1
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
                  double* optimalityRecord, int* interchangeRow1, int* interchangeRow2, 
				  int* optimalityRecordLength, int* newHypercube, int* bVerbose)
{
	int nOptimalityRecordLength = *optimalityRecordLength;
	int nsamples = *N;
	int nparameters = *K;
	bool isVerbose = static_cast<bool>(*bVerbose);
	int nMaxSweeps = *maxSweeps;
	double eps_change = *eps;

	int extraColumns = 0;
	double gOptimalityOld;
	double optimalityChangeOld = 0.0;
	double optimalityChange;
	int test, iter, optimalityRecordIndex, posit;

	/* find the initial optimality measure */
	gOptimalityOld = sumInvDistance(oldHypercube, nsamples, nparameters);

	if (isVerbose)
		PRINT_MACRO("Beginning Optimality Criterion %f \n", gOptimalityOld);

#if PRINT_RESULT
	lhsPrint(N, K, oldHypercube, 1);
#endif

	test = 0;
	iter = 0;

	while (test == 0)
	{
		if (iter == nMaxSweeps) break;
		iter++;
		/* iterate over the columns */
		for (int j = 0; j < nparameters; j++)
		{
			optimalityRecordIndex = 0;
			/* iterate over the rows for the first point from 0 to N-2 */
			for (int i = 0; i < (nsamples - 1); i++)
			{
				/* iterate over the rows for the second point from i+1 to N-1 */
				for (int k = (i + 1); k < nsamples; k++)
				{
				/* put the values from oldHypercube into newHypercube */
					for (int row = 0; row < nsamples; row++)
					{
						for (int col = 0; col < nparameters; col++)
						{
							//newHypercube[row * (nparameters) + col] = oldHypercube[row * (nparameters) + col];
							newHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)];
						}
					}
					/* exchange two values (from the ith and kth rows) in the jth column
					* and place them in the new matrix */
					//newHypercube[i * (nparameters) + j] = oldHypercube[k * (nparameters) + j];
					newHypercube[arrayLocation(i, j, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(k, j, nparameters, nsamples*nparameters)];
					//newHypercube[k * (nparameters) + j] = oldHypercube[i * (nparameters) + j];
					newHypercube[arrayLocation(k, j, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(i, j, nparameters, nsamples*nparameters)];

					/* store the optimality of the newly created matrix and the rows that
					* were interchanged */
					optimalityRecord[optimalityRecordIndex] = sumInvDistance(newHypercube, nsamples, nparameters);
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
			for (int k = 0; k < nOptimalityRecordLength; k++)
			{
				if (optimalityRecord[k] < optimalityRecord[posit]) posit = k;
			}

			/* If the new minimum optimality measure is better than the old measure */
			if (optimalityRecord[posit] < gOptimalityOld)
			{
				/* put oldHypercube in newHypercube */
				for (int row = 0; row < nsamples; row++)
				{
					for (int col = 0; col < nparameters; col++)
					{
						//newHypercube[row * (nparameters) + col] = oldHypercube[row * (nparameters) + col];
						newHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)];
					}
				}
				/* Interchange the rows that were the best for this column */
				//newHypercube[interchangeRow1[posit] * (nparameters) + j] = oldHypercube[interchangeRow2[posit] * (nparameters) + j];
				newHypercube[arrayLocation(interchangeRow1[posit], j, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(interchangeRow2[posit], j, nparameters, nsamples*nparameters)];
				//newHypercube[interchangeRow2[posit] * (nparameters) + j] = oldHypercube[interchangeRow1[posit] * (nparameters) + j];
				newHypercube[arrayLocation(interchangeRow2[posit], j, nparameters, nsamples*nparameters)] = oldHypercube[arrayLocation(interchangeRow1[posit], j, nparameters, nsamples*nparameters)];

				/* put newHypercube back in oldHypercube for the next iteration */
				for (int row = 0; row < nsamples; row++)
				{
					for (int col = 0; col < nparameters; col++)
					{
						//oldHypercube[row * (nparameters) + col] = newHypercube[row * (nparameters) + col];
						oldHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)] = newHypercube[arrayLocation(row, col, nparameters, nsamples*nparameters)];
					}
				}

				/* if this is not the first column we have used for this sweep */
				if (j > 0)
				{
					/* check to see how much benefit we gained from this sweep */
					optimalityChange = fabs(optimalityRecord[posit] - gOptimalityOld);
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
					optimalityChangeOld = fabs(optimalityRecord[posit] - gOptimalityOld);
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
	test = lhsCheck(N, K, oldHypercube, 1);

	if (test == 0)
	{
		/* the error function should send an error message through R */
		ERROR_MACRO("Invalid Hypercube\n");
	}
#endif

#if PRINT_RESULT
	lhsPrint(N, K, oldHypercube, 1);
#endif
}
