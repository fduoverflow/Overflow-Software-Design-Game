#pragma once
#include <string>
#include "ConsoleColors.h"
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
using namespace std;

const string TILE_DISPLAY = "  ";

//enum BLOCK_TYPE { GRASS, WATER, TREE, FLOOR, BUSH };

struct Block {
	string name;
	string description;
	Color color;
	bool collides;
};

const int NUM_BLOCK_TYPES = 23;


const Block BLOCK_TYPES[NUM_BLOCK_TYPES] = {
	{"Grass", "just a silly block of grass", DARK_GREEN, false},
	{"Water", "it's cold to the touch", LIGHT_BLUE, true},
	{"Bridge", "", BROWN, false},
	{"Dirt", "what a nice pattern!", TAN, false},
	{"Bush", "there's pointy thorns in this bush. you probably shouldn't walk through it...", LIME_GREEN, true},
	{"Fence", "", WHITE, true},
	{"Enemy", "", RED, false},
	{"Campfire", "", ORANGE, true},
	{"Shopkeeper", "", PINK, true},
	{"Scrummius", "", PURPLE, false},
	{"Tower Wall", "", GRAY, true},
	{"Friendly", "", BABY_BLUE, true},
	{"Friendly", "", LIGHT_GREEN, true},
	{"Mystery Item", "", LAVENDER, true},
	{"Old House", "", LIGHT_YELLOW, false},
	{"Old House", "", DARK_YELLOW, false},
	{"House Window", "", DARK_PURPLE, true},
	{"House Door", "", DARK_RED, false},
	{"Sign", "", BROWN, true},
	{"Ocean", "", DARK_BLUE, true},
	{"Doorway", "", BLACK, false},
	{"Building Wall", "", DARK_GRAY, true},
	{"Path","", LIGHT_GRAY, false}
};

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

	// ID Getter/Setter
	int GetID();
	void SetID(int);
  
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