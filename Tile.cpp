#include <iostream>
#include "Tile.h"

using namespace std;

// Constructor: Initializes a tile with row, column, and tile ID.
// Sets default pointers to nullptr and the quest flag to an empty string.
Tile::Tile(int r, int c, int tileID)
{
	row = r;
	col = c;
	ID = tileID;
	myItem = nullptr;
	myNPC = nullptr;
	myEnemy = nullptr;
	questFlag = "";
}

// Constructor: Initializes a tile with row, column, an item, and tile ID.
// Sets pointers for NPC and enemy to nullptr and the quest flag to an empty string.
Tile::Tile(int r, int c, Item* newItem, int tileID)
{
	row = r;
	col = c;
	ID = tileID;
	myItem = newItem;
	myNPC = nullptr;
	myEnemy = nullptr;
	questFlag = "";
}

// Default Constructor: Initializes a tile with default values.
// Row, column, and ID are set to 0; all pointers are initialized to nullptr.
Tile::Tile()
{
	row = 0;
	col = 0;
	ID = 0;
	myItem = nullptr;
	myNPC = nullptr;
	myEnemy = nullptr;
	questFlag = "";
}

// Returns the row position of the tile in the map.
int Tile::GetRow()
{
	return row;
}

// Sets the row position of the tile.
void Tile::SetRow(int r)
{
	row = r;
}

// Returns the column position of the tile in the map.
int Tile::GetColumn()
{
	return col;
}

// Sets the column position of the tile.
void Tile::SetColumn(int c)
{
	col = c;
}

// Returns the unique ID of the tile, representing its type.
int Tile::GetID() {
	return ID;
}

// Sets the tile's ID to a specified value.
void Tile::SetID(int i) {
	ID = i;
}

// Returns a pointer to the item on the tile, or nullptr if no item is present.
Item* Tile::GetItem()
{
	return myItem;
}

// Sets the item on the tile to a new item.
void Tile::SetItem(Item* newItem)
{
	myItem = newItem;
}

// Returns a pointer to the NPC on the tile, or nullptr if no NPC is present.
NPC* Tile::GetNPC()
{
	return myNPC;
}

// Sets the NPC on the tile to a new NPC.
void Tile::SetNPC(NPC* newNPC)
{
	myNPC = newNPC;
}

// Returns a pointer to the enemy on the tile, or nullptr if no enemy is present.
Enemy* Tile::GetEnemy()
{
	return myEnemy;
}

// Sets the enemy on the tile to a new enemy.
void Tile::SetEnemy(Enemy* newEnemy)
{
	myEnemy = newEnemy;
}


// Pick up item method used to remove Item from Tile and return to Player.
// Item is set to default state of EMPTY to signify it has been removed.
Item& Tile::PickUpItem()
{
	Item* temp = myItem;			//Needed because myItem can not be returned then changed to EMPTY
	myItem = nullptr;
	return *temp;
}


// Displays the tile's current state with appropriate color and symbol.
// Prioritizes NPC, then item, then enemy for display if present.
// If none are present, displays the default TILE_DISPLAY.
void Tile::DisplayTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	if (myNPC != nullptr) {
		display i = myNPC->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else if (myItem != nullptr) {
		icon i = myItem->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else if (myEnemy != nullptr) {
		enemyDisplay i = myEnemy->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else
		cout << TILE_DISPLAY;
}

// Sets a quest trigger flag for the tile, used to mark its role in a quest.
void Tile::SetQuestFlag(string q)
{
	questFlag = q;
}

// Returns the quest flag for the tile.
string Tile::GetQuestFlag()
{
	return questFlag;
}

// Displays the player icon on the current tile with proper coloring.
void Tile::DisplayPlayerTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	ConsoleColors::wprint(L"🧙‍♂️", 2);
}