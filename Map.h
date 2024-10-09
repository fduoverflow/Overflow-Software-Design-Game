#pragma once
#include <string>
#include "Tile.h"
using namespace std;
/*
2D Array of Tile objects that represents the map of the current location
*/

// Constant variable for row/col map size
// Change after design of map has been created
const int STARTING_AREA_ROW_SIZE = 3;
const int STARTING_AREA_COL_SIZE = 3;
class Map
{
	private:
		Tile startingAreaMap[STARTING_AREA_ROW_SIZE][STARTING_AREA_COL_SIZE];
	public:
		void DisplayMap();
};