#include <cmath>
/* VISUAL_STUDIO is defined as a preprocessor directive in the build */
#ifndef VISUAL_STUDIO
#include <R.h>
#else
#include <stdio.h>
#endif

#ifndef VISUAL_STUDIO
#define PRINT_MACRO Rprintf
#define ERROR_MACRO error
#else
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#endif


extern "C" int lhsCheck(int * N, int * K, int * result, int bTranspose)
{
	int total = 0;
	/*
	* verify that the result is a latin hypercube.  One easy check is to ensure
	* that the sum of the rows is the sum of the 1st N integers.  This check can
	* be fooled in one unlikely way...
	* if a column should be 1 2 3 4 6 8 5 7 9 10
	* the sum would be 10*11/2 = 55
	* the same sum could come from 5 5 5 5 5 5 5 5 5 10
	* but this is unlikely
	*/
	if (bTranspose == 0)
	{
		for (int row = 0; row < *K; row++)
		{
			total = 0;
			for (int col = 0; col < *N; col++)
			{
				total += result[row * (*N) + col];
			}
			if (total != (*N) * ((*N) + 1) / 2) return 0;
		}
	}
	else
	{
		for (int col = 0; col < *K; col++)
		{
			total = 0;
			for (int row = 0; row < *N; row++)
			{
				total += result[row * (*K) + col];
			}
			if (total != (*N) * ((*N) + 1) / 2) return 0;
		}
	}
	return 1;
}

extern "C" void lhsPrint(int * N, int * K, int * result, int bTranspose)
{
	if (bTranspose == 0)
	{
		for (int row = 0; row < *K; row++)
		{
			for (int col = 0; col < *N; col++)
			{
				PRINT_MACRO("%d ", result[row * (*N) + col]);
			}
			PRINT_MACRO("\n");
		}
	}
	else
	{
		for (int row = 0; row < *N; row++)
		{
			for (int col = 0; col < *K; col++)
			{
				PRINT_MACRO("%d ", result[row * (*K) + col]);
			}
			PRINT_MACRO("\n");
		}
	}
}

extern "C" void lhsPrint_double(int * N, int * K, double * result)
{
	// always bTranspose == 1
	for (int row = 0; row < *N; row++)
	{
		for (int col = 0; col < *K; col++)
		{
			PRINT_MACRO("%g ", result[row * (*K) + col]);
		}
		PRINT_MACRO("\n");
	}
}

/*
 * Function to return the sum of the inverse of the distances between each
 * point in the matrix
 *
 * Can't have a template in C, so use the template in c++ and expose the functions using extern "C"
 */
template <class T>
double sumInvDistance(T * matrix, int* nr, int* nc) 
{ 
	T oneDistance = (T) 0;
	double totalInvDistance = 0.0;
	/* iterate the row of the first point from 0 to N-2 */
	for (int i = 0; i < (*nr - 1); i++)
	{
		/* iterate the row the second point from i+1 to N-1 */
		for (int j = (i + 1); j < *nr; j++)
		{
			oneDistance = 0;
			/* iterate through the columns, summing the squared differences */
			for (int k = 0; k < *nc; k++)
			{
				/* calculate the square of the difference in one dimension between the
				* points */
				oneDistance += (matrix[i * (*nc) + k] - matrix[j * (*nc) + k]) * (matrix[i * (*nc) + k] - matrix[j * (*nc) + k]);
			}
			/* sum the inverse distances */
			totalInvDistance += (1.0 / sqrt((double) oneDistance));
		}
	}
	return(totalInvDistance);
}

extern "C" double sumInvDistance_double(double * matrix, int * nr, int * nc)
{
	return sumInvDistance(matrix, nr, nc);
}

extern "C" double sumInvDistance_int(int * matrix, int * nr, int * nc)
{
	return sumInvDistance(matrix, nr, nc);
}

