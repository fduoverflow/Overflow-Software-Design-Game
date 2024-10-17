#include "Map.h"

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

/*
* Display Map.
* Only displays VALID Chunks.
*/
void Map::DisplayMap()
{
	for (int row = numRows - 1; row >= 0; row--) {
		Chunk *chunksInRow = chunks[row];
		for (int column = 0; column < numColumns; column++)
			chunksInRow[column].DisplayChunk();
	}
}

/*
* Returns Chunk at given row and col
*/
Chunk& Map::GetChunkAt(int r, int c)
{
	return chunks[r][c];
}