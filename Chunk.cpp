#include <iostream>
#include "Chunk.h"
#include "ConsoleColors.h"

using namespace std;

// Default Constructor
Chunk::Chunk() {
	type = INVALID;
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			tiles[row][column] = Tile();
		}
	}
}

/*
* Constructor.
*/
Chunk::Chunk(ChunkType chunkType) 
{
	type = chunkType;
	if (type == VALID)
	{
		//Fill array
		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int column = 0; column < COLUMN_SIZE; column++)
			{
				tiles[row][column] = Tile();
			}
		}
	}
}

/*
* Displays the Chunk and the Player inside of it
*/
void Chunk::DisplayPlayerChunk(int playerX, int playerY)
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			if (column == playerX && row == playerY)
				tiles[row][column].DisplayPlayerTile();
			else
				tiles[row][column].DisplayTile();
		}
		cout << endl;
	}
}

/*
* Displays the full chunk with no objects inside of it.
*/
void Chunk::DisplayChunk()
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			tiles[row][column].DisplayTile();
		}
		cout << endl;
	}
}

/*
* Displays the map version of a chunk, the size of a tile.
*/
void Chunk::DisplayChunkInMap() {
	if (type == INVALID)
		ConsoleColors::SetColor(BLACK);
	if (type == VALID)
		ConsoleColors::SetColor(LIME_GREEN);
	cout << CHUNK_MAP_DISPLAY;
}

/*
* Get Tile at location r, c.
* Currently does not check for valid parameters.
* Needed to change method to pass Tile by reference so that changes to the array can be made in other classes.
*/
Tile& Chunk::GetTileAt(int x, int y)
{
	return tiles[y][x];
}

void Chunk::SetTileAt(int x, int y, Tile tile) {
	tiles[y][x] = tile;
}

//Return Chunk type
ChunkType Chunk::getType()
{
	return type;
}

// Sets Chunk type
void Chunk::setType(ChunkType t) {
	type = t;
}