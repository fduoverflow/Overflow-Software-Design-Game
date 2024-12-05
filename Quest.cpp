#include "Quest.h"

/*
* Default constructor
*/
Quest::Quest()
{
	questName = "";
	questDescription = "";
	currentObjective = "";
	itemGoal = nullptr;
	isQuestStarted = false;
	isQuestCompleted = false;
}

/*
* Quest constructor that assigns a name, description, objective, and item pointer.
*/
Quest::Quest(string n, string p, string obj, Item *i)
{
	questName = n;
	questDescription = p;
	currentObjective = obj;
	itemGoal = i;
	isQuestStarted = false;
	isQuestCompleted = false;
}

//Parameter setters/getters
void Quest::SetQuestName(string n) {questName = n;}
string Quest::GetQuestName() {return questName;}

void Quest::SetQuestDescription(string q) {questDescription = q;}
string Quest::GetQuestDescription() {return questDescription;}

void Quest::SetCurrentObjective(string obj) {currentObjective = obj;}
string Quest::GetCurrentObjective() {return currentObjective;}

void Quest::SetItemGoal(Item *i) {itemGoal = i;}
Item* Quest::GetItemGoal() {return itemGoal;}

void Quest::SetQuestStart(bool start) {isQuestStarted = start;}
bool Quest::GetQuestStart() {return isQuestStarted;}

void Quest::SetQuestComplete(bool end) {isQuestCompleted = end;}
bool Quest::GetQuestComplete() {return isQuestCompleted;}
