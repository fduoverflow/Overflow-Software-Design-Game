#include <iostream>
#include "ConsoleColors.h"
#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"

using namespace std;


const int STARTING_AREA_NUM_ROWS = 2;
const int STARTING_AREA_NUM_COLS = 2;

//int main()
//{
//	// Constant variable for row/col map size
//	// Change after design of map has been created
//	Chunk row1[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID) };
//	Chunk row2[STARTING_AREA_NUM_COLS] = { Chunk(VALID),	 Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };
//	Chunk row3[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };
//	Chunk row4[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(VALID),   Chunk(VALID) };
//	Chunk row5[STARTING_AREA_NUM_COLS] = { Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID) };
//
//	Chunk *startingAreaMap[STARTING_AREA_NUM_ROWS] = {row1, row2, row3, row4, row5};
//	Map worldMap(startingAreaMap, STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);
//
//	cout << "Overflow Game!" << endl;
//
//	// Ryan 
//	// creating an instance of the UserInterface class
//	UserInterface ui;
//
//	// Display the rules and backstory
//	string rules = ui.DisplayRules();        // Call method to display and get rules
//	string introMessage = ui.DisplayIntroMessage(); // Call method to display and get backstory
//
//	// Continue with the rest of the game setup
//
//
//	//Initialize Player then place them in middle of starting chunk
	//Player myPlayer("Shakir", worldMap);
	//myPlayer.SetPlayerLocation(myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 7));
	//myPlayer.SetPlayerChunkLocation(1, 1);

	////Set description of Tile at current player goal
	//myPlayer.GetMap().GetChunkAt(3, 6).GetTileAt(7, 15).SetDescription("This is the entrance to the City!");

	////Initialize control variables
	//bool isGameOver = false;
	//string moveInput;
//
//	while (!isGameOver)
//	{
//		//Get user input. Did not validate input yet.
		//cout << "Player's current location: " + myPlayer.GetPlayerLocation().GetDescription();
		//cout << "\nRow: " << myPlayer.GetPlayerLocation().GetRow();
		//cout << "\nCol: " << myPlayer.GetPlayerLocation().GetColumn();
		//cout << "\nEnter command: ";
		//cin >> moveInput;
		//// Clears the console screen
		//system("cls");

		////User Input Validation
		//UserInputValidation valid;
		//// TODO - Add 'map' commend to input validation. Refactor how we check for this command.
		//if (moveInput == "map") {
		//	worldMap.DisplayMap();
		//	continue;
		//}
		//valid.MoveChecker(moveInput);

		////Move player
		//myPlayer.MovePlayerTo(valid.GetPlayerMove());
//
//		/*
//		Piece to display player map
//		Input Validation will be using the enum Action class under UserInputValidation (Xavier can do later)
//
//		Tiffany work -
//		Display the map when the user enters the string "MAP"
//		
//		Have some way to see the player location on the displayed map
//		 */
//		worldMap.Display(myPlayer.GetPlayerChunkLocationX(), myPlayer.GetPlayerChunkLocationY(), myPlayer.GetPlayerLocation().GetColumn(), myPlayer.GetPlayerLocation().GetRow());
//	}
//
//	return 0;
//}

int main(){
	Map worldMap("startingAreaMap.txt", STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);

	Player myPlayer("link", 100, 5, 5);
	myPlayer.SetPlayerChunkLocation(0, 0);

	// Creates the Game Manager object that will handle all game logic
	GameManager manager(&myPlayer, &worldMap);

	bool isGameOver = false;
	string moveInput;

	while (!isGameOver) {
		// Clears the console screen
		system("cls");
		worldMap.DisplayChunkAt(myPlayer.GetPlayerChunkLocationX(), myPlayer.GetPlayerChunkLocationY());
		cout << "\nChunk X: " << myPlayer.GetPlayerChunkLocationX();
		cout << "\nChunk Y: " << myPlayer.GetPlayerChunkLocationY();
		cout << "\nRow: " << myPlayer.GetPlayerLocationY();
		cout << "\nCol: " << myPlayer.GetPlayerLocationX();
		cout << "\nEnter command: ";
		cin >> moveInput;

		//User Input Validation
		UserInputValidation valid;
		// TODO - Add 'map' commend to input validation. Refactor how we check for this command.
		if (moveInput == "map") {
			worldMap.DisplayMap();
			continue;
		}
		valid.MoveChecker(moveInput);

		//Move player
		manager.MovePlayer(valid.GetPlayerMove());

	}
}