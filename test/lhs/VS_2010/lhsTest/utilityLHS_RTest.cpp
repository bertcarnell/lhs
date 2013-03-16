#include "utilityLHS_RTest.h"

namespace lhsTest{
	void utilityLHSTest::Run()
	{
		printf("\timprovedLHS_RTest...");
		testLhsCheck();
		testRank();
		testRankColumns();
		testLhsPrint();
		testSumInvDistance();
		printf("passed\n");
	}

	void utilityLHSTest::testLhsCheck()
	{
		int a[10] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
		Assert(utilityLHS::lhsCheck(5, 2, a, false) == 1, "Failed 1");

		int b[10] = {0, 2, 3, 4, 5, 5, 4, 3, 2, 1};
		Assert(utilityLHS::lhsCheck(5, 2, b, false) == 0, "Failed 2");

		int d[10] = {1, 2, 3, 6, 5, 5, 4, 3, 2, 1};
		Assert(utilityLHS::lhsCheck(5, 2, d, false) == 0, "Failed 3");
	}

	void utilityLHSTest::testRank()
	{
		std::vector<double> a = std::vector<double>(5);
		double b[5] = {.1, .4, .2, .3, .5};
		for (int i = 0; i < 5; i++)
			a[i] = b[i];

		std::vector<int> d = std::vector<int>(5);
		utilityLHS::rank(a, d);

		int expected[5] = {4, 1, 3, 2, 0};
		for (int i = 0; i < 5; i++)
			Assert(d[i] == expected[i], "failed 1");

		std::vector<double> e = std::vector<double>(5);
		double f[5] = {.1, .4, .4, .3, .5};
		for (int i = 0; i < 5; i++)
			e[i] = f[i];

		utilityLHS::rank(e, d);

		int expected2[5] = {4, 1, 1, 3, 0};
		for (int i = 0; i < 5; i++)
			Assert(d[i] == expected2[i], "failed 1");
	}

	void utilityLHSTest::testRankColumns()
	{
		std::vector<double> a = std::vector<double>(10);
		double b[10] = {.1, .4, .2, .3, .5, .11, .12, .15, .14, .13};
		for (int i = 0; i < 10; i++)
			a[i] = b[i];

		std::vector<int> d = std::vector<int>(10);
		utilityLHS::rankColumns(a, d, 5);

		int expected[10] = {0, 2, 3, 1, 4, 0, 1, 4, 3, 2};
		for (int i = 0; i < 10; i++)
			Assert(d[i] == expected[i], "failed 1");

	}

	void utilityLHSTest::testLhsPrint()
	{
	}

	void utilityLHSTest::testSumInvDistance()
	{
	}
}
