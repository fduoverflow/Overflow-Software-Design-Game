#include "Quest.h"
Quest::Quest()
{
	name = "";
	prompt = "";
	itemGoal = Item();
}
Quest::Quest(string n, string p, Item i)
{
	name = name;
	prompt = prompt;
	itemGoal = i;
}