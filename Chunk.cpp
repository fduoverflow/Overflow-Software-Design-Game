#include <iostream>
#include "Chunk.h"
#include "ConsoleColors.h"

using namespace std;

// Default Constructor: Initializes a chunk as INVALID with default tiles.
// All tiles in the chunk are set to their default state.
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

// Constructor: Initializes a chunk with a specified type(VALID or INVALID).
// If the chunk is VALID, it populates the tiles with default tiles.
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

// Displays the chunk where the player is currently positioned.
// Takes the player's row and column position as arguments.
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


// Displays the full chunk with no objects inside of it.
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


// Displays the minimap version of a chunk, the size of a tile.
void Chunk::DisplayChunkInMap() {
	if (type == INVALID)
		ConsoleColors::SetColor(BLACK);
	if (type == VALID)
		ConsoleColors::SetColor(LIME_GREEN);
	cout << CHUNK_MAP_DISPLAY;
}


// Get Tile at location r, c.
// Does not check for valid parameters.
Tile& Chunk::GetTileAt(int x, int y)
{
	return tiles[y][x];
}

// Sets a specific tile at the given row and column.
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

//Update Enemy pointers when an Enemy is defeated
void Chunk::EnemyDefeted(Enemy* defetedEnemy)
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int column = 0; column < COLUMN_SIZE; column++)
		{
			if (tiles[row][column].GetEnemy() != nullptr && tiles[row][column].GetEnemy() == defetedEnemy)
				tiles[row][column].SetEnemy(nullptr);
		}
	}
}