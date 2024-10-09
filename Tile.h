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
		//Main Tile variables
		string description;
		int row;
		int col;

		//Adjacent tiles
		Tile* northTile;
		Tile* southTile;
		Tile* eastTile;
		Tile* westTile;

	public:
		//Description Setter/Getters
		string GetDescription();
		void SetDescription(string desc);
		void DisplayTile();

		//Row Setter/Getters
		int GetRow();
		void SetRow(int r);

		//Column Setter/Getters
		int GetColumn();
		void SetColumn(int c);

		//Adacent Tile Setter/Getters
		Tile GetNorthTile();
		Tile GetSouthTile();
		Tile GetEastTile();
		Tile GetWestTile();
		void SetNorthTile(Tile &targetTile);
		void SetSouthTile(Tile &targetTile);
		void SetEastTile(Tile &targetTile);
		void SetWestTile(Tile &targetTile);

		//Constructors
		Tile(string desc, int r, int c);
		Tile();
};