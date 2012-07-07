#pragma once

#include <cstdlib>
#include "TestClass.h"
#include "defines.h"

namespace lhsTest {
	class optimumLHS_RTest : public TestClass
	{
		void Run();
		void testOptimumLHS_R();
		void testStress();
	};
}