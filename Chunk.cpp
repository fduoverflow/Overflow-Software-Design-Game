#include <iostream>
#include "Chunk.h"

using namespace std;

/*
* Constructor.
*/
Chunk::Chunk(ChunkType type) 
{
	myChunkType = type;
	if (type == VALID) 
	{
		//Fill array
		for (int row = 0; row < ROW_SIZE; row++) 
		{
			for (int column = 0; column < COLUMN_SIZE; column++) 
			{
				tiles[row][column] = Tile("", row, column);
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

/*
* Display Chunk.
*/
void Chunk::DisplayChunk()
{
	if (myChunkType == VALID) {
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int column = 0; column < COLUMN_SIZE; column++)
			{
				tiles[row][column].DisplayTile();
			}
			cout << endl;
		}
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

//Return Chunk type
ChunkType Chunk::getType()
{
	return myChunkType;
}