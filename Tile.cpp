#include <iostream>
#include "Tile.h"
using namespace std;

//Constructors
Tile::Tile(string desc, int r, int c)
{
	description = desc;
	row = r;
	col = c;
	myItem = Item();
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
}
Tile::Tile(string desc, int r, int c, Item newItem)
{
	description = desc;
	row = r;
	col = c;
	myItem = newItem;
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
}
Tile::Tile()
{
	description = "";
	row = 0;
	col = 0;
	northTile = nullptr;
	southTile = nullptr;
	eastTile = nullptr;
	westTile = nullptr;
}

//Main variables getters and setters
string Tile::GetDescription()
{
	return description;
}
void Tile::SetDescription(string desc)
{
	description = desc;
}
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
void Tile::SetNorthTile(Tile &targetTile)
{
	northTile = &targetTile;
}
void Tile::SetSouthTile(Tile &targetTile)
{
	southTile = &targetTile;
}
void Tile::SetEastTile(Tile &targetTile)
{
	eastTile = &targetTile;
}
void Tile::SetWestTile(Tile &targetTile)
{
	westTile = &targetTile;
}
void Tile::DisplayTile() 
{
	cout << TILE_DISPLAY;
}