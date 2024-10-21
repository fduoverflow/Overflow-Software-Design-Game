#pragma once
#include <string>
#include "Enemy.h"
#include "Item.h"

using namespace std;

class Quest
{
private:
	string name;
	string prompt;
	Item goal;			// The criteria to complete the quest if the criteria is to retrieve an item
	Enemy goal;			// The criteria to complete the quest if the criteria is to kill an enemy
public:
	Quest();						// Default constructor
	Quest(string, string, Item);	// Constructor for an item quest
	Quest(string, string, Enemy);	// Constructor for an enemy quest
};



