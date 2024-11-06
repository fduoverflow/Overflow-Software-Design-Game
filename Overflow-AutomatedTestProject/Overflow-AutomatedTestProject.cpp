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
		/**
		 * Focusing on User Input Validation class
		 *    Users input a string - coud be null -> anything
		 *    Input validation class verifies the command entered is a valid command (movement or action)
		 *       and stores an enum version for later retrieval
		 *       invalid commands are stored as specific enums and leaves to calling routines to verify prior to use - e.g. ERROR or X
		 *
		 * First set of tests will verify all  of the currently available commands are parsed & stored correctly (case & white space insensitive)
		 * 			// Common player actions - Error occurs when invalid input is entered
		 *    RULES, INV, MAP, PICKUP, INSPECT, ERROR, HEALTH, TALK
		 *
		 * Next set will focus on some edge cases
		 */
		TEST_METHOD(OverflowAllActionTest)
		{
			std::string message;
			Logger::WriteMessage("Testing actions\n");

			// define the structure and test cases to compare
			struct inputStruct {
				// Create a struct to hold both elements of the array
				struct Element {
					std::string text;
					UserInputValidation::Action move;
				};

				// Array of two elements of the inner struct
				Element elements[9] = {
					// {"Rules", UserInputValidation::Action::RULES}, -- would fail, RULES not implemented
					{"Map", UserInputValidation::Action::MAP},
					{"inv", UserInputValidation::Action::INV},
					{"pickUP", UserInputValidation::Action::PICKUP},
					{"InSpEcT", UserInputValidation::Action::INSPECT},
					{"Health", UserInputValidation::Action::HEALTH},
					{"TALK", UserInputValidation::Action::TALK},
					{"garbage", UserInputValidation::Action::ERROR},     // rework code to support errors - Action checker fails here
					{"InSpEcT ", UserInputValidation::Action::INSPECT},  // trailing white space - fails
					{" Health", UserInputValidation::Action::HEALTH}    // leading white space - fails
				};
			};

			// run through the tests, assert any issues
			UserInputValidation action;
			inputStruct myInputStruct;
			for (const auto& element : myInputStruct.elements) {
				message = "Checking " + element.text + "\n";
				Logger::WriteMessage(message.c_str());
				Assert::IsTrue(action.ActionChecker(element.text), L"Action checker returned False");
				Assert::IsTrue(action.GetPlayerAction() == element.move, L"Stored action does not match predicted action");
			}
		}

		/**
		 * Single character moves
		 *  W = 'W',	A = 'A',	S = 'S',	D = 'D',
		 * For invalid inputs
		 *  X = 'X'
		 */

		TEST_METHOD(OverflowAllMoveTest)
		{
			std::string message;
			Logger::WriteMessage("Testing moves\n");

			// define the structure and test cases to compare
			struct inputStruct {
				// Create a struct to hold both elements of the array
				struct Element {
					std::string text;
					UserInputValidation::Move move;
				};

				// Array of two elements of the inner struct
				Element elements[5] = {
					{"W", UserInputValidation::Move::W},
					{"a", UserInputValidation::Move::A},
					{"s", UserInputValidation::Move::S},
					{"d", UserInputValidation::Move::D},
					{"z", UserInputValidation::Move::X} // error case - will fail
				};
			};

			// run through the tests, assert any issues
			UserInputValidation action;
			inputStruct myInputStruct;
			for (const auto& element : myInputStruct.elements) {
				message = "Checking " + element.text + "\n";
				Logger::WriteMessage(message.c_str());
				Assert::IsTrue(action.MoveChecker(element.text), L"Move checker returned False");
				Assert::IsTrue(action.GetPlayerMove() == element.move, L"Stored move does not match predicted action");
			}
		}
		TEST_METHOD(OverflowActionEdgeCases)
		{
			Logger::WriteMessage("Action edge cases - no tests yet - to be defined\n");
		}

	};
}
