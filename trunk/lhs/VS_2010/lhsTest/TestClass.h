#pragma once

#include <cstdlib>
#include <vector>
#include <exception>
#include <cstring>

namespace lhsTest
{
	class TestClass
	{
	public:
		virtual void Run(){};
		void Assert(bool test, std::string msg);
	};
}
