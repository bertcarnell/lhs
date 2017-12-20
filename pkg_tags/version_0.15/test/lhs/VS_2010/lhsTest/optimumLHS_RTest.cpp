#include "optimumLHS_RTest.h"

namespace lhsTest{
	void optimumLHS_RTest::Run()
	{
		printf("\toptimumLHS_RTest...");
		testOptimumLHS_R();
		testStress();
		printf("passed\n");
	}

	void optimumLHS_RTest::testOptimumLHS_R()
	{
		int n = 4;
		int k = 3;
		int maxSweeps = 2;
		double eps = 0.1;
		int * pOld = new int[n*k];
		int * pNew = new int[n*k];
		int jLen = 7; // 4 choose 2 + 1
		double * J1 = new double[jLen];
		int * J2 = new int[jLen];
		int * J3 = new int[jLen];
		int iVerbose = 0;
		std::vector<double> toRank = std::vector<double>(n*k);
		std::vector<int> ranks = std::vector<int>(n*k);

		set_seed(1976, 1968);

		for (size_t i = 0; i < toRank.size(); i++)
			toRank[i] = unif_rand();
		utilityLHS::rankColumns(toRank, ranks, n);
		for (size_t i = 0; i < ranks.size(); i++)
			ranks[i]++;
		// transpose
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
			{
				pOld[i*k+j] = ranks[j*n+i];
			}
		}

		optimumLHS_C(&n, &k, &maxSweeps, &eps, pOld, &jLen, &iVerbose);
		int expected[12] = {1,2,3,4,2,4,3,1,3,1,4,2};

		// transpose to compare
		for (int i = 0; i < k; i++) // columns
		{
			for (int j = 0; j < n; j++) // rows
			{
				Assert(expected[i*n+j] == pOld[j*k+i], "Failed 1");
			}
		}
	}


/*
require(lhs)

RNGkind("Marsaglia-Multicarry")
RNGkind()
.Random.seed

.Random.seed <- as.integer(c(401, 1976, 1968))
.Random.seed
floor(4*optimumLHS(4,3,2,0.1))+1
.Random.seed
*/

		void optimumLHS_RTest::testStress()
		{
			int n = 4;
			int k = 3;
			int maxSweeps = 2;
			double eps = 0.1;
			int * pOld = new int[n*k];
			int * pNew = new int[n*k];
			int jLen = 7; // 4 choose 2 + 1
			double * J1 = new double[jLen];
			int * J2 = new int[jLen];
			int * J3 = new int[jLen];
			int iVerbose = 0;
			std::vector<double> toRank = std::vector<double>(n*k);
			std::vector<int> ranks = std::vector<int>(n*k);

			set_seed(1976, 1968);

			for (size_t i = 0; i < toRank.size(); i++)
				toRank[i] = unif_rand();
			utilityLHS::rankColumns(toRank, ranks, n);
			for (size_t i = 0; i < ranks.size(); i++)
				ranks[i]++;
			// transpose
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < k; j++)
				{
					pOld[i*k+j] = ranks[j*n+i];
				}
			}

			for (int i = 0; i < 10000; i++)
				optimumLHS_C(&n, &k, &maxSweeps, &eps, pOld, &jLen, &iVerbose);
		}
}