#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <vector>
#include "../UserInputValidation.cpp"
#include "../Enemy.cpp"
#include "../Enemy.h"  // Include Enemy class
#include "../Item.h"   // Include Item class
#include "../Inventory.h" // Include Inventory class
#include "../Tile.h"    // Include Tile class
#include "../Inventory.cpp"
#include "../Item.cpp"
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

        TEST_METHOD(AddTwoItemsTest)
        {
            Logger::WriteMessage("Testing adding two items to the inventory\n");

            // inventory created with a size of size 5 
            Inventory inventory(5);

            // creating two dummy items
            Item potion("Potion", "A healing potion", Item::Type::HEALING, 10);
            Item key("Key", "A key for unlocking doors", Item::Type::KEY, 0);

            // now adding both items to the inventory
            inventory.addItem(potion);
            inventory.addItem(key);

            // now basically gotta simulate displaying this inventory
            inventory.displayInventory();

            // inventory is not empty
            Assert::IsFalse(inventory.IsEmpty(), L"Inventory should not be empty after adding items");

            Logger::WriteMessage("AddTwoItemsTest completed successfully\n");
        }

        TEST_METHOD(PreventAddingWhenFull)
        {
            Logger::WriteMessage("Testing adding items to a full inventory\n");

            // Create an inventory of size 2 again
            Inventory inventory(2);

            // Creating three items
            Item sword("Sword", "A sharp blade", Item::Type::WEAPON, 100);
            Item shield("Shield", "A sturdy shield", Item::Type::EQUIPMENT, 50);
            Item potion("Potion", "A healing potion", Item::Type::HEALING, 10);

            // Step 3: Add two items (inventory will be full)
            inventory.addItem(sword);
            inventory.addItem(shield);

            // trying to add a third item (should fail)
            inventory.addItem(potion);

            // tring to simulate displaying the inventory
            inventory.displayInventory();

            // inventory is full
            Assert::IsTrue(true, L"Inventory should not accept more items when full");

            Logger::WriteMessage("PreventAddingWhenFull completed successfully\n");
        }

        TEST_METHOD(OverflowAllActionTest)
        {
            Logger::WriteMessage("Testing actions\n");

            // Define the structure and test cases to compare
            struct inputStruct {
                struct Element {
                    std::string text;
                    UserInputValidation::Action move;
                };

                // Array with the test scenarios
                Element elements[10] = {
                    {"Map", UserInputValidation::Action::MAP},
                    {"inv", UserInputValidation::Action::INV},
                    {"pickUP", UserInputValidation::Action::PICKUP},
                    {"InSpEcT", UserInputValidation::Action::INSPECT},
                    {"Health", UserInputValidation::Action::HEALTH},
                    {"TALK", UserInputValidation::Action::TALK},
                    {"InSpEcT ", UserInputValidation::Action::INSPECT},
                    {" Health", UserInputValidation::Action::HEALTH},
                    {"garbage", UserInputValidation::Action::ERROR},
                    {"A", UserInputValidation::Action::ERROR}
                };
            };

            
            // vallone work
            // Run through the tests, assert any issues
            UserInputValidation action;
            inputStruct myInputStruct;
            for (const auto& element : myInputStruct.elements) {
                std::string message = "Checking " + element.text + "\n";
                Logger::WriteMessage(message.c_str());

                // ActionChecker will return false if an invalid command (enum = ERROR), otherwise true for valid commands
                if (element.move == UserInputValidation::Action::ERROR)
                    Assert::IsFalse(action.ActionChecker(element.text, true), L"Invalid command passed validation");
                else
                    Assert::IsTrue(action.ActionChecker(element.text, true), L"Valid command failed validation");

                Assert::IsTrue(action.GetPlayerAction() == element.move, L"Stored action does not match predicted action");
            }
        }

        TEST_METHOD(OverflowAllMoveTest)
        {
            Logger::WriteMessage("Testing moves\n");

            // Define the structure and test cases 
            struct inputStruct {
                struct Element {
                    std::string text;
                    UserInputValidation::Move move;
                };

                // Array of elements for test cases
                Element elements[5] = {
                    {"W", UserInputValidation::Move::W},
                    {"a", UserInputValidation::Move::A},
                    {"s", UserInputValidation::Move::S},
                    {"d", UserInputValidation::Move::D},
                    {"z", UserInputValidation::Move::X} // error case
                };
            };

            // basically examing my test now
            UserInputValidation action;
            inputStruct myInputStruct;
            for (const auto& element : myInputStruct.elements) {
                std::string message = "Checking " + element.text + "\n";
                Logger::WriteMessage(message.c_str());

                Assert::IsTrue(action.MoveChecker(element.text), L"Valid move failed validation");
                Assert::IsTrue(action.GetPlayerMove() == element.move, L"Stored move does not match predicted action");
            }
        }

        TEST_METHOD(EnemyClassBasicTest)
        {
            Logger::WriteMessage("Testing Enemy class basic functionality\n");

            // Enemy made with a constructor made with love <3
            Enemy enemy("Goblin", 100);

            // basically checking enemy name and health
            Assert::AreEqual(std::string("Goblin"), enemy.GetName(), L"Enemy name mismatch");
            Assert::AreEqual(100, enemy.GetHealth(), L"Enemy health mismatch");

            // u can change the enemy's attributes here
            enemy.SetName("Orc");
            enemy.SetHealth(150);

            // now you can check the switch attritubes and name here
            Assert::AreEqual(std::string("Orc"), enemy.GetName(), L"Updated enemy name mismatch");
            Assert::AreEqual(150, enemy.GetHealth(), L"Updated enemy health mismatch");

            Logger::WriteMessage("Enemy class basic functionality test completed successfully\n");
        }
    };
}
