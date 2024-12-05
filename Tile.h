#pragma once
#include <string>
#include "ConsoleColors.h"
#include "Item.h"
#include "NPC.h"
#include "Enemy.h"
using namespace std;

// Default display representation for a tile.
const string TILE_DISPLAY = "  ";

// Represents a type of block in the game world.
struct Block {
	string name;		// Name of the block type (e.g., "Grass").
	string description;	// Description of the block type.
	Color color;		// Display color of the block.
	bool collides;		// Whether the block prevents movement (true = impassable).
};

// Total number of block types available.
const int NUM_BLOCK_TYPES = 23;

// Array defining all block types with their properties.
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
	int ID;		// Unique identifier for the tile.
	int row;	// Row position of the tile in the chunk.
	int col;	// Column position of the tile in the chunk.

	// Used to flag tiles as part of a quest.
	string questFlag;

	// Pointer to an item present on the tile.
	Item* myItem;

	// Pointer to an NPC present on the tile.
	NPC* myNPC;

	// Pointer to an enemy present on the tile.
	Enemy* myEnemy;

public:
	// Displays information about the tile in a standard format.
	void DisplayTile();
	// Displays tile information specifically for the player's current position.
	void DisplayPlayerTile();

	// Accessor and mutator for the row position of the tile.
	int GetRow();
	void SetRow(int r);

	// Accessor and mutator for the column position of the tile.
	int GetColumn();
	void SetColumn(int c);

	// Accessor and mutator for the tile's unique ID.
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

	// Accessor and mutator for the quest flag associated with the tile.
	string GetQuestFlag();
	void SetQuestFlag(string questFlag);

	// Removes and returns a reference to the item on the tile.
	Item& PickUpItem();

	//Constructors
	Tile(int r, int c, int tileID);					// Initialize with position and ID.
	Tile(int r, int c, Item* newItem, int tileID);	// Initialize with item, position, and ID.
	Tile();											// Default constructor.
};