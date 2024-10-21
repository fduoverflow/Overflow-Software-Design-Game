#pragma once
#include "Entity.h"
#include <string>

using namespace std;

class NPC:Entity
{
private:
	string name;			// Name of the NPC
	string dialogue;		// What the NPC will say when interacted with
public:
	NPC();					// Default constructor
	NPC(string, string);	// Constructor to include name, dialogue
};

