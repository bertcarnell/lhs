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
 * "pOld", "pNew", and "matrix" are matricies but are treated as one
 * dimensional arrays to facilitate passing them from R.
 * Dimensions:  pOld    N x K
 *              pNew    N x K
 *              J1, J2, J3, jLen = N choose 2 + 1
 * Parameters:
 *              N:         The number of points to be sampled
 *              K:         The number of dimensions (or variables) needed
 *              MAXSWEEPS: The maximum number of times the exchange algorithm
 *                         is applied across the columns.  Therefor if
 *                         MAXSWEEPS =5 and K = 6 then 30 exchange operations
 *                         could be used.
 *              EPS:       The minimum fraction gained in optimality that is
 *                         desired to continue the iterations as a fraction of
 *                         the gain from the first interchange
 * References:  Please see the package documentation
 *
 */

/*
 * Return an optimized hypercube according to the criteria given
 *
 */
void optimumLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, int* pOld,
                  double* J1, int* J2, int* J3, int* jLen, int* pNew)
{
	double gOld;
	double deltag1 = 0.0;
	double deltag;
	int test, iter, i, j, k, r, posit, row, col;

	/* find the initial optimality measure */
	gOld = sumInvDistance_int(pOld, N, K);

	PRINT_MACRO("Beginning Optimality Criterion %f \n", gOld);

#if PRINT_RESULT
	lhsPrint(N, K, pOld, 1);
#endif

	test = 0;
	iter = 0;
	j = 0;

	while (test == 0)
	{
		if (iter == *MAXSWEEPS) break;
		iter++;
		/* iterate over the columns */
		for (j = 0; j < *K; j++)
		{
			r = 0;
			/* iterate over the rows for the first point from 0 to N-2 */
			for (i = 0; i < (*N - 1); i++)
			{
				/* iterate over the rows for the second point from i+1 to N-1 */
				for (k = (i + 1); k < *N; k++)
				{
				/* put the values from pOld into pNew */
					for (row = 0; row < *N; row++)
					{
						for (col = 0; col < *K; col++)
						{
							pNew[row * (*K) + col] = pOld[row * (*K) + col];
						}
					}
					/* exchange two values (from the ith and kth rows) in the jth column
					* and place them in the new matrix */
					pNew[i * (*K) + j] = pOld[k * (*K) + j];
					pNew[k * (*K) + j] = pOld[i * (*K) + j];

					/* store the optimality of the newly created matrix and the rows that
					* were interchanged */
					J1[r] = sumInvDistance_int(pNew, N, K);
					J2[r] = i;
					J3[r] = k;
					r++;
				}
			}
			/* once all combinations of the row interchanges have been completed for
			* the current column j, store the old optimality measure (the one we are
			* trying to beat) */
			J1[r] = gOld;
			J2[r] = 0;
			J3[r] = 0;

			/* Find which optimality measure is the lowest for the current column.
			* In other words, which two row interchanges made the hypercube better in
			* this column */
			posit = 0;
			for (k = 0; k < *jLen; k++)
			{
				if (J1[k] < J1[posit]) posit = k;
			}

			/* If the new minimum optimality measure is better than the old measure */
			if (J1[posit] < gOld)
			{
				/* put pOld in pNew */
				for (row = 0; row < *N; row++)
				{
					for (col = 0; col < *K; col++)
					{
						pNew[row * (*K) + col] = pOld[row * (*K) + col];
					}
				}
				/* Interchange the rows that were the best for this column */
				pNew[J2[posit] * (*K) + j] = pOld[J3[posit] * (*K) + j];
				pNew[J3[posit] * (*K) + j] = pOld[J2[posit] * (*K) + j];

				/* put pNew back in pOld for the next iteration */
				for (row = 0; row < *N; row++)
				{
					for (col = 0; col < *K; col++)
					{
						pOld[row * (*K) + col] = pNew[row * (*K) + col];
					}
				}

				/* if this is not the first column we have used for this sweep */
				if (j > 0)
				{
					/* check to see how much benefit we gained from this sweep */
					deltag = fabs(J1[posit] - gOld);
					if (deltag < ((*EPS) * deltag1))
					{
						test = 1;
						PRINT_MACRO("Algorithm stopped when the change in the inverse distance measure was smaller than %f \n", ((*EPS) * deltag1));
					}
				}
				/* if this is first column of the sweep, then store the benefit gained */
				else
				{
					deltag1 = fabs(J1[posit] - gOld);
				}

				/* replace the old optimality measure with the current one */
				gOld = J1[posit];
			}
			/* if the new and old optimality measures are equal */
			else if (J1[posit] == gOld)
			{
				test = 1;
				PRINT_MACRO("Algorithm stopped when changes did not impove design optimality\n");
			}
			/* if the new optimality measure is worse */
			else if (J1[posit] > gOld)
			{
				ERROR_MACRO("Unexpected Result: Algorithm produced a less optimal design\n");
				test = 1;
			}
			/* if there is a reason to exit... */
			if (test == 1) break;
		}
	}

	/* if we made it through all the sweeps */
	if (iter == *MAXSWEEPS)
	{
		PRINT_MACRO("%d full sweeps completed\n", *MAXSWEEPS);
	}
	/* if we didn't make it through all of them */
	else
	{
		PRINT_MACRO("Algorithm used %d sweep(s) and %d extra column(s)\n", iter-1, j);
	}

	PRINT_MACRO("Final Optimality Criterion %f \n", gOld);

	test = lhsCheck(N, K, pOld, 1);

	if (test == 0)
	{
		/* the error function should send an error message through R */
		ERROR_MACRO("Invalid Hypercube\n");
	}

#if PRINT_RESULT
	lhsPrint(N, K, pOld, 1);
#endif
}
