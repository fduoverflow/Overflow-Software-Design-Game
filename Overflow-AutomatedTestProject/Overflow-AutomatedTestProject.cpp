#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <vector>
#include "../UserInputValidation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OverflowAutomatedTestProject
{
	TEST_CLASS(OverflowAutomatedTestProject)
	{
	public:
		TEST_METHOD(OverflowHelloAutoTest)
		{
			Logger::WriteMessage("Hello from Overflow_HelloAutoTest\n");
		}
	};
}
