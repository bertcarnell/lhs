/*
 *
 * maximinLHS_R.c: A C routine for creating Improved Latin Hypercube Samples
 *                  used in the LHS package
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

#include <float.h>
#include <limits.h>
#include "defines.h"

/*
 * Arrays are passed into this routine to allow R to allocate and deallocate
 * memory within the wrapper function.
 * The R internal random numer generator is used that R can set.seed for
 * testing the functions.
 * This code uses ISO C90 comment styles and layout
 * "result", "avail", and "point1" are matricies but are treated as one
 * dimensional arrays to facilitate passing them from R.
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

void maximinLHS_C(int* N, int* K, int* dup, int* result, int* avail,
                  int* point1, int* list1, int* vec)
{
	int nsample = *N;
	int nparameters = *K;
	int duplication = *dup;
	/* distance between corner (1,1,1,..) and (N,N,N,...) */
	double corners = std::sqrt(static_cast<double>(nparameters * (nsample - 1) * (nsample - 1)));
	/* index of the current candidate point */
	int point_index;
	/* index of the optimum point */
	int best;
	/* the squared distance between points */
	unsigned int distSquared;
	/* the minimum distance between points */
	double max_all;
	/*  The minumum candidate squared difference between points */
	unsigned int min_candidate;
	/* the length of the point1 columns and the list1 vector */
	int len = duplication * (nsample - 1);
	/* used in testing the output */
	int test = 1;

	/* initialize the avail matrix */
	for (int row = 0; row < nparameters; row++)
	{
		for (int col = 0; col < nsample; col++)
		{
			//avail[row * nsample + col] = col + 1;
			avail[arrayLocation(row, col, nsample, nsample*nparameters)] = col + 1;
		}
	}

	/*
	* come up with an array of K integers from 1 to N randomly
	* and put them in the last column of result
	*/
#ifndef VISUAL_STUDIO
	GetRNGstate();
#endif

	for (int row = 0; row < nparameters; row++)
	{
		//result[row * (nsample) + ((nsample) - 1)] = static_cast<int>(floor(unif_rand() * static_cast<double>(nsample) + 1/0));
		result[arrayLocation(row, nsample-1, nsample, nsample*nparameters)] = static_cast<int>(std::floor(unif_rand() * static_cast<double>(nsample) + 1.0));
	}

	/*
	* use the random integers from the last column of result to place an N value
	* randomly through the avail matrix
	*/
	for (int row = 0; row < nparameters; row++)
	{
		avail[row * (nsample) + (result[row * (nsample) + ((nsample) - 1)] - 1)] = nsample;
	}

	/* move backwards through the result matrix columns */
	for (int count = (nsample - 1); count > 0; count--)
	{
		for (int row = 0; row < nparameters; row++)
		{
			for (int col = 0; col < duplication; col++)
			{
				/* create the list1 vector */
				for (int j = 0; j < count; j++)
				{
					//list1[(j + count*col)] = avail[row * (nsample) + j];
					list1[(j + count*col)] = avail[arrayLocation(row, j, nsample, nsample*nparameters)];
				}
			}
			/* create a set of points to choose from */
			for (int col = (count * (duplication)); col > 0; col--)
			{
				point_index = static_cast<int>(std::floor(unif_rand() * static_cast<double>(col) + 1.0));
				point1[row * len + (col-1)] = list1[point_index];
				list1[point_index] = list1[(col-1)];
			}
		}
		max_all = DBL_MIN;
		best = 0;
		for (int col = 0; col < ((duplication) * count - 1); col++)
		{
			/* set min candidate equal to the maximum distance to start */
			min_candidate = static_cast<unsigned int>(std::ceil(corners));
			for (int j = count; j < nsample; j++)
			{
				distSquared = 0;
				/*
				* find the distance between candidate points and the points already
				* in the sample
				*/
				for (int k = 0; k < nparameters; k++)
				{
					//vec[k] = point1[k * len + col] - result[k * (nsample) + j];
					vec[k] = point1[arrayLocation(k, col, len, nparameters*duplication*(nsample-1))] - result[arrayLocation(k, j, nsample, nsample*nparameters)];
					distSquared += vec[k] * vec[k];
				}
				/*
				* if the distSquard value is the smallest so far place it in
				* min candidate
				*/
				if (min_candidate > distSquared) min_candidate = distSquared;
			}
			/*
			* if the difference between min candidate and OPT2 is the smallest so
			* far, then keep that point as the best.
			*/
			if (min_candidate > max_all)
			{
				max_all = min_candidate;
				best = col;
			}
		}

		/* take the best point out of point1 and place it in the result */
		for (int row = 0; row < nparameters; row++)
		{
			//result[row * (nsample) + (count-1)] = point1[row * len + best];
			result[arrayLocation(row, count-1, nsample, nsample*nparameters)] = point1[arrayLocation(row, best, len, nparameters*duplication*(nsample-1))];
		}
		/* update the numbers that are available for the future points */
		for (int row = 0; row < nparameters; row++)
		{
			for (int col = 0; col < nsample; col++)
			{
				//if (avail[row * (nsample) + col]==result[row * (nsample) + (count-1)])
				if (avail[arrayLocation(row, col, nsample, nsample*nparameters)] == result[arrayLocation(row, count-1, nsample, nsample*nparameters)])
				{
					//avail[row * (nsample) + col] = avail[row * (nsample) + (count-1)];
					avail[arrayLocation(row, col, nsample, nsample*nparameters)] = avail[arrayLocation(row, count-1, nsample, nsample*nparameters)];
				}
			}
		}
	}

	/*
	* once all but the last points of result are filled in, there is only
	* one choice left
	*/
	for (int row = 0; row < nparameters; row++)
	{
		//result[row * (nsample) + 0] = avail[row * (nsample) + 0];
		result[arrayLocation(row, 0, nsample, nsample*nparameters)] = avail[arrayLocation(row, 0, nsample, nsample*nparameters)];
	}

#ifdef _DEBUG
	test = lhsCheck(N, K, result, 0);

	if (test == 0)
	{
		/* the error function should send an error message through R */
		ERROR_MACRO("Invalid Hypercube\n");
	}
#endif

#if PRINT_RESULT
	lhsPrint(N, K, result, 0);
#endif

#ifndef VISUAL_STUDIO
	/* Give the state of the random number generator back to R */
	PutRNGstate();
#endif
}
