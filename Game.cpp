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

	//Rules and Backstory Output Here
	
	//Initialize Player then place them in middle of starting chunk
	Player myPlayer("Shakir");
	myPlayer.SetPlayerLocation(myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 7));
	myPlayer.SetPlayerChunkLocation(1, 1);

	//Set description of Tile at current player goal
	myPlayer.GetMap().GetChunkAt(3, 6).GetTileAt(7, 15).SetDescription("This is the entrance to the City!");

	//Initialize control variables
	bool isGameOver = false;
	string moveInput;

	while (!isGameOver)
	{
		//Get user input. Did not validate input yet.
		cout << "Player's current location: " + myPlayer.GetPlayerLocation().GetDescription();
		cout << "\nRow: " << myPlayer.GetPlayerLocation().GetRow();
		cout << "\nCol: " << myPlayer.GetPlayerLocation().GetColumn();
		cout << "\nEnter movement command: ";
		cin >> moveInput;

		//User Input Validation
		
		//TEST CASE FOR MOVECHECKER
		UserInputValidation valid;
		valid.MoveChecker(moveInput);

		//Move player
		myPlayer.MovePlayerTo(valid.GetPlayerMove());
	
		/*
		if (moveInput == "W")
		{
			cout << "North detected\n";
			myPlayer.MovePlayerNorth();
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
		*/
	}

	return 0;
}