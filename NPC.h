#ifndef NPC_H 
#define NPC_H

#include <string> 
using namespace std;

struct display {
    wstring emoji;
    int size;
};

class NPC {
public:
    // Constructor for NPC
    // Takes a name (e.g., "Scrummius the Owl") and dialogue string (e.g., "Hellooo! My name is Scrummius the Owl, and I am quite pleased to meet yooou!") as parameters
    NPC(string name, display icon, string dialogue);
    NPC();

    // Method to initiate a conversation with the NPC
    // Displays the NPC's dialogue to the player
    void Talk();

    //Name getters and setters
    string GetName();
    void SetName(string n);

    //Display getter
    display GetIcon();

    //dialogue getters and setters
    string GetDialogue();
    void SetDialogue(string d);

private:
    // Name of the NPC, used to identify the character (e.g., "Scrummius the Owl")
    string name;

    
    display icon;

    // Dialogue that the NPC will say to the player
    string dialogue;
};

#endif 
