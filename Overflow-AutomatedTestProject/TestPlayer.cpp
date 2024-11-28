#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Item.cpp"
#include "../Quest.cpp"
#include "../Player.h"
#include "../Player.cpp"

// use this class to test if quests fully work, and map movement remeber u can only use cpp files in one class 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OverflowTestPlayerClass
{
    TEST_CLASS(TestPlayer)
    {
    public:
        TEST_METHOD(TestPlayerInitialization)
        {
            
            Player player("Hero", 100, 5, 5);

            
            Assert::AreEqual(std::string("Hero"), player.GetPlayerName(), L"Player name mismatch");
            Assert::AreEqual(100, player.GetPlayerHealth(), L"Player health mismatch");
            Assert::AreEqual(5, player.GetPlayerLocationX(), L"Player X location mismatch");
            Assert::AreEqual(5, player.GetPlayerLocationY(), L"Player Y location mismatch");
        }
        TEST_METHOD(TestPlayerMovement)
        {
            
            Player player("Hero", 100, 5, 5);

            
            player.SetPlayerLocation(10, 15);

            
            Assert::AreEqual(10, player.GetPlayerLocationX(), L"Player X location mismatch after movement");
            Assert::AreEqual(15, player.GetPlayerLocationY(), L"Player Y location mismatch after movement");
        }
        
        TEST_METHOD(TestPlayerHealthUpdate)
        {
            
            Player player("Hero", 100, 5, 5);

            
            player.SetPlayerHealth(80); // Update health to 80

            // Assert
            Assert::AreEqual(80, player.GetPlayerHealth(), L"Player health mismatch after update");
        }

		TEST_METHOD(TestQuestInitialization)
		{
			// Arrange
			Item spellbook("Spellbook", { L"📖", 1 }, "A book containing magical spells.", Item::Type::KEY, 0, 1);
			Quest quest("Retrieve the Spellbook",
				"Find the spellbook in the abandoned house.",
				"Travel to the house.", &spellbook);

			// Act & Assert
			Assert::AreEqual(std::string("Retrieve the Spellbook"), quest.GetQuestName(), L"Quest name mismatch.");
			Assert::AreEqual(std::string("Find the spellbook in the abandoned house."), quest.GetQuestDescription(), L"Quest description mismatch.");
			Assert::AreEqual(std::string("Travel to the house."), quest.GetCurrentObjective(), L"Initial objective mismatch.");
			Assert::IsNotNull(quest.GetItemGoal(), L"Item goal should not be null.");
		}

		TEST_METHOD(TestQuestProgression)
		{
			
			Item spellbook("Spellbook", { L"📖", 1 }, "A book containing magical spells.", Item::Type::KEY, 0, 1);
			Quest quest("Retrieve the Spellbook",
				"Find the spellbook in the abandoned house.",
				"Travel to the house.", &spellbook);

			// Start the quest
			quest.SetQuestStart(true);
			Assert::IsTrue(quest.GetQuestStart(), L"Quest should be marked as started.");

			// Update the objective
			quest.SetCurrentObjective("Retrieve the spellbook.");
			Assert::AreEqual(std::string("Retrieve the spellbook."), quest.GetCurrentObjective(), L"Objective update failed.");

			// Complete the quest
			quest.SetQuestComplete(true);
			Assert::IsTrue(quest.GetQuestComplete(), L"Quest should be marked as completed.");
		}

		TEST_METHOD(TestQuestReward)
		{
			// QUEST TESTING
			Item spellbook("Spellbook", { L"📖", 1 }, "A book containing magical spells.", Item::Type::KEY, 0, 1);
			Player player("Hero", 100, 5, 5);
			Quest quest("Retrieve the Spellbook",
				"Find the spellbook in the abandoned house.",
				"Travel to the house.",
				&spellbook);

			// Act: Simulate completing the quest
			quest.SetQuestStart(true);
			quest.SetQuestComplete(true);

			// Apply the reward (e.g., increase player health)
			if (quest.GetQuestComplete())
			{
				player.SetPlayerHealth(player.GetPlayerHealth() + 10); // Reward: heal 10 HP
			}

			// Assert
			Assert::AreEqual(110, player.GetPlayerHealth(), L"Player's health reward was not applied correctly.");
		}

    };
}
