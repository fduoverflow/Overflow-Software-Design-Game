#include <iostream>
#include <cstdlib>
#include "ConsoleColors.h"
#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"
#include "Item.h"
#include "Inventory.h"

using namespace std;


int main() {

	//Initialize player and inventory
	Player myPlayer("link", 20, 5, 4);
	Inventory inventory(25);

	//Initialize UI
	UserInterface myUI;

	// Creates the Game Manager object that will handle all game logic
	GameManager manager(&myPlayer);

	// Initialize first world
	manager.SetNewWorld();

	/*
	// Intilalize the Mushroom Warrior Enemy -- we can move all NPC / enemy implementions to it's own classes if needed
	
	worldMap.GetChunkAt(1, 1).GetTileAt(9, 11).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3));
	worldMap.GetChunkAt(1, 1).GetTileAt(7, 11).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3));

	// Intilalize the Wizard Squirrel Enemy
	worldMap.GetChunkAt(1, 1).GetTileAt(9, 12).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Leaf Sword", { L"🗡️", 3 }, "Sword that does does 3 damage.", Item::Type::WEAPON, 5, 1), "Nut Throw", 2, ""));

	*/
	//Set game loop variables
	bool isGameOver = false;
	string moveInput;

	//Display current chunk once before entering play loop
	manager.Display();

	//Display rules and story.
	myUI.DisplayIntroMessage();
	myUI.DisplayRules();

	while (!isGameOver) {
		
		//Display NPC if there is one on Tile
		if (manager.GetPlayerLocationTile().GetNPC() != nullptr)
		{
			cout << "\nThere is an NPC here: " + manager.GetPlayerLocationTile().GetNPC()->GetName();
			cout << "\nType Talk to speak to them.";
		}

		
		//Display Enemy if there is one on Tile. When battle system is implemented, it will launch from here.
		if (manager.GetPlayerLocationTile().GetEnemy() != nullptr)
		{
			cout << "\nYou have encountered an enemy! The enemy here is: " + manager.GetPlayerLocationTile().GetEnemy()->GetName();
			cout << "\nEnemy Description:" << manager.GetPlayerLocationTile().GetEnemy()->GetEnemyDescription() << "\n";
			cout << "\nGet ready to battle!\n\n";

			// Call the GameBattleManager to handle the battle that is happening
			// GameBattleManager is a method of the GameManager class
			manager.GameBattleManager(myPlayer);
		}

		//Display item if there is one on Tile
		if (manager.GetPlayerLocationTile().GetItem() != nullptr)
		{
			Item *i = manager.GetPlayerLocationTile().GetItem();
			// Checks if the player is at a teleporter
			if (i->GetType() == Item::Type::TELEPORTER) {
				cout << i->GetDescription() << endl;
				cout << "Type Enter to advance." << endl;
			}
			else {
				cout << "\nThere is an item here: " + manager.GetPlayerLocationTile().GetItem()->GetName();
				cout << "\nType PickUp to pick up item.";
				cout << "\nType Inspect to look at item description.";
			}
		}

		//End game if player dies
		if (myPlayer.GetPlayerHealth() <= 0) {
			cout << "You have died. Better luck next time!" << endl;
			return 0;
		}

		//Display player location info
		cout << "\nChunk X: " << myPlayer.GetPlayerChunkLocationX();
		cout << "\nChunk Y: " << myPlayer.GetPlayerChunkLocationY();
		cout << "\nRow: " << myPlayer.GetPlayerLocationY();
		cout << "\nCol: " << myPlayer.GetPlayerLocationX();
		cout << "\nEnter command: ";
		cin >> moveInput;

		// Clears the console screen
		system("cls");

		//Display current chunk
		manager.Display();

		//User Input Validation
		UserInputValidation valid;

		// Checking if input is a movement or action
		bool isAction = valid.ActionChecker(moveInput);
		bool isMove = valid.MoveChecker(moveInput);

		//Process Player Move and Player Action separately
		if (isAction && !isMove)
		{
			switch (valid.GetPlayerAction())
			{
				case UserInputValidation::Action::TALK:
					if (manager.GetPlayerLocationTile().GetNPC() != nullptr)		//Check if NPC is on Tile
					{
						manager.GetPlayerLocationTile().GetNPC()->Talk();
						
						//Initialize first quest if NPC is Scummius and check to make sure Player can not restart same quest.
						if (manager.GetPlayerLocationTile().GetNPC()->GetName() == "Scrummius" && manager.GetFirstQuest()->GetQuestStart() != true && manager.GetFirstQuest()->GetQuestComplete() != true)
						{
							manager.InitilizeTutorialQuest();
						}

						//Check if NPC is Three Stones and if puzzle is not complete then start the puzzle. Also checks to make sure player has already completed the first quest.
						if (manager.GetPlayerLocationTile().GetNPC()->GetName() == "Three Stones" && manager.GetThreeStonesQuest()->GetQuestComplete() != true && manager.GetFirstQuest()->GetQuestComplete() == true)
						{
							cout << "\nType LEAVE to exit puzzle.\n";

							if (manager.ThreeStonesPuzzle())					//Starts puzzle and returns true or false if player solves or leaves puzzle
							{
								manager.GetPlayerLocationTile().GetNPC()->SetDialogue("The Three Stones Puzzle has been completed. You are free to cross the river.");
							}
						}

						//Check if NPC is Hero's Tree and if puzzle is not complete then start the puzzle.
						if (manager.GetPlayerLocationTile().GetNPC()->GetName() == "Hero's Tree" && manager.GetBranchesQuest()->GetQuestComplete() != true)
						{
							cout << "\nType LEAVE to exit puzzle.\n";

							if (manager.BranchesOfHerosPuzzle())					//Starts puzzle and returns true or false if player solves or leaves puzzle
							{
								manager.GetPlayerLocationTile().GetNPC()->SetDialogue("Congrats on completing the Branches of Heroes! Thine next destination should be further to the east.");
							}
						}
					}
					break;
				case UserInputValidation::Action::PICKUP:
					if (manager.GetPlayerLocationTile().GetItem() != nullptr)		//Check if item is on Tile
					{
						if (manager.GetPlayerLocationTile().GetItem()->GetName() == "Scrummius' Spell Book") // KEY item for First Quest-- flag trigger for completion of first quest
						{
							// Marking First Quest as Complete and spawn in Dust Golem on tiles that correspond to the door tiles (7,7) and (7,8)
							manager.TutorialQuestComplete();
							cout << "You hear a gust of wind coming from the doorway...\n";

						}
						inventory.addItem(manager.GetPlayerLocationTile().PickUpItem()); //Adds the picked up item to the invetory
						cout << "Item was picked up.\n";
					}
					else
					{
						cout << "No item to pick up.\n";
					}
					break;
				case UserInputValidation::Action::INSPECT:
					if (manager.GetPlayerLocationTile().GetItem() != nullptr)		//Check if item is on Tile
					{
						cout << "Item description: " + manager.GetPlayerLocationTile().GetItem()->GetDescription() + "\n";
					}
					else
					{
						cout << "No item to inspect.\n";
					}
					break;
				case UserInputValidation::Action::MAP:
					manager.DisplayMap();
					break;
				case UserInputValidation::Action::HEALTH:
					cout << "You are at " << myPlayer.GetPlayerHealth() << " health.";
					break;
				case UserInputValidation::Action::INV:
					inventory.displayInventory();
					break;
				case UserInputValidation::Action::ENTER:
					if (manager.GetPlayerLocationTile().GetItem() != nullptr && manager.GetPlayerLocationTile().GetItem()->GetType() == Item::Type::TELEPORTER)
						// Creates the new world in here for now, and brings the player to it
					{
						manager.SetNewWorld();
						system("cls");
						manager.Display();
					}
					else
						cout << "There is nothing to enter.\n";
					break;
				case UserInputValidation::Action::RULES:
					myUI.DisplayRules();
					break;
			}
		}
		else if (!isAction && isMove)
		{
			//Move player
			manager.MovePlayer(valid.GetPlayerMove());

			// Clears the console screen
			system("cls");

			//Display current chunk
			manager.Display();
		}
		else if (!isAction && !isMove)							//Moved action error messages here because they were printing when the other action was used. Ex: "Invalid action" printed when inputing WASD.
		{
			cout << "Invalid Input! Please enter WASD or a valid action!\n";
		}
	}
}