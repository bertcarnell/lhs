#pragma once

#include <cstdlib>
#include <cmath>
#include <exception>
#include <vector>
#include <algorithm>
#include <functional>
/* VISUAL_STUDIO is defined as a preprocessor directive in the build */
#ifndef VISUAL_STUDIO
#include "R.h"
#include "Rmath.h"
#else
#include <cstdio>
#ifndef MATHLIB_STANDALONE
#define MATHLIB_STANDALONE
#include "Rmath.h"
#endif
#endif

#define PRINT_RESULT 0

#ifndef VISUAL_STUDIO
#define PRINT_MACRO Rprintf
#define ERROR_MACRO error
#else
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#endif

int lhsCheck(int * N, int * K, int * result, int bTranspose);
void lhsPrint(int * N, int * K, int * result, int bTranspose);
void lhsPrint_double(int * N, int * K, double * result);

extern "C" {
	void improvedLHS_C(int* N, int* K, int* DUP, int* result, int* avail,
                   int* point1, int* list1, int* vec);
	void maximinLHS_C(int* N, int* K, int* DUP, int* result, int* avail,
                  int* point1, int* list1, int* vec);
	void optimumLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, int* pOld,
                  double* J1, int* J2, int* J3, int* jLen, int* pNew, int* bVerbose);
	void optSeededLHS_C(int* N, int* K, int* MAXSWEEPS, double* EPS, double* pOld,
                  double* J1, int* J2, int* J3, int* jLen, double* pNew, int* bVerbose);
}

/*
 * Function to return the sum of the inverse of the distances between each
 * point in the matrix
 */
template <class T>
double sumInvDistance(T * matrix, int nr, int nc) 
{ 
	T oneDistance = (T) 0;
	double totalInvDistance = 0.0;
	/* iterate the row of the first point from 0 to N-2 */
	for (int i = 0; i < (nr - 1); i++)
	{
		/* iterate the row the second point from i+1 to N-1 */
		for (int j = (i + 1); j < nr; j++)
		{
			oneDistance = 0;
			/* iterate through the columns, summing the squared differences */
			for (int k = 0; k < nc; k++)
			{
				/* calculate the square of the difference in one dimension between the
				* points */
				oneDistance += (matrix[i * (nc) + k] - matrix[j * (nc) + k]) * (matrix[i * (nc) + k] - matrix[j * (nc) + k]);
			}
			/* sum the inverse distances */
			totalInvDistance += (1.0 / sqrt((double) oneDistance));
		}
	}
	return(totalInvDistance);
}

inline
int arrayLocation(int dim1Index, int dim2Index, int dim2Length, int max)
{
	int result = dim1Index * dim2Length + dim2Index;
#ifdef _DEBUG
	if (result >= max)
		throw new std::exception("arrayLocation out of bounds");
#endif
	return result;
}

void rank(std::vector<double> & toRank, std::vector<int> & ranks);
void rankColumns(std::vector<double> & toRank, std::vector<int> & ranks, int nrow);