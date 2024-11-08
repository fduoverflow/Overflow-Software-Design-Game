#include <iostream>
#include "Tile.h"
#include "ConsoleColors.h"
using namespace std;

//enum BLOCK_TYPE { GRASS, WATER, TREE, FLOOR, BUSH };

struct Block {
	string name;
	string description;
	Color color;
	bool collides;
};

const int NUM_BLOCK_TYPES = 19;


Block BLOCK_TYPES[NUM_BLOCK_TYPES] = {
	{"Grass", "just a silly block of grass", DARK_GREEN, false},
	{"Water", "it's cold to the touch", LIGHT_BLUE, true},
	{"Bridge", "", BROWN, false},
	{"Dirt", "what a nice pattern!", TAN, false},
	{"Bush", "there's pointy thorns in this bush. you probably shouldn't walk through it...", LIME_GREEN, true},
	{"Fence", "", WHITE, true},
	{"Enemy", "", RED, true},
	{"Campfire", "", ORANGE, true},
	{"Shopkeeper", "", PINK, true},
	{"Scrummius", "", PURPLE, true},
	{"Tower Wall", "", GRAY, true},
	{"Friendly", "", BABY_BLUE, true},
	{"Friendly", "", LIGHT_GREEN, true},
	{"Mystery Item", "", LAVENDER, true},
	{"Old House", "", LIGHT_YELLOW, true},
	{"Old House", "", DARK_YELLOW, true},
	{"House Window", "", DARK_PURPLE, true},
	{"House Door", "", DARK_RED, true},
	{"Sign", "", BROWN, true}
};

//Constructors
Tile::Tile(int r, int c, int tileID)
{
	row = r;
	col = c;
	ID = tileID;
	myItem = nullptr;
	myNPC = nullptr;
	questFlag = "";
}
Tile::Tile(int r, int c, Item* newItem, int tileID)
{
	row = r;
	col = c;
	ID = tileID;
	myItem = newItem;
	myNPC = nullptr;
	questFlag = "";
}
Tile::Tile()
{
	row = 0;
	col = 0;
	ID = 0;
	myItem = nullptr;
	myNPC = nullptr;
	questFlag = "";
}

//Main variables getters and setters
int Tile::GetRow()
{
	return row;
}
void Tile::SetRow(int r)
{
	row = r;
}
int Tile::GetColumn()
{
	return col;
}
void Tile::SetColumn(int c)
{
	col = c;
}

//Item getters and setters
Item* Tile::GetItem()
{
	return myItem;
}
void Tile::SetItem(Item* newItem)
{
	myItem = newItem;
}

//NPC getters and setters
NPC* Tile::GetNPC()
{
	return myNPC;
}
void Tile::SetNPC(NPC* newNPC)
{
	myNPC = newNPC;
}

//Enemy getters and setters
Enemy* Tile::GetEnemy()
{
	return myEnemy;
}
void Tile::SetEnemy(Enemy* newEnemy)
{
	myEnemy = newEnemy;
}

/*
* Pick up item method used to remove Item from Tile and return to Player.
* Item is set to default state of EMPTY to signify it has been removed.
*/
Item& Tile::PickUpItem()
{
	Item* temp = myItem;			//Needed because myItem can not be returned then changed to EMPTY
	myItem = nullptr;
	return *temp;
}

void Tile::DisplayTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	if (myNPC != nullptr) {
		display i = myNPC->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else if (myItem != nullptr) {
		icon i = myItem->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else if (myEnemy != nullptr) {
		enemyDisplay i = myEnemy->GetIcon();
		ConsoleColors::wprint(i.emoji, i.size);
	}
	else
		cout << TILE_DISPLAY;
}

/*
* If Tile is used for a quest, set its trigger flag as a string here.
*/
void Tile::SetQuestFlag(string q)
{
	questFlag = q;
}
//Quest flag getter
string Tile::GetQuestFlag()
{
	return questFlag;
}

/*
* Display mage emoji on player location.
*/
void Tile::DisplayPlayerTile()
{
	ConsoleColors::SetColor(BLOCK_TYPES[ID].color);
	ConsoleColors::wprint(L"🧙‍♂️", 2);
}