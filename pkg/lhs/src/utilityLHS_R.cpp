#include "defines.h"
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


int lhsCheck(int * N, int * K, int * result, int bTranspose)
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

void lhsPrint(int * N, int * K, int * result, int bTranspose)
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

void lhsPrint_double(int * N, int * K, double * result)
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

void rank(std::vector<double> & toRank, std::vector<int> & ranks)
{
	size_t len = toRank.size();
#ifdef _DEBUG
	if (toRank.size() != ranks.size())
		throw new std::exception("illegal call in rank");
#endif
	for (size_t i = 0; i < len; i++)
	{
		ranks[i] = 0;
		for (size_t j = 0; j < len; j++)
		{
			if (toRank[i] < toRank[j])
				ranks[i]++;
		}
	}
}

void rankColumns(std::vector<double> & toRank, std::vector<int> & ranks, int nrow)
{
	size_t n = static_cast<size_t>(nrow);
	std::vector<double> column = std::vector<double>(n);
	size_t len = toRank.size();
	int offset;
#ifdef _DEBUG
	if (toRank.size() != ranks.size())
		throw new std::exception("illegal call in rank");
#endif
	for (size_t i = 0; i < len; i+=n)
	{
		// copy the first nrow
		for (size_t j = 0; j < n; j++)
		{
			column[j] = toRank[i+j];
		}
		// sort
		std::sort(column.begin(), column.end(), std::less<double>());
		// find the sorted number that is the same as the number to rank
		for (size_t j = 0; j < n; j++)
		{
			offset = static_cast<int>(i);
			ranks[i+j] = std::find(toRank.begin()+offset, toRank.begin()+offset+nrow, column[j]) - (toRank.begin()+offset);
		}
	}
}

