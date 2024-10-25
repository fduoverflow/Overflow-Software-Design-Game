#pragma once
#include <string>
#include "Enemy.h"
#include "Item.h"

using namespace std;

// enemyGoal and Constructor with enemy are commented out for now as first quest is an item fetch type quest
class Quest
{
private:
	string name;
	string prompt;
	Item itemGoal;			// The criteria to complete the quest if the criteria is to retrieve an item
	//Enemy enemyGoal;			// The criteria to complete the quest if the criteria is to kill an enemy
public:
	Quest();						// Default constructor
	Quest(string, string, Item);	// Constructor for an item quest - name, prompt, Item
	//Quest(string, string, Enemy);	// Constructor for an enemy quest
};



