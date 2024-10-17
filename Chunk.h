#pragma once
#include "Tile.h"
#include <string>
using namespace std;

enum ChunkType { VALID, INVALID };

const int ROW_SIZE = 16;
const int COLUMN_SIZE = 16;

/*
Chunk class will hold information for a group of 16x16 tiles of the Map
Chunk can either be valid or invalid, noting it's ability for a player to move onto it
*/
class Chunk
{
	private:
		Tile tiles[ROW_SIZE][COLUMN_SIZE];
		ChunkType type;
	public:
		//Constructor
		Chunk(ChunkType);

		//Accessor methods
		void DisplayChunk();
		void DisplayPlayerChunk(int, int);
		void DisplayChunkInMap();
		Tile& GetTileAt(int r, int c);
		ChunkType getType();
};

