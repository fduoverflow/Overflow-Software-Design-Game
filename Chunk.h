#pragma once
#include "Tile.h"
#include <string>
using namespace std;

// Enum to represent whether a chunk is valid or invalid.
// Valid chunks are accessible by the player; invalid ones are not.
enum ChunkType { VALID, INVALID };

// Constants defining the dimensions of a chunk (16x16 grid of tiles).
const int ROW_SIZE = 16;		// Number of rows in a chunk.
const int COLUMN_SIZE = 16;		// Number of columns in a chunk.

// Default display representation for a chunk on the minimap.
const string CHUNK_MAP_DISPLAY = "  ";

/*
The Chunk class represents a group of 16x16 tiles in the game world.
Each chunk can be either "valid" (accessible by the player) or "invalid" (inaccessible).
Chunks are used to structure and manage the map efficiently.
*/
class Chunk
{
	private:
		Tile tiles[ROW_SIZE][COLUMN_SIZE];	// 2D array of tiles representing the chunk.
		ChunkType type;						// Indicates if the chunk is valid or invalid.

	public:
		//Constructors
		Chunk();			// Default constructor initializes a chunk with default values.
		Chunk(ChunkType);	// Initializes a chunk with a specified type (VALID or INVALID).

		// Displays the entire chunk in a formatted manner.
		void DisplayChunk();

		// Displays the chunk where the player is currently positioned.
		// Takes the player's row and column position as arguments.
		void DisplayPlayerChunk(int, int);

		// Displays the chunk as part of a minimap representation.
		void DisplayChunkInMap();

		// Retrieves a reference to the tile at the specified row and column.
		Tile& GetTileAt(int x, int y);

		// Sets a specific tile at the given row and column.
		void SetTileAt(int x, int y, Tile t);

		// Returns the type of the chunk (VALID or INVALID).
		ChunkType getType();

		// Sets the type of the chunk (VALID or INVALID).
		void setType(ChunkType);

		//Update Enemy pointers when an Enemy is defeated
		void EnemyDefeted(Enemy* defetedEnemy);
};

