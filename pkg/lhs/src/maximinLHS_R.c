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

#include <math.h>
#include <float.h>
#include <limits.h>
#include <R.h>
#include <Rmath.h>

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
 *              DUP: The duplication factor which affects the number of points
 *                   that the optimization algorithm has to choose from
 * References:  Please see the package documentation
 *
 */

#define printResult 0

void maximinLHS_C(int* N, int* K, int* DUP, int* result, int* avail,
                   int* point1, int* list1, int* vec)
{
  /* distance between corner (1,1,1,..) and (N,N,N,...) */
  double corners = sqrt((double) *K * (*N - 1) * (*N - 1));
  /* iterators */
  int row, col;
  int count;
  int j, k;
  /* index of the current candidate point */
  int point_index;
  /* index of the optimum point */
  int best;
  /* the squared distance between points */
  unsigned int distSquared;
  /*
   * the minimum distance between points
   */
  double max_all;
  /*  The minumum candidate squared difference between points */
  unsigned int min_candidate;
  /* the length of the point1 columns and the list1 vector */
  int len = *DUP * (*N - 1);
  /* used in testing the output */
  int total;
  int test = 1;

  /* initialize the avail matrix */
  for(row = 0; row < *K; row++)
  {
	  for(col = 0; col < *N; col++)
	  {
		  avail[row * (*N) + col] = col + 1;
	  }
  }

  /*
   * come up with an array of K integers from 1 to N randomly
   * and put them in the last column of result
   */
  GetRNGstate();

  for(row = 0; row < *K; row++)
  {
    result[row * (*N) + ((*N) - 1)] = (int) floor(unif_rand() * (*N) + 1);
  }

  /*
   * use the random integers from the last column of result to place an N value
   * randomly through the avail matrix
   */
  for(row = 0; row < *K; row++)
  {
	  avail[row * (*N) + (result[row * (*N) + ((*N) - 1)] - 1)] = *N;
  }

  /* move backwards through the result matrix columns */
  for(count = (*N - 1); count > 0; count--)
  {
	  for(row = 0; row < *K; row++)
	  {
      for(col = 0; col < *DUP; col++)
		  {
        /* create the list1 vector */
			  for(j = 0; j < count; j++)
			  {
          list1[(j + count*col)] = avail[row * (*N) + j];
			  }
		  }
		  /* create a set of points to choose from */
		  for(col = (count * (*DUP)); col > 0; col--)
		  {
        point_index = (int) floor(unif_rand() * col + 1);
			  point1[row * len + (col-1)] = list1[point_index];
			  list1[point_index] = list1[(col-1)];
      }
    }
	  max_all = DBL_MIN;
	  best = 0;
	  for(col = 0; col < ((*DUP) * count - 1); col++)
	  {
      min_candidate = corners;
		  for(j = count; j < *N; j++)
		  {
			  distSquared = 0;
			  /*
         * find the distance between candidate points and the points already
			   * in the sample
			   */
			  for(k = 0; k < *K; k++)
			  {
				  vec[k] = point1[k * len + col] - result[k * (*N) + j];
				  distSquared += vec[k] * vec[k];
			  }
			  /*
         * if the distSquard value is the smallest so far place it in
			   * min candidate
			   */
			  if(min_candidate > distSquared) min_candidate = distSquared;
		  }
		  /*
       * if the difference between min candidate and OPT2 is the smallest so
		   * far, then keep that point as the best.
		   */
		  if(min_candidate > max_all)
		  {
        max_all = min_candidate;
        best = col;
		  }
    }

    /* take the best point out of point1 and place it in the result */
	  for(row = 0; row < *K; row++){
      result[row * (*N) + (count-1)] = point1[row * len + best];
	  }
	  /* update the numbers that are available for the future points */
	  for(row = 0; row < *K; row++)
	  {
      for(col = 0; col < *N; col++)
		  {
        if(avail[row * (*N) + col]==result[row * (*N) + (count-1)])
			  {
				  avail[row * (*N) + col] = avail[row * (*N) + (count-1)];
			  }
      }
    }
  }

  /*
   * once all but the last points of result are filled in, there is only
   * one choice left
   */
  for(row = 0; row < *K; row++)
  {
	  result[row * (*N) + 0] = avail[row * (*N) + 0];
  }

  /*
   * verify that the result is a latin hypercube.  One easy check is to ensure
   * that the sum of the rows is the sum of the 1st N integers.  This check can
   * be fooled in one unlikely way...
   * if a column should be 1 2 3 4 6 8 5 7 9 10
   * the sum would be 10*11/2 = 55
   * the same sum could come from 5 5 5 5 5 5 5 5 5 10
   * but this is unlikely
   */
  for(row = 0; row < *K; row++)
  {
	  total = 0;
	  for(col = 0; col < *N; col++)
	  {
		  total += result[row * (*N) + col];
	  }
	  if(total != (*N) * ((*N) + 1) / 2) test = 0;
  }
  if(test == 0)
  {
    /* the error function should send an error message through R */
	  error("Invalid Hypercube\n");
  }
  
#if printResult
  
  for(row = 0; row < *K; row++)
  {
	  for(col = 0; col < *N; col++)
	  {
		  Rprintf("%d ", result[row * (*N) + col]);
	  }
	  Rprintf("\n");
  }
  
#endif

  /* Give the state of the random number generator back to R */
	PutRNGstate();
}

