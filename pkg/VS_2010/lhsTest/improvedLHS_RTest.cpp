#include "improvedLHS_RTest.h"

namespace lhsTest{
	void improvedLHS_RTest::Run()
	{
		printf("\timprovedLHS_RTest...");
		testImprovedLHS_R();
		testStress();
		printf("passed\n");
	}

	void improvedLHS_RTest::testImprovedLHS_R()
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
		improvedLHS_C(&n, &k, &DUP, result);
		
		matrix<int> result_temp = matrix<int>(k, n, result);
		result_temp.transpose();

		int expected[12] = {1,4,2,3,3,1,4,2,3,4,1,2};
		for (size_t i = 0; i < static_cast<size_t>(n*k); i++)
		{
			Assert(expected[i] == result_temp.values[i], "Failed 1");
		}

		unsigned int a, b;

		set_seed(1976, 1968);
		double temp = unif_rand();
		get_seed(&a, &b);
		Assert(std::abs(temp - 0.66590160146958687903) < 1E-12, "failed RNG test");
		Assert(a == 73050744 && b == 35424000, "failed RNG test2");

		set_seed(1976, 1968);
		improvedLHS_C(&n, &k, &DUP, result);
		get_seed(&a, &b);
		Assert(a == 1399152289 && b == 766747565, "failed RNG test3");
	}


/*
require(lhs)

RNGkind("Marsaglia-Multicarry")
RNGkind()
.Random.seed

.Random.seed <- as.integer(c(401, 1976, 1968))
.Random.seed
floor(4*improvedLHS(4,3,5))+1
.Random.seed

.Random.seed <- as.integer(c(401, 1976, 1968))
.Random.seed
print(runif(1), 20)
.Random.seed
*/

	void improvedLHS_RTest::testStress()
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
			improvedLHS_C(&n, &k, &DUP, result);

	}

}