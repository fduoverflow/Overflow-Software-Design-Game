#pragma once
#include <string>
#include "Tile.h"
#include "Chunk.h"
using namespace std;

/*
The Map class represents a 2D array of Chunk objects, forming the map for the player's current location.
Maps are structured based on a grid of chunks, and their layout aligns with the level design.
*/
class Map
{
	private:
		Chunk** chunks;				// Pointer to a 2D array of Chunk objects that make up the map.
		int numRows, numColumns;	// Number of rows and columns of chunks in the map.
	public:
		// Default constructor.
		Map();

		// Parameterized constructor, initializes the map.
		// Uses a file holding the map data, and takes in the map's size (rows and columns)
		Map(string, int, int);

		// Displays the entire map with a marker for the player's position.
		void DisplayMap(int, int, wstring);

		// Displays the current visible chunk
		void Display(int, int, int, int);

		// Displays the chunk at x, y
		void DisplayChunkAt(int, int);

		// Retrieves a reference to the chunk at the specified coordinates.
		Chunk& GetChunkAt(int r, int c);

		// Retrieves the number of columns in the map.
		int GetNumColumns();

		// Retrieves the number of rows in the map.
		int GetNumRows();
};