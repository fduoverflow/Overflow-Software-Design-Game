#pragma once
#include <string>
#include "Map.h"
using namespace std;

/*
This class will hold methods that will output messages (to the console) that is relevant to the player.
Examples of constant messages: rules and intro message (backstory)
These will be set in the corresponding .cpp file
*/
class UserInterface
{
	private:
		string rules;
		string introMessage;
		
	public:
		string DisplayRules();
		string DisplayIntroMessage();
		void DisplayMap(Map playerMap);
};

