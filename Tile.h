#pragma once
#include <string>
using namespace std;

const string TILE_DISPLAY = "  ";

/*
Tile class will hold information for 1 specific tile in the Map
Tile can also be "out of bounds" as a description
Ex: 3x3 grid if the "playable area" is only the bottom left 2 tiles,
every other tile would be "out of bounds" and not accessible by the player
*/
class Tile
{
	private:
		string description;
		int row;
		int col;

	public:
		// Description Setter/Getters
		string GetDescription();
		void SetDescription(string desc);
		void DisplayTile();

		Tile();
		Tile(string desc);
};