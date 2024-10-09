#include <iostream>
#include "Chunk.h"

using namespace std;

Chunk::Chunk(ChunkType type) {
	if (type == VALID) {
		for (int column = 0; column < COLUMN_SIZE; column++) {
			for (int row = 0; row < ROW_SIZE; row++) {
				tiles[column][row] = Tile();
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

