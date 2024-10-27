#include "NPC.h" 
#include <iostream> 

// Constructor definition
// Initializes the NPC with a specified name and dialogue
NPC::NPC(string name, string dialogue)
    : name(name), dialogue(dialogue) {}

// talk() method definition
// This method displays the NPC's name and dialogue when called
void NPC::talk() {
    // Prints a message to the console, showing the NPC's name and their dialogue
    cout << name << " says: " << dialogue << endl;
}
