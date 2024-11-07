#include "GameManager.h"

//Constructors.
GameManager::GameManager() 
{
	firstQuest = new Quest();
}

GameManager::GameManager(Player* p, Map* m) {
	myPlayer = p;
	map = m;
	firstQuest = new Quest();
}

/*
* Move player to adjacent Tile in given direction.
*/
void GameManager::MovePlayer(UserInputValidation::Move dir) {
	int x = 0, y = 0;	// Transposition magnitude per direction
	switch (dir)
	{
	case UserInputValidation::Move::W:
		y--;
		break;
	case UserInputValidation::Move::S:
		y++;
		break;
	case UserInputValidation::Move::D:
		x++;
		break;
	case UserInputValidation::Move::A:
		x--;
		break;
	}
	int posX = myPlayer->GetPlayerLocationX(), posY = myPlayer->GetPlayerLocationY();

	// Check where the player would be if they moved to the new location, and if that location would be valid
	int newPosX = posX + x, newPosY = posY + y;
	int newChunkX = myPlayer->GetPlayerChunkLocationX() + x, newChunkY = myPlayer->GetPlayerChunkLocationY() + y;
	// If new move is within the chunk bounds, check that the new tile is valid and move there
	if (-1 < newPosX && newPosX < 16 && -1 < newPosY && newPosY < 16) {
		// Update the tile that the player is on
		myPlayer->SetPlayerLocation(newPosX, newPosY);
	}
	// If new move is not within chunk bounds
	else if (newChunkX > -1 && newChunkY > -1 && newChunkX < map->GetNumColumns() && newChunkY < map->GetNumRows() && map->GetChunkAt(newChunkX, newChunkY).getType() == VALID) {
		myPlayer->SetPlayerChunkLocation(newChunkX, newChunkY);
		myPlayer->SetPlayerLocation((newPosX % 16 + 16) % 16, (newPosY % 16 + 16) % 16);
	}
	else
		cout << "sorry pookie can't move here :(";
}

/*
* Returns Tile object at current player location.
*/
Tile& GameManager::GetPlayerLocationTile()
{
	return map->GetChunkAt(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY()).GetTileAt(myPlayer->GetPlayerLocationX(), myPlayer->GetPlayerLocationY());
}

/*
* Initializes first quest by updating start bool and providing quest components.
*/
void GameManager::InitilizeTutorialQuest()
{
	//Setting the first quest to start as true -- Talking to Scrummius will trigger this
	firstQuest->SetQuestStart(true);

	// Tutorial Quest Name, Description, and Overall Objective
	string name = "Tutorial Quest- Retrieve the Spellbook from the house!";
	string desc = "Before you can set off on your quest, you must retrieve back your spellbook so you may harness your magic powers once again!";
	string objective = "Go to the house and gather the spellbook!";

	// Spell book is a key item that is gathered after the first quest-- not a weapon for now
	spellBook = new Item("Scrummius' Spell Book","A certain peculiar owl's spellbook, who knows what secrets it may hold...",Item::Type::KEY, 0);
	firstQuest = new Quest(name, desc, objective, spellBook);

	// Place the spellbook in location -- door: (7,7) and (7,8)
	// Spell book is in chunk (0,1) and tile (4,4)
	map->GetChunkAt(0, 1).GetTileAt(4,4).SetItem(spellBook);
}

/*
* Update fist quest flags to complete status and update NPC dialogue.
*/
void GameManager::TutorialQuestComplete()
{
	//String to hold large npc dialogue. May move to somewhere else later.
	string scrummiusDialogue = 
		"That was fast. I bet yooou just wanted that book for yourself. Either way, now yooou must get to the city if you want tooo make it to Lord Vallonious� lair. Like that�s gonna happen. First, get throoough the forest by heading east. It will lead yooou straight there!";
	
	//Mark first quest as done
	firstQuest->SetQuestStart(false);
	firstQuest->SetQuestComplete(true);

	//Update npc dialgue
	map->GetChunkAt(1,1).GetTileAt(15,12).GetNPC()->SetDialogue(scrummiusDialogue);

	//Spawn Enemy that takes up two tiles. Use this method to generate enemies that can occupy multiple tiles.
	map->GetChunkAt(0, 1).GetTileAt(7, 7).SetEnemy(new Enemy("Dust Golem", 2, new Item("Potion", "Use this potion to restore your HP", Item::Type::HEALING, 5)));
	map->GetChunkAt(0, 1).GetTileAt(7, 8).SetEnemy(map->GetChunkAt(0, 1).GetTileAt(7, 7).GetEnemy());
}

//First Quest getters and setters
Quest* GameManager::GetFirstQuest()
{
	return firstQuest;
}
void GameManager::SetFirstQuest(Quest* newQuest)
{
	firstQuest = newQuest;
}

void GameManager::Display() {
	map->Display(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY(), myPlayer->GetPlayerLocationX(), myPlayer->GetPlayerLocationY());
}

/*
This function will manage how battles will work and will be called in Game.cpp when a battle starts
3 player actions: ATTACK, DEFLECT, RUN
Enemy actions: ATTACK and DEFLECT
*/
void GameManager::GameBattleManager(GameManager manager, Player myPlayer)
{
	// if the player chooses run and run succeeds, it should stop the battle, but not get rid of the enemy
	bool isActionRun = false;
	while (manager.GetPlayerLocationTile().GetEnemy() != nullptr && manager.GetPlayerLocationTile().GetEnemy()->GetHealth() > 0 && isActionRun == false)
	{
		// Player turn
		string battleAction;
		cout << "Enter Attack, Deflect, or Run for your action: ";
		cin >> battleAction;
		UserInputValidation checker;
		bool validAction = checker.ActionChecker(battleAction);

		if (validAction)
		{
			int playerAttackDamage = myPlayer.GetPlayerAttackDamage();
			switch (checker.GetPlayerAction())
			{
			// Player chooses the ATTACK Action and will do damage to the enemy			
			case UserInputValidation::Action::ATTACK:
																																								  
				manager.GetPlayerLocationTile().GetEnemy()->SetHealth(manager.GetPlayerLocationTile().GetEnemy()->GetHealth() - playerAttackDamage);
				cout << "Enemy Health: " << manager.GetPlayerLocationTile().GetEnemy()->GetHealth() << "\n";

				// Occurs when the enemy is defeated by reaching 0 or less health
				if (manager.GetPlayerLocationTile().GetEnemy()->GetHealth() <= 0)
				{
					cout << manager.GetPlayerLocationTile().GetEnemy()->GetName() << " has been defeated!\n";
					delete manager.GetPlayerLocationTile().GetEnemy();	//Delete Enemy object so that other pointers no longer reference it.					  
					manager.GetPlayerLocationTile().SetEnemy(nullptr);
					break;
				}
				break;
			case UserInputValidation::Action::DEFLECT:

				break;
			case UserInputValidation::Action::RUN:

				// Providing a seed value
				srand((unsigned)time(NULL));

				// Get a random number from 1 to 10
				int runChance = 1 + (rand() % 9);
				if (runChance <= 5)
				{
					cout << "You ran away safely, but the " << manager.GetPlayerLocationTile().GetEnemy()->GetName() << " still remains...\n";
					isActionRun = true;
				}
				break;
			}
		}


		// Enemy turn, then begin loop again																																							  
	}
}

