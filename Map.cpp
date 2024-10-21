#include <iostream>
#include <fstream>
#include "Map.h"
#include "ConsoleColors.h"

using namespace std;

Map::Map() {
	numRows = 0;
	numColumns = 0;
}

Map::Map(Chunk** chunkList, int rows, int cols) {
	chunks = chunkList;
	numRows = rows;
	numColumns = cols;
}

Map::Map(string fileName, int rows, int columns) {
	numRows = rows;
	numColumns = columns;

	std::ifstream file(fileName);  // Open the file

	// Check if the file was successfully opened
	if (!file) {
		std::cerr << "Error: Could not open the map file." << std::endl;
		return;
	}

	std::string line;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Output the line to the console
	}

	file.close();  // Close the file after reading
	return;
}

void Map::Display(int chunkX, int chunkY, int tileX, int tileY) {
	ConsoleColors::EnableColor();
	chunks[chunkX][chunkY].DisplayPlayerChunk(tileX, tileY);
	ConsoleColors::DisableColor();
}

/*
* Display Map.
* Only displays VALID Chunks.
*/
void Map::DisplayMap()
{
	ConsoleColors::EnableColor();
	for (int row = 0; row < numRows; row++) {
		Chunk *chunksInRow = chunks[row];
		for (int column = 0; column < numColumns; column++)
			chunksInRow[column].DisplayChunkInMap();
		cout << endl;
	}
	ConsoleColors::DisableColor();
}

/*
* Returns Chunk at given row and col
*/
Chunk& Map::GetChunkAt(int r, int c)
{
	return chunks[r][c];
}