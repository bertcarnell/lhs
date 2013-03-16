#include "maximinLHS_RTest.h"

namespace lhsTest{
	void maximinLHS_RTest::Run()
	{
		printf("\tmaximinLHS_RTest...");
		testMaximinLHS_R();
		testStress();
		printf("passed\n");
	}

	void maximinLHS_RTest::testMaximinLHS_R()
	{
		int n = 4;
		int k = 3;
		int DUP = 5;
		int * result = new int[n*k];
		int * avail = new int[n*k];
		int * point1 = new int[k*DUP*(n-1)];
		int * list1 = new int[DUP*(n-1)];
		int * vec = new int[k];

		set_seed(1976, 1968);
		maximinLHS_C(&n, &k, &DUP, result);

		matrix<int> result_temp = matrix<int>(k, n, result);
		result_temp.transpose();

		//int expected[12] = {2,4,1,3,1,4,3,2,1,3,4,2}; // before correction to point index.  No longer matches R program
		int expected[12] = {4,2,1,3,1,4,3,2,3,1,4,2};
		for (int i = 0; i < n*k; i++)
		{
			Assert(expected[i] == result_temp.values[i], "Failed 1");
		}
	}

/*
require(lhs)

RNGkind("Marsaglia-Multicarry")
RNGkind()
.Random.seed

.Random.seed <- as.integer(c(401, 1976, 1968))
.Random.seed
floor(4*maximinLHS(4,3,5))+1
.Random.seed
*/

		void maximinLHS_RTest::testStress()
		{
			int n = 4;
			int k = 3;
			int DUP = 5;
			int * result = new int[n*k];
			int * avail = new int[n*k];
			int * point1 = new int[k*DUP*(n-1)];
			int * list1 = new int[DUP*(n-1)];
			int * vec = new int[k];

			set_seed(1976, 1968);
			for (int i = 0; i < 10000; i++)
				maximinLHS_C(&n, &k, &DUP, result);
		}
}