#pragma once
#include "ConsoleColors.h"
#include <string>

using namespace std;

enum BLOCK_TYPE { GRASS, WATER, TREE, FLOOR };

struct Block {
	string name;
	BLOCK_TYPE ID;
	string description;
	Color color;
	bool collides;
};

const int NUM_BLOCK_TYPES = 4;


Block BLOCK_TYPES[NUM_BLOCK_TYPES] = {
	{"Grass", GRASS, "just a silly block of grass", GREEN, false},
	{"Water", WATER, "it's cold to the touch", BLUE, true},
	{"Tree", TREE, "the shade it's leaves bring is relaxing", DARK_GREEN, true},
	{"Floor", FLOOR, "what a nice pattern!", DARK_ORANGE, false}
};