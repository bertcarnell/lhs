#pragma once

#include <cstdlib>
#include "TestClass.h"
#include "defines.h"
#include "simpleMatrix.h"

namespace lhsTest {
	class simpleMatrixTest : public TestClass
	{
		void Run();
		void testConstructor();
		void testAssignment();
		void testElementAssignment();
		void testElementExtraction();
		void testTranspose();

		void testUnsafeConstructor();
		void testUnsafeAssignment();
		void testUnsafeElementAssignment();
		void testUnsafeElementExtraction();
	};
}
