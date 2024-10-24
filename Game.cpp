#include <iostream>
#include "ConsoleColors.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"
//#include "Item.h"

using namespace std;


const int STARTING_AREA_NUM_ROWS = 5;
const int STARTING_AREA_NUM_COLS = 7;

int main()
{
	// Constant variable for row/col map size
	// Change after design of map has been created
	Chunk row1[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID) };
	Chunk row2[STARTING_AREA_NUM_COLS] = { Chunk(VALID),	 Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };
	Chunk row3[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };
	Chunk row4[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(VALID),   Chunk(VALID) };
	Chunk row5[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };

	Chunk *startingAreaMap[STARTING_AREA_NUM_ROWS] = {row1, row2, row3, row4, row5};
	Map worldMap(startingAreaMap, STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);

	cout << "Overflow Game!" << endl;

	// Ryan 
	// creating an instance of the UserInterface class
	UserInterface ui;

	// Display the rules and backstory
	string rules = ui.DisplayRules();        // Call method to display and get rules
	string introMessage = ui.DisplayIntroMessage(); // Call method to display and get backstory

	// Continue with the rest of the game setup


	//Initialize Player then place them in middle of starting chunk
	Player myPlayer("Shakir", worldMap);
	myPlayer.SetPlayerLocation(myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 7));
	myPlayer.SetPlayerChunkLocation(1, 1);

	//Set description of Tile at current player goal
	myPlayer.GetMap().GetChunkAt(3, 6).GetTileAt(7, 15).SetDescription("This is the entrance to the City!");

	//Set items on starting chunk
	myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(6, 7).SetItem(Item("Apple", "This Apple will heal 10 HP when used.", Item::Type::HEALING, 10));
	myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 8).SetItem(Item("Key", "This key might unlock a door somewhere.", Item::Type::KEY, 0));
	myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 6).SetItem(Item("Ring", "This Ring can be equipped to increase your magic power.", Item::Type::EQUIPMENT, 5));
	myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(8, 7).SetItem(Item("Wand", "This Wand can be used as a weapon against your enemies.", Item::Type::WEAPON, 25));

	//Initialize control variables
	bool isGameOver = false;
	string moveInput;

	while (!isGameOver)
	{
		bool validAction = false; //Resets the validAction bool to default false
		
		//Display Tile information
		cout << "Player's current location: " + myPlayer.GetPlayerLocation().GetDescription();
		//Display item if there is one on Tile
		if (myPlayer.GetPlayerLocation().GetItem().GetType() != Item::Type::EMPTY)
		{
			cout << "\nThere is an item here: " + myPlayer.GetPlayerLocation().GetItem().GetName();
			cout << "\nType PickUp to pick up item.";
			cout << "\nType Inspect to look at item description.";
		}
		cout << "\nRow: " << myPlayer.GetPlayerLocation().GetRow();
		cout << "\nCol: " << myPlayer.GetPlayerLocation().GetColumn();

		//Get user input. Did not validate input yet.
		cout << "\nEnter command: ";
		cin >> moveInput;
		// Clears the console screen
		system("cls");

		// Displays the user moving around the map
		worldMap.Display(myPlayer.GetPlayerChunkLocationX(), myPlayer.GetPlayerChunkLocationY(), myPlayer.GetPlayerLocation().GetColumn(), myPlayer.GetPlayerLocation().GetRow());

		//Test code for item pick up and inspect commands. To be removed when implementing user validation for pick up command.
		if (moveInput == "PickUp")
		{
			if (myPlayer.GetPlayerLocation().GetItem().GetType() != Item::Type::EMPTY)
			{
				myPlayer.GetPlayerLocation().PickUpItem();
				cout << "Item was picked up.\n";
			}
		}
		else if(moveInput == "Inspect")
		{
			if (myPlayer.GetPlayerLocation().GetItem().GetType() != Item::Type::EMPTY)
			{
				cout << "Item description: " + myPlayer.GetPlayerLocation().GetItem().GetDescription() + "\n";
			}
		}

		//User Input Validation Object
		UserInputValidation valid;
		// TODO - Add 'map' commend to input validation. Refactor how we check for this command.

		/*
		if (moveInput == "map") {
			worldMap.DisplayMap();
			continue;
		} */

		// Checking if input is a movement or action
		bool isAction = valid.ActionChecker(moveInput);
		bool isMove = valid.MoveChecker(moveInput);

		//Process Player Move and Player Action separately
		if (isAction && !isMove)
		{
			valid.ProcessAction(moveInput, worldMap);
		}
		else if (!isAction && isMove)
		{
			// Player movement
			myPlayer.MovePlayerTo(valid.GetPlayerMove());
		}

		/*
		Piece to display player map
		Input Validation will be using the enum Action class under UserInputValidation (Xavier can do later)

		Tiffany work -
		Display the map when the user enters the string "MAP"
		
		Have some way to see the player location on the displayed map
		 */
		
	}

	return 0;
}