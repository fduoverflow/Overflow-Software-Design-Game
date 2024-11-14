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


const int STARTING_AREA_NUM_ROWS = 5;
const int STARTING_AREA_NUM_COLS = 6;

int main() {
	//Initialize map
	Map worldMap("startingAreaMap.txt", STARTING_AREA_NUM_ROWS, STARTING_AREA_NUM_COLS);

	//Initialize player and inventory
	Player myPlayer("link", 20, 5, 4);
	myPlayer.SetPlayerChunkLocation(1, 1);
	Inventory inventory(25);

	//Initialize UI
	UserInterface myUI;

	//Strings to hold large npc dialogue. May move to somewhere else later.
	string scrummiusDialogue = "Hellooo! My name is Scrummius the Owl, and I am quite pleased to meet yooou! What is your name?\nYooou said your name is " + myPlayer.GetPlayerName() +
		" and Lord Vallonious has taken your pet, Gapplin? I don't believe you. But if I did I would say yooou are going to need a spell book if you are going tooo face him. Head west from your house and enter the old chateau. I believe yooou may find what you're looking for in there... liar.";
	string herosTreeDialogue = "Greetings. I am the Hero's Tree. Thou must pass the Branches of Heroes to continue your adventure. These branches have chronicled the tales of these lands and to clear them, you must answer their three questions.";
	string threeStonesDialogue = "The river seems to be uncrossable at the current moment...";

	// Creates the Game Manager object that will handle all game logic
	GameManager manager(&myPlayer, &worldMap);

	//Place items near player's starting tile
	//worldMap.GetChunkAt(0, 0).GetTileAt(5, 4).SetItem(new Item("Apple", "This Apple will heal 10 HP when used.", Item::Type::HEALING, 10));
	worldMap.GetChunkAt(1, 1).GetTileAt(6, 5).SetItem(new Item("Key", { L"🗝️", 3 }, "This key might unlock a door somewhere.", Item::Type::KEY, 0,1));
	worldMap.GetChunkAt(1, 1).GetTileAt(4, 5).SetItem(new Item("Ring", { L"💍", 3 }, "This Ring can be equipped to increase your magic power.", Item::Type::EQUIPMENT, 5,1));
	worldMap.GetChunkAt(1, 1).GetTileAt(6, 6).SetItem(new Item("Key", { L"🗝️", 3 }, "This key might unlock a door somewhere.", Item::Type::KEY, 0,1));
	worldMap.GetChunkAt(1, 1).GetTileAt(5, 6).SetItem(new Item("Wand", { L"🪄", 3 }, "This Wand can be used as a weapon against your enemies.", Item::Type::WEAPON, 25,1));

	//Initialize first NPC Scrummius 3 tiles north of where the player starts. Placement is temporary until map gets further implementation.
	worldMap.GetChunkAt(1, 1).GetTileAt(1, 7).SetNPC(new NPC("Scrummius", {L"🦉", 3}, scrummiusDialogue));

	//Initialize 3 Stones NPC to offer the 3 Stepping Stone Questions puzzle.
	worldMap.GetChunkAt(3, 1).GetTileAt(2, 6).SetNPC(new NPC("Three Stones", { L"🪨", 3 }, threeStonesDialogue));

	//Initialize Hero's Tree NPC to offer the Branches of Heroes puzzle.
	worldMap.GetChunkAt(5, 3).GetTileAt(6, 8).SetNPC(new NPC("Hero's Tree", { L"🌲", 3 }, herosTreeDialogue));

	// Intilalize the Mushroom Warrior Enemy -- we can move all NPC / enemy implementions to it's own classes if needed
	
	worldMap.GetChunkAt(1, 1).GetTileAt(9, 11).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3));
	//worldMap.GetChunkAt(1, 1).GetTileAt(9, 16).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3));


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
			cout << "\nThere is an item here: " + manager.GetPlayerLocationTile().GetItem()->GetName();
			cout << "\nType PickUp to pick up item.";
			cout << "\nType Inspect to look at item description.";
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