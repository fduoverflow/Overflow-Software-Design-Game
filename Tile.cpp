#include <iostream>
#include "Tile.h"

using namespace std;

Tile::Tile() {
	description = "";
}

Tile::Tile(string desc) {
	description = desc;
}

string Tile::GetDescription() {
	return description;
}

void Tile::SetDescription(string desc) {
	description = desc;
}

void Tile::DisplayTile() {
	cout << TILE_DISPLAY;
}