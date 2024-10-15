#include "UserInterface.h"
#include <iostream>

// Ryan work

string UserInterface::DisplayRules()

{
    rules = "General tips for success:\n";
    rules += "1. Use WASD to move your character (W = up, A = left, S = down, D = right).\n";
    rules += "2. Gather equipment and food for survival.\n";
    rules += "3. Defeat bosses to progress.\n";
    rules += "4. Explore the world and interact with NPCs to receive quests.\n";
    rules += "5. Reach the land of Scrum to rescue Gapplin and defeat Vallonious.\n";

    cout << rules << endl; // Print the rules to the console
    return rules; // Return the rules as a string
}

string UserInterface::DisplayIntroMessage()
{
    introMessage = "Backstory:\n";
    introMessage += "You are a wizard in the land of [insert name].\n";
    introMessage += "While having a picnic with your pet Gapplin, the dragon wizard Vallonious swoops in and steals Gapplin.\n";
    introMessage += "Now, you must travel to the land of Scrum, gather the right equipment, and defeat Vallonious to rescue Gapplin.\n";

    cout << introMessage << endl; // Print the backstory to the console
    return introMessage; // i watn the backstory to come back to me as a string
}
