#pragma once
#include <string>
#include "Item.h"
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
		int ID;
		int row;
		int col;

		//Item in Tile
		Item myItem;

		//Adjacent Tiles
		Tile* northTile;
		Tile* southTile;
		Tile* eastTile;
		Tile* westTile;

	public:
		//Description Setter/Getters
		void DisplayTile();

		//Row Setter/Getters
		int GetRow();
		void SetRow(int r);

		//Column Setter/Getters
		int GetColumn();
		void SetColumn(int c);

		//Item Setter/Getters, passed by value
		Item GetItem();
		void SetItem(Item newItem);

		//Pickup item
		Item PickUpItem();

		//Adacent Tile Setter/Getters
		Tile& GetNorthTile();
		Tile& GetSouthTile();
		Tile& GetEastTile();
		Tile& GetWestTile();
		void SetNorthTile(Tile &targetTile);
		void SetSouthTile(Tile &targetTile);
		void SetEastTile(Tile &targetTile);
		void SetWestTile(Tile &targetTile);

		//Constructors
		Tile(string desc, int r, int c);
		Tile(string desc, int r, int c, Item newItem);
		Tile();
};