#pragma once

#include <cstdlib>
#include "TestClass.h"
#include "defines.h"
#include "utilityLHS_R.h"

namespace lhsTest {
	class utilityLHSTest : public TestClass
	{
		void Run();
		void testLhsCheck();
		void testRank();
		void testRankColumns();
		void testLhsPrint();
		void testSumInvDistance();
	};
}
