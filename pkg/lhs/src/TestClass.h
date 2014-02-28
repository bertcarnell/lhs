/**
 * @file TestClass.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TESTCLASS_H
#define	TESTCLASS_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <exception>
#include <string>
#include "simpleAssert.h"

/**
 * Macro to start the tests  in the main.cpp of the test project
 */
#define START_TESTS(x) \
	printf(x); \
	std::vector<bclib::TestClass*> tests = std::vector<bclib::TestClass*>();

/**
 * Macro to create an individual test and instantiate it's class if it 
 * inherits from TestClass.h
 */
#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<bclib::TestClass*>(new x()))

/**
 * Macro to run all the defined tests
 */
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
    /**
     * A class used to derive unit test from
     * 
     * Used in conjunction with the macros as follows
     * <code>
     * #include <cstdlib>
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
     * </code>
     */
	class TestClass
	{
	public:
        /**
         * run a set of unit tests in a TestClass
         */
		virtual void Run(){};
        /**
         * method used in the main.cpp to run unit test classes
         * @param tests
         */
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
