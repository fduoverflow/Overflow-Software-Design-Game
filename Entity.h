#pragma once
#include <string>

using namespace std;

class Entity
{
private:
	string name;			// Name of the Entity
	string dialogue;		// What the Entity will say when interacted with
public:
	Entity();					// Default constructor
	Entity(string, string);	// Constructor to include name, dialogue
};

