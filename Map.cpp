#include "Map.h"

using namespace std;

/*
* Display Map.
* Only displays VALID Chunks.
*/
void Map::DisplayMap()
{

}

/*
* Returns Chunk at given row and col
*/
Chunk& Map::GetChunkAt(int r, int c)
{
	return startingAreaMap[r][c];
}