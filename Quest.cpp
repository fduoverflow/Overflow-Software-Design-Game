#include "Quest.h"
Quest::Quest()
{
	questName = "";
	questDescription = "";
	currentObjective = "";
	itemGoal = nullptr;
	isQuestStarted = false;
	isQuestCompleted = false;
}
Quest::Quest(string n, string p, string obj, Item &i)
{
	questName = n;
	questDescription = p;
	currentObjective = obj;
	itemGoal = &i;
	isQuestStarted = false;
	isQuestCompleted = false;
}
void Quest::SetQuestName(string n) {questName = n;}
string Quest::GetQuestName() {return questName;}

void Quest::SetQuestDescription(string q) {questDescription = q;}
string Quest::GetQuestDescription() {return questDescription;}

void Quest::SetCurrentObjective(string obj) {currentObjective = obj;}
string Quest::GetCurrentObjective() {return currentObjective;}

void Quest::SetItemGoal(Item &i) {itemGoal = &i;}
Item* Quest::GetItemGoal() {return itemGoal;}


// Is QuestCompleted method -- each quest has bool to see if it completed

// Objectives: travel to the house, gather the spellbook, and leave the house -- prompts first battle

// QuestBuilder
// enum type

// start flag
// content middle
// end flag

// start -- talking to scrummius
// content - moving to the house, exploring, picking up the spellbook
//end -- getting the spellbook from the house
