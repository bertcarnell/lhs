#include <cstdlib>
#include <cstdio>
#include <vector>
#include "TestClass.h"
#include "improvedLHS_RTest.h"
#include "maximinLHS_RTest.h"
#include "optimumLHS_RTest.h"
#include "optSeededLHS_RTest.h"

using namespace lhsTest;

int main(int argc, const char* argv[] )
{
	printf("Starting lhsTest...\n");
	std::vector<TestClass*> tests = std::vector<TestClass*>();
	tests.push_back(dynamic_cast<TestClass*>(new improvedLHS_RTest()));
	tests.push_back(dynamic_cast<TestClass*>(new maximinLHS_RTest()));
	tests.push_back(dynamic_cast<TestClass*>(new optimumLHS_RTest()));
	tests.push_back(dynamic_cast<TestClass*>(new optSeededLHS_RTest()));

	for (size_t i = 0; i < tests.size(); i++)
	{
		try{
			tests[i]->Run();
		} catch (std::exception * e){
			printf(e->what());
		}
	}
}