#ifndef TESTCLASS_H
#define	TESTCLASS_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <exception>
#include <string>
#include "simpleAssert.h"

#define START_TESTS(x) \
	printf(x); \
	std::vector<bclib::TestClass*> tests = std::vector<bclib::TestClass*>();

#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<bclib::TestClass*>(new x()))

#define EXECUTE_TESTS(x) \
	bclib::TestClass::executeTests(tests);

/* #include <cstdlib>
 * #include <vector>
 * #include <exception>
 * #include "TestClass.h"
 * #include "simpleTest1.h"
 * #include "simpleTest2.h"
 * 
 * int main(int argc, const char* argv[] )
 * {
 *  START_TESTS("Starting Simple Tests...\n")
 *  CREATE_TEST(simpleTest1);
 *  CREATE_TEST(simpleTest2);
 *  EXECUTE_TESTS
 * }
 */

namespace bclib
{
	class TestClass
	{
	public:
		virtual void Run(){};
        static void executeTests(std::vector<TestClass*> tests)
        {
            for (size_t i = 0; i < tests.size(); i++)
            {
                try
                {
                    tests[i]->Run();
                } 
                catch (std::exception & e)
                {
                    printf("\nCaught Test Exception:\n");
                    printf("\t%s\n", e.what());
                }
            }
        }
	};
}

#endif
