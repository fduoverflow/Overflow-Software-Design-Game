#pragma once
#include <string>
#include "Tile.h"
#include "Chunk.h"
using namespace std;
/*
2D Array of Chunk objects that represents the map of the current location
*/

// Constant variable for row/col map size
// Change after design of map has been created
const int STARTING_AREA_ROW_SIZE = 5;
const int STARTING_AREA_COL_SIZE = 7;
class Map
{
	private:
		//This needs to mostly be hard coded to align to level design.
		Chunk startingAreaMap[STARTING_AREA_ROW_SIZE][STARTING_AREA_COL_SIZE] =
		{
			{Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID)},
			{Chunk(VALID),	 Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(VALID),   Chunk(INVALID), Chunk(INVALID)},
			{Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID)},
			{Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(VALID),   Chunk(VALID)  },
			{Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(INVALID), Chunk(VALID),   Chunk(INVALID), Chunk(INVALID)}
		};
	public:
		//Accessor methods
		void DisplayMap();
		Chunk& GetChunkAt(int r, int c);
};