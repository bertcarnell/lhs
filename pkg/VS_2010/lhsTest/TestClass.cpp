#include "TestClass.h"

namespace lhsTest
{
	void TestClass::Assert(bool test, std::string msg)
	{
		if (!test)
			throw new std::exception(msg.c_str());
	}
}
