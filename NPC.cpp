#include "NPC.h" 
#include <iostream> 

// Constructor definition
// Initializes the NPC with a specified name and dialogue
NPC::NPC(string n, string d)
{
    name = n;
    dialogue = d;
}

NPC::NPC()
{
    name = "";
    dialogue = "";
}

// Talk() method definition
// This method displays the NPC's name and dialogue when called
void NPC::Talk() {
    // Prints a message to the console, showing the NPC's name and their dialogue
    cout << name << " says: " << dialogue << endl;
}

//Name getters and setters
string NPC::GetName()
{
    return name;
}
void NPC::SetName(string n)
{
    name = n;
}

//dialogue getters and setters
string NPC::GetDialogue()
{
    return dialogue;
}
void NPC::SetDialogue(string d)
{
    dialogue = d;
}
