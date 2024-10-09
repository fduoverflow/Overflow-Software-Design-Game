#include <iostream>
#include "Tile.h"
using namespace std;

//Constructors
Tile::Tile(string desc, int r, int c)
{
	description = desc;
	row = r;
	col = c;
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

//Adjacent tiles getters and setters
Tile Tile::GetNorthTile()
{
	return *northTile;
}
Tile Tile::GetSouthTile()
{
	return *southTile;
}
Tile Tile::GetEastTile()
{
	return *eastTile;
}
Tile Tile::GetWestTile()
{
	return *westTile;
}
void Tile::SetNorthTile(Tile &targetTile)
{
	northTile = &targetTile;
}
void Tile::SetSouthTile(Tile targetTile)
{
	southTile = &targetTile;
}
void Tile::SetEastTile(Tile targetTile)
{
	eastTile = &targetTile;
}
void Tile::SetWestTile(Tile targetTile)
{
	westTile = &targetTile;
}
void Tile::DisplayTile() 
{
	cout << TILE_DISPLAY;
}