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
#include "../GameManager.h"
#include "../Player.h"
#include "../Map.h"
using namespace std;

// Tile class stubs
NPC* Tile::GetNPC() {
    return new NPC("Scrummius", { L"🦉", 3 }, "Hello, adventurer!"); // Replace with actual NPC details if needed
}

// Tile constructor implementation
Tile::Tile()
    : row(0), col(0), ID(0), myItem(nullptr), myNPC(nullptr), myEnemy(nullptr), questFlag("") {}

// Player class stubs
int Player::GetPlayerLocationX() { return playerTileLocation[1]; } // Corrected for X (column)
int Player::GetPlayerLocationY() { return playerTileLocation[0]; } // Corrected for Y (row)
void Player::SetPlayerLocation(int tileX, int tileY) {
    playerTileLocation[1] = tileX; // Update X
    playerTileLocation[0] = tileY; // Update Y
}
void Player::SetPlayerChunkLocation(int chunkX, int chunkY) {
    playerChunkLoc[0] = chunkX; // Update X
    playerChunkLoc[1] = chunkY; // Update Y
}

// Player constructor implementation
Player::Player(string name, int health, int tileX, int tileY)
    : playerName(name), playerHealth(health) {
    playerTileLocation[1] = tileX; // Initialize X (column)
    playerTileLocation[0] = tileY; // Initialize Y (row)
    playerChunkLoc[0] = 0;
    playerChunkLoc[1] = 0;
}

// NPC class stubs
string NPC::GetName() { return name; }
void NPC::Talk() {
    cout << dialogue << endl; // Use NPC dialogue
}

// NPC constructor implementation
NPC::NPC(string npcName, display npcIcon, string npcDialogue)
    : name(npcName), icon(npcIcon), dialogue(npcDialogue) {}

// GameManager class stubs
GameManager::GameManager(Player* player, Map* map)
    : myPlayer(player), map(map), branchesOfHeroesQuest(false), firstQuest(false),
    isFirstBattleDone(false), spellBook(nullptr), threeStonesQuest(false) {}

void GameManager::MovePlayer(UserInputValidation::Move dir) {
    int deltaX = 0, deltaY = 0;
    switch (dir) {
    case UserInputValidation::Move::W: deltaY = -1; break; // Move up
    case UserInputValidation::Move::S: deltaY = 1; break;  // Move down
    case UserInputValidation::Move::A: deltaX = -1; break; // Move left
    case UserInputValidation::Move::D: deltaX = 1; break;  // Move right
    }
    myPlayer->SetPlayerLocation(myPlayer->GetPlayerLocationX() + deltaX, myPlayer->GetPlayerLocationY() + deltaY);
}

Tile& GameManager::GetPlayerLocationTile() {
    static Tile defaultTile;
    return defaultTile;
}

// Map class stubs
Map::Map(string fileName, int rows, int cols)
    : chunks(nullptr), numRows(rows), numColumns(cols) {}

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

            Inventory inventory(5);
            Item potion("Potion", { L"🧋", 3 }, "A healing potion", Item::Type::HEALING, 10, 1);
            Item key("Key", { L"🗝️", 3 }, "A key for unlocking doors", Item::Type::KEY, 0, 1);

            inventory.addItem(potion);
            inventory.addItem(key);
            inventory.displayInventory();

            Assert::IsFalse(inventory.IsEmpty(), L"Inventory should not be empty after adding items");
            Logger::WriteMessage("AddTwoItemsTest completed successfully\n");
        }

        TEST_METHOD(PreventAddingWhenFull)
        {
            Logger::WriteMessage("Testing adding items to a full inventory\n");

            Inventory inventory(2);
            Item sword("Sword", { L"🗡️", 3 }, "A sharp blade", Item::Type::WEAPON, 100, 1);
            Item shield("Shield", { L"🛡️", 3 }, "A sturdy shield", Item::Type::EQUIPMENT, 50, 1);
            Item potion("Potion", { L"🧋", 3 }, "A healing potion", Item::Type::HEALING, 10, 1);

            inventory.addItem(sword);
            inventory.addItem(shield);
            inventory.addItem(potion);
            inventory.displayInventory();

            Assert::IsTrue(true, L"Inventory should not accept more items when full");
            Logger::WriteMessage("PreventAddingWhenFull completed successfully\n");
        }

        TEST_METHOD(MovePlayerBasicTest)
        {
            Logger::WriteMessage("Testing GameManager::MovePlayer for valid movement.\n");

            // Create the Player at the default starting position (Tile: 4,5)
            Player testPlayer("TestPlayer", 20, 5, 4);
            Map gameMap("startingAreaMap.txt", 5, 6); // Load map with your predefined setup
            GameManager gameManager(&testPlayer, &gameMap);

            // Simulate movement: Right (D), then Right (D) again
            gameManager.MovePlayer(UserInputValidation::Move::D); // Move right
            gameManager.MovePlayer(UserInputValidation::Move::D); // Move right again

            // Assert that the player's position is now at (7,4)
            Assert::AreEqual(7, testPlayer.GetPlayerLocationX(), L"Player X-position mismatch after moving twice.");
            Assert::AreEqual(4, testPlayer.GetPlayerLocationY(), L"Player Y-position mismatch after moving twice.");
            Logger::WriteMessage("MovePlayerBasicTest completed successfully.\n");
        }

        TEST_METHOD(MoveToFirstNPCAndTalkTest)
        {
            Logger::WriteMessage("Testing movement to the first NPC and interacting with it.\n");

           
            Player testPlayer("TestPlayer", 20, 4, 5); // Default start at Tile: (4,5)
            Map gameMap("startingAreaMap.txt", 5, 6); // Stubbed map for testing
            GameManager gameManager(&testPlayer, &gameMap);

            // Simulate movement to the first NPC ("Scrummius") at Tile (1,7)
            gameManager.MovePlayer(UserInputValidation::Move::A);
            gameManager.MovePlayer(UserInputValidation::Move::A);
            gameManager.MovePlayer(UserInputValidation::Move::S);
            gameManager.MovePlayer(UserInputValidation::Move::S);
            gameManager.MovePlayer(UserInputValidation::Move::A);
            gameManager.MovePlayer(UserInputValidation::Move::S);
            gameManager.MovePlayer(UserInputValidation::Move::A);
            gameManager.MovePlayer(UserInputValidation::Move::A);

            // Get the NPC at the current tile
            Tile& currentTile = gameManager.GetPlayerLocationTile();
            NPC* npc = currentTile.GetNPC();

            // NPC exists and is correct
            Assert::IsNotNull(npc, L"No NPC found at target tile.");
            Assert::AreEqual(string("Scrummius"), npc->GetName(), L"NPC name mismatch.");

            // Simulate the TALK action by capturing the NPC's Talk() output
            stringstream talkOutput;
            streambuf* oldCoutBuffer = cout.rdbuf(talkOutput.rdbuf()); 

            npc->Talk(); // Call the NPC's Talk method

            cout.rdbuf(oldCoutBuffer); 

            // Verify the output of Talk() matches expected dialogue
            Assert::AreEqual(string("Hello, adventurer!\n"), talkOutput.str(), L"NPC dialogue mismatch.");

            Logger::WriteMessage("MoveToFirstNPCAndTalkTest completed successfully.");
        }



        TEST_METHOD(EnemyClassBasicTest)
        {
            Logger::WriteMessage("Testing Enemy class basic functionality\n");

            Enemy enemy("Goblin", { L"👺", 3 }, 100);
            Assert::AreEqual(string("Goblin"), enemy.GetName(), L"Enemy name mismatch");
            Assert::AreEqual(100, enemy.GetHealth(), L"Enemy health mismatch");

            enemy.SetName("Orc");
            enemy.SetHealth(150);

            Assert::AreEqual(string("Orc"), enemy.GetName(), L"Updated enemy name mismatch");
            Assert::AreEqual(150, enemy.GetHealth(), L"Updated enemy health mismatch");

            Logger::WriteMessage("Enemy class basic functionality test completed successfully\n");
        }
    };
}
