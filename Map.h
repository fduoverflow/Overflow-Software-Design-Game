#pragma once
#include <string>
#include "Tile.h"
#include "Chunk.h"
using namespace std;
/*
2D Array of Chunk objects that represents the map of the current location
*/

class Map
{
	private:
		//This needs to mostly be hard coded to align to level design.
		Chunk** chunks;
		int numRows, numColumns;
	public:
		Map();
		Map(Chunk**, int, int);
		//Accessor methods
		void DisplayMap();
		void Display(int, int, int, int);
		Chunk& GetChunkAt(int r, int c);
};