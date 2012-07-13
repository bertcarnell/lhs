#include <cstdlib>
#include <cstdio>
#include <vector>
#include "TestClass.h"
#include "improvedLHS_RTest.h"
#include "maximinLHS_RTest.h"
#include "optimumLHS_RTest.h"
#include "optSeededLHS_RTest.h"
#include "simpleMatrixTest.h"
#include "utilityLHS_RTest.h"

#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<TestClass*>(new x()))

using namespace lhsTest;

int main(int argc, const char* argv[] )
{
	printf("Starting lhsTest...\n");
	std::vector<TestClass*> tests = std::vector<TestClass*>();
	CREATE_TEST(simpleMatrixTest);
	CREATE_TEST(improvedLHS_RTest);
	CREATE_TEST(maximinLHS_RTest);
	CREATE_TEST(optimumLHS_RTest);
	CREATE_TEST(optSeededLHS_RTest);
	CREATE_TEST(utilityLHSTest);

	for (size_t i = 0; i < tests.size(); i++)
	{
		try{
			tests[i]->Run();
		} catch (std::exception * e){
			printf(e->what());
		}
	}
}