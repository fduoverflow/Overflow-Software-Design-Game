#include <iostream>
#include "ConsoleColors.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	cout << "Overflow Game!" << endl;

	//Initialize Player then place them in middle of starting chunk
	Player myPlayer("Shakir");
	myPlayer.SetPlayerLocation(myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 7));
	myPlayer.SetPlayerChunkLocation(1, 1);

	/*
	cout << myPlayer.GetPlayerLocation().GetDescription();
	myPlayer.GetPlayerLocation().SetDescription("This is the player starting position");
	cout << "\n" + myPlayer.GetPlayerLocation().GetDescription();
	cout << "\n" + myPlayer.GetPlayerLocation().GetNorthTile().GetSouthTile().GetDescription();

	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerEast();
	myPlayer.MovePlayerSouth();
	myPlayer.MovePlayerWest();

	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerNorth();
	myPlayer.MovePlayerSouth();
	*/


	/*
	* The following is test code and does not check for input validation.
	*/
	/*
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
	startingChunk.GetTileAt(3, 10).GetNorthTile().SetDescription("North of the middle tile");

	cout << startingChunk.GetTileAt(0, 0).GetDescription();
	cout << "\n" + startingChunk.GetTileAt(3, 10).GetDescription() + "\n";
	cout << startingChunk.GetTileAt(3, 10).GetNorthTile().GetDescription() + "\n";

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
	*/

	return 0;
}