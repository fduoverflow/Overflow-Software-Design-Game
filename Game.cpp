#include <iostream>
#include "ConsoleColors.h"
#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"
#include "Item.h"
#include "Inventory.h"

using namespace std;


const int STARTING_AREA_NUM_ROWS = 5;
const int STARTING_AREA_NUM_COLS = 6;

int main() {
	Map worldMap("startingAreaMap.txt", STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);

	Player myPlayer("link", 100, 15, 15);
	myPlayer.SetPlayerChunkLocation(1, 1);
	Inventory inventory(25);

	// Creates the Game Manager object that will handle all game logic
	GameManager manager(&myPlayer, &worldMap);

	//Place items near player's starting tile
	//worldMap.GetChunkAt(0, 0).GetTileAt(5, 4).SetItem(new Item("Apple", "This Apple will heal 10 HP when used.", Item::Type::HEALING, 10));
	worldMap.GetChunkAt(0, 0).GetTileAt(6, 5).SetItem(new Item("Key", "This key might unlock a door somewhere.", Item::Type::KEY, 0));
	worldMap.GetChunkAt(0, 0).GetTileAt(4, 5).SetItem(new Item("Ring", "This Ring can be equipped to increase your magic power.", Item::Type::EQUIPMENT, 5));
	worldMap.GetChunkAt(0, 0).GetTileAt(5, 6).SetItem(new Item("Wand", "This Wand can be used as a weapon against your enemies.", Item::Type::WEAPON, 25));

	// Test code to Initialize First Quest until Scrummius is Implemmented
	manager.InitilizeTutorialQuest();
	//Set game loop variables
	bool isGameOver = false;
	string moveInput;

	while (!isGameOver) {

		//Display current chunk
		manager.Display();
		
		//Display item if there is one on Tile
		if (manager.GetPlayerLocationTile().GetItem() != nullptr)
		{
			cout << "\nThere is an item here: " + manager.GetPlayerLocationTile().GetItem()->GetName();
			cout << "\nType PickUp to pick up item.";
			cout << "\nType Inspect to look at item description.";
		}
		if (manager.GetPlayerLocationTile().GetQuestFlag() == "First Quest")
		{
		}

		cout << "\nChunk X: " << myPlayer.GetPlayerChunkLocationX();
		cout << "\nChunk Y: " << myPlayer.GetPlayerChunkLocationY();
		cout << "\nRow: " << myPlayer.GetPlayerLocationY();
		cout << "\nCol: " << myPlayer.GetPlayerLocationX();
		cout << "\nEnter command: ";
		cin >> moveInput;

		// Clears the console screen
		system("cls");

		//User Input Validation
		UserInputValidation valid;

		// Checking if input is a movement or action
		bool isAction = valid.ActionChecker(moveInput);
		bool isMove = valid.MoveChecker(moveInput);

		//Process Player Move and Player Action separately
		if (isAction && !isMove)
		{
			switch (valid.GetPlayerAction())
			{
				case UserInputValidation::Action::PICKUP:
					if (manager.GetPlayerLocationTile().GetItem() != nullptr)		//Check if item is on Tile
					{
						if (manager.GetPlayerLocationTile().GetItem()->GetName() == "Scrummius' Spell Book") // KEY item for First Quest-- flag trigger for completion of first quest
						{
							// Marking First Quest as Complete
							manager.TutorialQuestComplete();

							// Spawn in Dust Golem on tiles that correspond to the door tiles (7,7) and (7,8) -- once quest is complete
							cout << "You hear a gust of wind coming from the doorway...\n";
						}
						inventory.addItem(manager.GetPlayerLocationTile().PickUpItem()); //Adds the picked up item to the invetory
						cout << "Item was picked up.\n";
					}
					else
					{
						cout << "No item to pick up.\n";
					}
					break;
				case UserInputValidation::Action::INSPECT:
					if (manager.GetPlayerLocationTile().GetItem() != nullptr)		//Check if item is on Tile
					{
						cout << "Item description: " + manager.GetPlayerLocationTile().GetItem()->GetDescription() + "\n";
					}
					else
					{
						cout << "No item to inspect.\n";
					}
					break;
				case UserInputValidation::Action::MAP:
					worldMap.DisplayMap();
					break;
				case UserInputValidation::Action::HEALTH:
					cout << "You are at " << myPlayer.GetPlayerHealth() << " health.";
					break;
				case UserInputValidation::Action::INV:
					inventory.displayInventory();
					break;
			}
		}
		else if (!isAction && isMove)
		{
			//Move player
			manager.MovePlayer(valid.GetPlayerMove());
		}
		else if (!isAction && !isMove)							//Moved action error messages here because they were printing when the other action was used. Ex: "Invalid action" printed when inputing WASD.
		{
			cout << "Invalid Input! Please enter WASD or a valid action!\n";
		}
	}
}