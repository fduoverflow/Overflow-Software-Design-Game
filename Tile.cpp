#include <iostream>
#include "Tile.h"
#include "ConsoleColors.h"
using namespace std;

//enum BLOCK_TYPE { GRASS, WATER, TREE, FLOOR, BUSH };

struct Block {
	string name;
	string description;
	Color color;
	bool collides;
};

const int NUM_BLOCK_TYPES = 19;


Block BLOCK_TYPES[NUM_BLOCK_TYPES] = {
	{"Grass", "just a silly block of grass", DARK_GREEN, false},
	{"Water", "it's cold to the touch", LIGHT_BLUE, true},
	{"Bridge", "", BROWN, false},
	{"Dirt", "what a nice pattern!", TAN, false},
	{"Bush", "there's pointy thorns in this bush. you probably shouldn't walk through it...", LIME_GREEN, true},
	{"Fence", "", WHITE, true},
	{"Enemy", "", RED, true},
	{"Campfire", "", ORANGE, true},
	{"Shopkeeper", "", PINK, true},
	{"Scrummius", "", PURPLE, true},
	{"Tower Wall", "", GRAY, true},
	{"Friendly", "", BABY_BLUE, true},
	{"Friendly", "", LIGHT_GREEN, true},
	{"Mystery Item", "", LAVENDER, true},
	{"Old House", "", LIGHT_YELLOW, true},
	{"Old House", "", DARK_YELLOW, true},
	{"House Window", "", DARK_PURPLE, true},
	{"House Door", "", DARK_RED, true},
	{"Sign", "", BROWN, true}
};

//Constructors
Tile::Tile(int r, int c, int tileID)
{
	row = r;
	col = c;
	ID = tileID;
	myItem = Item();
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
}
Tile::Tile(int r, int c, Item newItem, int tileID)
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
}
Tile::Tile()
{
	row = 0;
	col = 0;
	ID = 0;
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
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

//Item getters and setters
Item Tile::GetItem()
{
	return myItem;
}
void Tile::SetItem(Item newItem)
{
	myItem = newItem;
}

/*
* Pick up item method used to remove Item from Tile and return to Player.
* Item is set to default state of EMPTY to signify it has been removed.
*/
Item Tile::PickUpItem()
{
	Item temp = myItem;			//Needed because myItem can not be returned then changed to EMPTY
	myItem = Item();
	return temp;
}

/*
* Adjacent tiles getters and setters
* Getters throw int 404 as exception when out of bounds.
* Getters pass reference to allow other classes to change Tile values.
*/
Tile& Tile::GetNorthTile()
{
	if (northTile != nullptr)
		return *northTile;
	else
		throw 404;
}
Tile& Tile::GetSouthTile()
{
	if (southTile != nullptr)
		return *southTile;
	else
		throw 404;
}
Tile& Tile::GetEastTile()
{
	if (eastTile != nullptr)
		return *eastTile;
	else
		throw 404;
}
Tile& Tile::GetWestTile()
{
	if (westTile != nullptr)
		return *westTile;
	else
		throw 404;
}
void Tile::SetNorthTile(Tile& targetTile)
{
	northTile = &targetTile;
}
void Tile::SetSouthTile(Tile& targetTile)
{
	southTile = &targetTile;
}
void Tile::SetEastTile(Tile& targetTile)
{
	eastTile = &targetTile;
}
void Tile::SetWestTile(Tile& targetTile)
{
	westTile = &targetTile;
}
void Tile::DisplayTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	cout << TILE_DISPLAY;
}