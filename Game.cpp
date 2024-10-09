#include <iostream>
#include "ConsoleColors.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"

using namespace std;

int main() {
	cout << "Overflow Game!" << endl;

	/*
	* The following is test code for user movement and does not check for input validation.
	*/
	bool isGameOver = false;
	string moveInput;
	Tile testTile("This is the test tile", 0, 0);		//This is an example of a starting tile declaration
	Tile upTile("This is the north Tile", 0, 1);		//This is a new tile that will sit above the initial tile
	testTile.SetNorthTile(upTile);						//Connect the initial tile to the tile above it
	upTile.SetSouthTile(testTile);						//Connect the up tile to the initial tile


	//Test code for chunks
	Chunk startingChunk(VALID);

	startingChunk.GetTileAt(0, 0).SetDescription("This is a Tile");
	startingChunk.GetTileAt(3, 10).SetDescription("Wow a middle Tile");

	cout << startingChunk.GetTileAt(0, 0).GetDescription();
	cout << "\n" + startingChunk.GetTileAt(3, 10).GetDescription() + "\n";

	//Player example code
	Player myPlayer("Shakir", testTile);

	while (!isGameOver)
	{
		cout << "Player's current location: " + myPlayer.GetPlayerLocation().GetDescription();
		cout << "\nEnter movement command: ";
		cin >> moveInput;

		if (moveInput == "W")
		{
			cout << "North detected\n";
			cout << testTile.GetDescription() + "\n";
			cout << testTile.GetNorthTile().GetDescription() + "\n";		//Example of how a tile can access its adjacent tiles

			myPlayer.MovePlayerNorth();										//Example of changing player location
		}
		else if (moveInput == "S")
		{
			cout << "South detected\n";
			myPlayer.MovePlayerSouth();
		}
		else if (moveInput == "D")
		{
			cout << "East detected\n";
			myPlayer.MovePlayerEast();
		}
		else if (moveInput == "A")
		{
			cout << "West detected\n";
			myPlayer.MovePlayerWest();
		}
	}

	return 0;
}