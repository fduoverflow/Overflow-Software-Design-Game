#pragma once
#include <string>
#include "Enemy.h"
#include "Item.h"

using namespace std;

// enemyGoal and Constructor with enemy are commented out for now as first quest is an item fetch type quest
class Quest
{
private:
	//Quest strings that describe the quest
	string questName;
	string questDescription;
	string currentObjective;     // Uupdated to be the next objective if quest has multiple steps
	
	//Potential item reward
	Item* itemGoal;		         // The criteria to complete the quest if the criteria is to retrieve an item

	//Controller bools
	bool isQuestStarted;
	bool isQuestCompleted;
public:
	Quest();						// Default constructor
	Quest(string, string, string, Item*);	// Constructor for an item quest - name, prompt, Item

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



