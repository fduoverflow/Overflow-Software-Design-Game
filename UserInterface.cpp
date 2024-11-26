#include "UserInterface.h"
#include <iostream>

// Ryan work

string UserInterface::DisplayRules()

{
    rules = "General tips for success:\n";
    rules += "1. Use WASD to move your character (W = up, A = left, S = down, D = right).\n";
    rules += "2. Use MAP to view the overworld map.\n";
    rules += "3. Use HEALTH to view your current health.\n";
    rules += "4. Use INV to view what is in your inventory.\n";
    rules += "5. Type USE to use an item from the inventory.\n";
    rules += "6. Use EQUIP to equip an item from the inventory.\n";
    rules += "7. Use RULES to view these rules again.\n";
    rules += "8. Gather equipment and food for survival.\n";
    rules += "9. Defeat bosses to progress.\n";
    rules += "10. Explore the world and interact with NPCs to receive quests.\n";
    rules += "11. Reach the land of Scrum to rescue Gapplin and defeat Vallonious.\n";

    //Stats affected by items
    rules += "\nStats affected by items:\n";
    rules += "Weapons affect the player's attack.\n";
    rules += "Hats increase the player's max health.\n";
    rules += "Robes increase the player's evasiveness when attempting to flee from battle.\n";
    rules += "Healing items will be available around the map which can be used to restore your HP.\n";

    cout << rules << endl; // Print the rules to the console
    return rules; // Return the rules as a string
}

string UserInterface::DisplayIntroMessage()
{
    introMessage = "Backstory:\n";
    introMessage += "You are a wizard in The World of Retrospecta.\n";
    introMessage += "While having a picnic with your pet Gapplin, the dragon wizard Vallonious swoops in and steals Gapplin.\n";
    introMessage += "Now, you must travel to the land of Scrum, gather the right equipment, and defeat Vallonious to rescue Gapplin.\n";

    cout << introMessage << endl; // Print the backstory to the console
    return introMessage; // i watn the backstory to come back to me as a string
}

