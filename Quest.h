#pragma once
#include <string>
#include "Enemy.h"
#include "Item.h"

using namespace std;

// enemyGoal and Constructor with enemy are commented out for now as first quest is an item fetch type quest
class Quest
{
private:
	string questName;
	string questDescription;
	string currentObjective;     // Uupdated to be the next objective if quest has multiple steps
	Item* itemGoal;		         // The criteria to complete the quest if the criteria is to retrieve an item
	//Enemy enemyGoal;			// The criteria to complete the quest if the criteria is to kill an enemy
	bool isQuestStarted;
	bool isQuestCompleted;
public:
	Quest();						// Default constructor
	Quest(string, string, string, Item*);	// Constructor for an item quest - name, prompt, Item
	//Quest(string, string, Enemy);	// Constructor for an enemy quest

	// Setters and Getters for Quest Class
	void SetQuestName(string);
	string GetQuestName();

	void SetQuestDescription(string);
	string GetQuestDescription();

	void SetCurrentObjective(string);
	string GetCurrentObjective();

	void SetItemGoal(Item*);
	Item* GetItemGoal();

	void SetQuestStart(bool);
	bool GetQuestStart();

	void SetQuestComplete(bool);
	bool GetQuestComplete();
};



