#include <iostream>
#include "Map.h"
#include "Player.h"
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

	while (!isGameOver)
	{
		cout << "\nEnter movement command: ";
		cin >> moveInput;

		if (moveInput == "W")
		{
			cout << "North detected\n";
			cout << testTile.GetDescription() + "\n";
			cout << testTile.GetNorthTile().GetDescription();		//Example of how a tile can access its adjacent tiles
		}
		else if (moveInput == "S")
			cout << "South detected";
		else if (moveInput == "D")
			cout << "East detected";
		else if (moveInput == "A")
			cout << "West detected";
	}

	return 0;
}