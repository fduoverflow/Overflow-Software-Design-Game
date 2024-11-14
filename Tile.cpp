#include <iostream>
#include "Tile.h"

using namespace std;

//Constructors
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

//Main variables getters and setters
int Tile::GetRow()
{
	return row;
}
void Tile::SetRow(int r)
{
	row = r;
}
int Tile::GetColumn()
{
	return col;
}
void Tile::SetColumn(int c)
{
	col = c;
}

// Returns the ID number of the tile, designating its type
int Tile::GetID() {
	return ID;
}

// Sets the ID to a different typeof tile
void Tile::SetID(int i) {
	ID = i;
}

//Item getters and setters
Item* Tile::GetItem()
{
	return myItem;
}
void Tile::SetItem(Item* newItem)
{
	myItem = newItem;
}

//NPC getters and setters
NPC* Tile::GetNPC()
{
	return myNPC;
}
void Tile::SetNPC(NPC* newNPC)
{
	myNPC = newNPC;
}

//Enemy getters and setters
Enemy* Tile::GetEnemy()
{
	return myEnemy;
}
void Tile::SetEnemy(Enemy* newEnemy)
{
	myEnemy = newEnemy;
}

/*
* Pick up item method used to remove Item from Tile and return to Player.
* Item is set to default state of EMPTY to signify it has been removed.
*/
Item& Tile::PickUpItem()
{
	Item* temp = myItem;			//Needed because myItem can not be returned then changed to EMPTY
	myItem = nullptr;
	return *temp;
}

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

/*
* If Tile is used for a quest, set its trigger flag as a string here.
*/
void Tile::SetQuestFlag(string q)
{
	questFlag = q;
}
//Quest flag getter
string Tile::GetQuestFlag()
{
	return questFlag;
}

/*
* Display mage emoji on player location.
*/
void Tile::DisplayPlayerTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	ConsoleColors::wprint(L"🧙‍♂️", 2);
}