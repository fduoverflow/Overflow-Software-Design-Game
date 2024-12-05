#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Map.h"
#include "ConsoleColors.h"

using namespace std;


// Default constructor for the Map class.
// Initializes an empty map with no rows and columns.
Map::Map() {
	numRows = 0;
	numColumns = 0;
}

// Parameterized constructor for the Map class.
// Reads a map file and initializes a 2D grid of chunks based on the input file.
Map::Map(string fileName, int rows, int columns) {
	numRows = rows;				// number of chunks
	numColumns = columns;		// number of columns
	chunks = new Chunk*[rows];

	for (int row = 0; row < rows; row++) {
		chunks[row] = new Chunk[columns];  // Allocate a new array of Chunk for each row
	}

	std::ifstream file(fileName);  // Open the file

	// Check if the file was successfully opened
	if (!file) {
		std::cerr << "Error: Could not open the map file." << std::endl;
		return;
	}

	Chunk currentChunk;
	int mapRow = -1, mapColumn = -1;
	int chunkRowCount = -1;
	std::string line;
	// Read the file line by line
	while (getline(file, line)) {
		// Checks to see if we've reached a new chunk
		if (line[0] == '(') {
			// captures the coordinates of this chunk
			// Remove the '(' character
			line.erase(0, 1);  // Remove the first character
			line.erase(line.size() - 1); // Remove the last character

			// Parse the remaining string
			mapColumn = stoi(line.substr(0, line.find(',')));
			mapRow = stoi(line.substr(line.find(',') + 1));

			currentChunk = Chunk(); // creates a new chunk
			currentChunk.setType(VALID); // registers the chunk as a playable chunk
			chunkRowCount++; // increases chunkRowCount so the line satisfies the below if statement
			continue;
		}
		// Check to see if we're currently in a chunk
		if (chunkRowCount > -1) {
			// Populates rows 0-15
			stringstream ss(line);
			int ID = 0;
			int chunkColumnCount = 0;
			while (ss >> ID) {
				Tile currentTile(0, 0, ID);
				currentChunk.SetTileAt(chunkColumnCount, chunkRowCount, currentTile);
				chunkColumnCount++;
			}
			// Places the completed chunk into the map and resets chunkRowCount if we've reached the last row
			if (chunkRowCount >= 15) {
				chunks[mapRow][mapColumn] = currentChunk;
				chunkRowCount = -1;
			}
			else
				chunkRowCount++;
		}
	}

	file.close();  // Close the file after reading
	return;
}

// Displays the current visible chunk
void Map::Display(int chunkX, int chunkY, int tileX, int tileY) {
	ConsoleColors::EnableColor();
	chunks[chunkY][chunkX].DisplayPlayerChunk(tileX, tileY);
	ConsoleColors::DisableColor();
}

// Displays the chunk at x, y
void Map::DisplayChunkAt(int chunkX, int chunkY) {
	ConsoleColors::EnableColor();
	chunks[chunkY][chunkX].DisplayChunk();
	ConsoleColors::DisableColor();
}

/*
* Display Map.
* Only displays VALID Chunks.
*/
void Map::DisplayMap(int x, int y, wstring icon)
{
	ConsoleColors::EnableColor();
	for (int row = 0; row < numRows; row++) {
		Chunk *chunksInRow = chunks[row];
		for (int column = 0; column < numColumns; column++) {
			if (chunksInRow[column].getType() == INVALID)
				ConsoleColors::SetColor(GRAY);
			else
				ConsoleColors::SetColor(LIME_GREEN);
			if (x == column && y == row)
				ConsoleColors::wprint(icon, 2);
			else
				cout << CHUNK_MAP_DISPLAY;
		}
		cout << endl;
	}
	ConsoleColors::DisableColor();
}

// Returns Chunk at given row and col
Chunk& Map::GetChunkAt(int x, int y)
{
	return chunks[y][x];
}

// Retrieves the number of columns in the map.
int Map::GetNumColumns() {
	return numColumns;
}

// Retrieves the number of rows in the map.
int Map::GetNumRows() {
	return numRows;
}