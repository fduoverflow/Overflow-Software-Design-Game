#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include "../Player.h"
#include "../NPC.h"
#include "../NPC.cpp"

// use this class to test npc in future

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OverflowTestGameManager
{
	TEST_CLASS(TestGameManager)
	{
	public:
		TEST_METHOD(TestPlayerInteractsWithNPC)
		{
			// basically Creating a player and an NPC
			Player player("Hero", 100, 5, 5); // Player starts at (5, 5)
			NPC npc("Scrummius", { L"??", 1 }, "Hello there, adventurer!");

			// now i can place whateber npc at a tile
			int npcX = 6;
			int npcY = 5;

			// player moving to the NPC's location
			while (player.GetPlayerLocationX() != npcX || player.GetPlayerLocationY() != npcY)
			{
				if (player.GetPlayerLocationX() < npcX)
				{
					player.SetPlayerLocation(player.GetPlayerLocationX() + 1, player.GetPlayerLocationY());
				}
				else if (player.GetPlayerLocationY() < npcY)
				{
					player.SetPlayerLocation(player.GetPlayerLocationX(), player.GetPlayerLocationY() + 1);
				}
			}

			// make sure interaction and dialogue is happenng
			if (player.GetPlayerLocationX() == npcX && player.GetPlayerLocationY() == npcY)
			{
				std::string dialogue = npc.GetDialogue();
				Assert::AreEqual(std::string("Hello there, adventurer!"), dialogue, L"NPC dialogue does not match expected.");
			}
			else
			{
				Assert::Fail(L"Player did not reach NPC's location.");
			}
		}
	};
}
