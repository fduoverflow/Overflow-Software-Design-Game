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
	spellBook = new Item("Scrummius' Spell Book", { L"📖", 3 }, "A certain peculiar owl's spellbook, who knows what secrets it may hold...", Item::Type::KEY, 0);
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
		"That was fast. I bet yooou just wanted that book for yourself. Either way, now yooou must get to the city if you want tooo make it to Lord Vallonious‘ lair. Like that’s gonna happen. First, get throoough the forest by heading east. It will lead yooou straight there!";
	
	//Mark first quest as done
	firstQuest->SetQuestStart(false);
	firstQuest->SetQuestComplete(true);

	//Update npc dialgue
	map->GetChunkAt(1,1).GetTileAt(15,12).GetNPC()->SetDialogue(scrummiusDialogue);

	//Spawn Enemy that takes up two tiles. Use this method to generate enemies that can occupy multiple tiles.
	// Setting the Dust Golem
	// Dust Golem has 8 HP, drops a potion, it's attack name is Arm Swing and that attack does 2 HP
	map->GetChunkAt(0, 1).GetTileAt(7, 7).SetEnemy(new Enemy("Dust Golem", 8, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5),"Arm Swing",2));
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
void GameManager::GameBattleManager(Player &myPlayer)
{
	// if the player chooses run and run succeeds, it should stop the battle, but not get rid of the enemy
	bool isActionRun = false;
	while (GetPlayerLocationTile().GetEnemy() != nullptr && GetPlayerLocationTile().GetEnemy()->GetHealth() > 0 && isActionRun == false)
	{
		// Player turn
		// Asking for user input for their action
		string battleAction;
		cout << "Enter Attack, Deflect, or Run for your action: ";
		cin >> battleAction;

		cout << endl;

		// Check if the input is a valid action
		UserInputValidation playerChecker;
		bool validAction = playerChecker.ActionChecker(battleAction);

		// Get the player and enemy name
		string enemyName = GetPlayerLocationTile().GetEnemy()->GetName();
		string playerName = myPlayer.GetPlayerName();

		// Get enemy Health
		int startEnemyHealth = GetPlayerLocationTile().GetEnemy()->GetHealth();
		int currentEnemyHealth = startEnemyHealth;

		// Get player name and attack damage
		int playerAttackDamage = myPlayer.GetPlayerAttackDamage();
		string playerAttackName = myPlayer.GetPlayerAttack();

		// Get enemy attack and attack damage
		string enemyAttackName = GetPlayerLocationTile().GetEnemy()->GetEnemyAttack();
		int enemyAttackDamage = GetPlayerLocationTile().GetEnemy()->GetEnemyAttackDamage();
		int currentPlayerHealth = myPlayer.GetPlayerHealth();

		// Get a random number from 1 to 10
		srand((unsigned)time(nullptr)); // seed value
		int runChance = 1 + (rand() % 9);

		// If the player chose a valid action, process their action
		if (validAction)
		{
			switch (playerChecker.GetPlayerAction())
			{
			
			// Player chooses the ATTACK Action and will do damage to the enemy			
			case UserInputValidation::Action::ATTACK:
													
				cout << playerName << " uses " << playerAttackName << " and deals " << playerAttackDamage << " HP!\n";
				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - playerAttackDamage);

				currentEnemyHealth = GetPlayerLocationTile().GetEnemy()->GetHealth();
				cout << enemyName << " Health: " << currentEnemyHealth << "\n\n";
				break;
			case UserInputValidation::Action::DEFLECT:
				cout << playerName << " deflects!\n";
				myPlayer.SetPlayerHealth(currentPlayerHealth - (enemyAttackDamage / 2));
				currentPlayerHealth = myPlayer.GetPlayerHealth();

				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - (enemyAttackDamage / 2));
				currentEnemyHealth = GetPlayerLocationTile().GetEnemy()->GetHealth();

				cout << enemyName << " Health: " << currentEnemyHealth << "\n";
				cout << playerName << " Health: " << currentPlayerHealth << "\n\n";
				break;
			case UserInputValidation::Action::RUN:
				
				
				if (runChance <= 5)
				{
					cout << "You ran away safely, but the " << GetPlayerLocationTile().GetEnemy()->GetName() << " still remains...\n";
					isActionRun = true;
				}
				else
				{
					cout << "You were not able to run away...\n";
				}
				break;
			}		
		}
		else
		{
			// player must enter a valid action, or their turn is lost
			cout << "Oops, you entered a wrong command. You lost your turn...\n\n";
		}
		// Occurs when the enemy is defeated by reaching 0 or less health
		if (GetPlayerLocationTile().GetEnemy()->GetHealth() <= 0)
		{
			cout << enemyName << " has been defeated!\n";
			delete GetPlayerLocationTile().GetEnemy();	//Delete Enemy object so that other pointers no longer reference it.					  
			GetPlayerLocationTile().SetEnemy(nullptr);
			return;
		}

		// Get the enemy action
		UserInputValidation::Action enemyTurn = ProcessEnemyTurn(currentEnemyHealth, startEnemyHealth);

		// Enemy actions limited to ATTACK and DEFLECT-- updating the health accordingly
		switch (enemyTurn)
		{
			case UserInputValidation::Action::ATTACK:
				cout << enemyName << " uses " << enemyAttackName << " and deals " << enemyAttackDamage << " HP!\n";

				myPlayer.SetPlayerHealth(currentPlayerHealth - enemyAttackDamage);
				currentPlayerHealth = myPlayer.GetPlayerHealth();

				cout << playerName << " Health: " << currentPlayerHealth << "\n\n";
				break;
			case UserInputValidation::Action::DEFLECT:
				cout << enemyName << " deflects!\n";

				myPlayer.SetPlayerHealth(currentPlayerHealth - (playerAttackDamage / 2));
				currentPlayerHealth = myPlayer.GetPlayerHealth();

				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - (playerAttackDamage / 2));
				currentEnemyHealth = GetPlayerLocationTile().GetEnemy()->GetHealth();

				cout << enemyName << " Health: " << currentEnemyHealth << "\n";
				cout << playerName << " Health: " << currentPlayerHealth << "\n\n";
				break;
			default:
				break;
		}
	}
}

/*
This method will process the enemies turn
It is called in the GameBattleManager method to process the enemy's turn
return the proper enemy action based on the ratios highlighted
*/
UserInputValidation::Action GameManager::ProcessEnemyTurn(int currentEnemyHealth, int startEnemyhealth)
{
	/*
	If enemy health is between 100% - 75%: Attack chance is 95%, Deflect Chance is 5%
	If enemy health is between 75% - 50%: Attack chance is 70%, Deflect Chance is 30%
	If enemy health is between 50% - 25%: Attack chance is 60%, Deflect Chance is 50%
	If enemy health is between 25% - 0%: Attack chance is 50%, Deflect chance is 50%
	*/
	double healthPercentage = currentEnemyHealth / startEnemyhealth;

	int attackChance = 50;  // Default chance in case of error
	int deflectChance = 50; // Default chance in case of error

	// RNG for enemy action -- based on enemy health percentage
	srand((unsigned)time(nullptr));
	int randomEnemyAction = 1 + (rand() % 100);

	// Map health percentage to categories and set attack/deflect chances
	if (healthPercentage >= 0.75) {
		attackChance = 95;
		deflectChance = 5;
	}
	else if (healthPercentage >= 0.5) {
		attackChance = 70;
		deflectChance = 30;
	}
	else if (healthPercentage >= 0.25) {
		attackChance = 60;
		deflectChance = 40;
	}
	else {
		attackChance = 50;
		deflectChance = 50;
	}

	// Return enemy action based on attack and deflect chances
	if (randomEnemyAction <= attackChance) {
		return UserInputValidation::Action::ATTACK;
	}
	else 
	{
		return UserInputValidation::Action::DEFLECT;
	}
}

/*
* Display Map.
* Only displays VALID Chunks.
*/
void GameManager::DisplayMap()
{
	map->DisplayMap(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY(), myPlayer->GetPlayerIcon());
}
