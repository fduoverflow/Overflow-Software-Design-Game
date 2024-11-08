#pragma once
#include <string>
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
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

	// Marks if a tile is a flag for a quest
	string questFlag;

	//Item in Tile
	Item* myItem;

	//NPC on tile
	NPC* myNPC;

	//Enemy on tile
	Enemy* myEnemy;

public:
	//Description Setter/Getters
	void DisplayTile();
	void DisplayPlayerTile();

	//Row Setter/Getters
	int GetRow();
	void SetRow(int r);

	//Column Setter/Getters
	int GetColumn();
	void SetColumn(int c);
  
	//Item Setter/Getters, passed by reference
	Item* GetItem();
	void SetItem(Item *newItem);

	//NPC Setter/Getters, passed by reference
	NPC* GetNPC();
	void SetNPC(NPC* newNPC);

	//Enemy Setter/Getters, passed by reference
	Enemy* GetEnemy();
	void SetEnemy(Enemy* newEnemy);

	// questFlag Setters/Getters
	string GetQuestFlag();
	void SetQuestFlag(string questFlag);

	//Pickup item
	Item& PickUpItem();

	//Constructors
	Tile(int r, int c, int tileID);
	Tile(int r, int c, Item* newItem, int tileID);
	Tile();
};