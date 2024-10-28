#include <iostream>
#include "Chunk.h"
#include "ConsoleColors.h"

using namespace std;

const string CHUNK_MAP_DISPLAY = "  ";

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
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			//Check if adjacent tiles exist then connect. Incrementing and decrementing by 1 to reach adjacent tiles.
			if (row > 0)
				tiles[row][column].SetNorthTile(tiles[row - 1][column]);
			if (row < ROW_SIZE - 1)
				tiles[row][column].SetSouthTile(tiles[row + 1][column]);
			if (column < COLUMN_SIZE - 1)
				tiles[row][column].SetEastTile(tiles[row][column + 1]);
			if (column > 0)
				tiles[row][column].SetWestTile(tiles[row][column - 1]);
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
* Displays the Chunk and the Player inside of it
*/
void Chunk::DisplayPlayerChunk(int playerX, int playerY)
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			if (column == playerX && row == playerY)
				ConsoleColors::SetColor(PINK);
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
Tile& Chunk::GetTileAt(int r, int c)
{
	return tiles[r][c];
}

void Chunk::SetTileAt(int r, int c, Tile tile) {
	tiles[r][c] = tile;
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