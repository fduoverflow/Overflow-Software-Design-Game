#include <iostream>
#include "Chunk.h"

using namespace std;

Chunk::Chunk(ChunkType type) {
	if (type == VALID) {
		for (int column = 0; column < COLUMN_SIZE; column++) {
			for (int row = 0; row < ROW_SIZE; row++) {
				tiles[column][row] = Tile("", row, column);			//might want to switch tiles[column][row] to tiles[row][column] for better readability
			}
		}

		//Connect tiles in chunk to each other
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int column = 0; column < COLUMN_SIZE; column++)
			{
				//Check if adjacent tiles exist then connect. Incrementing and decrementing by 1 to reach adjacent tiles.
				if(row > 0)
					tiles[row][column].SetNorthTile(tiles[row - 1][column]);
				if(row < ROW_SIZE - 1)
					tiles[row][column].SetSouthTile(tiles[row + 1][column]);
				if(column < COLUMN_SIZE - 1)
					tiles[row][column].SetEastTile(tiles[row][column + 1]);
				if(column > 0)
					tiles[row][column].SetWestTile(tiles[row][column - 1]);
			}
		}
	}
}

void Chunk::DisplayChunk() {
	for (int column = 0; column < COLUMN_SIZE; column++) {
		for (int row = 0; row < ROW_SIZE; row++) {
			tiles[column][row].DisplayTile();
		}
		cout << endl;
	}
}

/*
* Get Tile at location r, c.
* Currently does not check for valid parameters.
* Needed to change method to pass Tile by reference so that changes to the array can be made in other classes.
*/
Tile& Chunk::GetTileAt(int r, int c)
{
	return tiles[r][c];
}