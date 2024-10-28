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

using namespace std;


const int STARTING_AREA_NUM_ROWS = 5;
const int STARTING_AREA_NUM_COLS = 6;

int main() {
	Map worldMap("startingAreaMap.txt", STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);

	Player myPlayer("link", 100, 5, 5);
	myPlayer.SetPlayerChunkLocation(1, 1);

	// Creates the Game Manager object that will handle all game logic
	GameManager manager(&myPlayer, &worldMap);

	//Place items near player's starting tile
	worldMap.GetChunkAt(0, 0).GetTileAt(5, 4).SetItem(new Item("Apple", "This Apple will heal 10 HP when used.", Item::Type::HEALING, 10));
	worldMap.GetChunkAt(0, 0).GetTileAt(6, 5).SetItem(new Item("Key", "This key might unlock a door somewhere.", Item::Type::KEY, 0));
	worldMap.GetChunkAt(0, 0).GetTileAt(4, 5).SetItem(new Item("Ring", "This Ring can be equipped to increase your magic power.", Item::Type::EQUIPMENT, 5));
	worldMap.GetChunkAt(0, 0).GetTileAt(5, 6).SetItem(new Item("Wand", "This Wand can be used as a weapon against your enemies.", Item::Type::WEAPON, 25));

	//Set game loop variables
	bool isGameOver = false;
	string moveInput;

	//Display current chunk
	worldMap.DisplayChunkAt(myPlayer.GetPlayerChunkLocationX(), myPlayer.GetPlayerChunkLocationY());

	while (!isGameOver) {
		
		//Display item if there is one on Tile
		if (manager.GetPlayerLocationTile().GetItem() != nullptr)
		{
			cout << "\nThere is an item here: " + manager.GetPlayerLocationTile().GetItem()->GetName();
			cout << "\nType PickUp to pick up item.";
			cout << "\nType Inspect to look at item description.";
		}
		cout << "\nChunk X: " << myPlayer.GetPlayerChunkLocationX();
		cout << "\nChunk Y: " << myPlayer.GetPlayerChunkLocationY();
		cout << "\nRow: " << myPlayer.GetPlayerLocationY();
		cout << "\nCol: " << myPlayer.GetPlayerLocationX();
		cout << "\nEnter command: ";
		cin >> moveInput;

		// Clears the console screen
		system("cls");

		//Display current chunk
		worldMap.DisplayChunkAt(myPlayer.GetPlayerChunkLocationX(), myPlayer.GetPlayerChunkLocationY());

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
					if (manager.GetPlayerLocationTile().GetItem()->GetType() != Item::Type::EMPTY)
					{
						manager.GetPlayerLocationTile().PickUpItem();
						cout << "Item was picked up.\n";
					}
					break;
				case UserInputValidation::Action::INSPECT:
					if (manager.GetPlayerLocationTile().GetItem()->GetType() != Item::Type::EMPTY)
					{
						cout << "Item description: " + manager.GetPlayerLocationTile().GetItem()->GetDescription() + "\n";
					}
					break;
				case UserInputValidation::Action::MAP:
					worldMap.DisplayMap();
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