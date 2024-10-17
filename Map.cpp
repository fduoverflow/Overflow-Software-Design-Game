#include <iostream>
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

void Map::Display(int x, int y) {
	ConsoleColors::EnableColor();
	ConsoleColors::SetColor(GREEN);
	chunks[x][y].DisplayChunk();
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