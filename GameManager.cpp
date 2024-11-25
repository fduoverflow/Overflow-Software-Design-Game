#include "GameManager.h"
#include <algorithm>
#include <regex>

using namespace std;

/*
* Default constructor
*/
GameManager::GameManager() 
{
	//Initialize quests
	firstQuest = new Quest();
	branchesOfHeroesQuest = new Quest("Branches of Heroes", "Three roots block your path and you must pass them by answering their questions.", "Answer the 3 questions.", nullptr);
	threeStonesQuest = new Quest("Three Stones", "The 3 stones of Agile can now guide you on your path to safely cross. You must answer their 3 questions to cross safely.", "Answer the 3 questions.", nullptr);
	captainQuest = new Quest("Ship Captain", "", "", nullptr);
	//Initialize tutorial battle checker
	isFirstBattleDone = false;
}
/*
* Constructor with passed player and map.
*/
GameManager::GameManager(Player* p, Map* m) 
{
	//Pass player and map
	myPlayer = p;
	map = m;

	//Initialize quests
	firstQuest = new Quest();
	branchesOfHeroesQuest = new Quest("Branches of Heroes", "Three roots block your path and you must pass them by answering their questions.", "Answer the 3 questions.", nullptr);
	threeStonesQuest = new Quest("Three Stones", "The 3 stones of Agile can now guide you on your path to safely cross. You must answer their 3 questions to cross safely.", "Answer the 3 questions.", nullptr);
	captainQuest = new Quest("Ship Captain", "", "", nullptr);
	//Initialize tutorial battle checker
	isFirstBattleDone = false;
}

// Moves to the next work, thus changing the map
void GameManager::MoveToWorld(Map* m, int cX, int cY, int tX, int tY) {
	map = m;
	myPlayer->SetPlayerChunkLocation(cX, cY);
	myPlayer->SetPlayerLocation(tX, tY);
}
Map* GameManager::GetMap()
{
	return map;
}

/*
* Display map and anything within it.
*/
void GameManager::Display() {
	map->Display(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY(), myPlayer->GetPlayerLocationX(), myPlayer->GetPlayerLocationY());
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
	int chunkX = myPlayer->GetPlayerChunkLocationX(), chunkY = myPlayer->GetPlayerChunkLocationY();

	// Check where the player would be if they moved to the new location, and if that location would be valid
	int newPosX = posX + x, newPosY = posY + y;
	int newChunkX = chunkX + x, newChunkY = chunkY + y;
	// If new move is within the chunk bounds, check that the new tile is valid and move there
	if (-1 < newPosX && newPosX < 16 && -1 < newPosY && newPosY < 16) {
		if (!WillCollide(chunkX, chunkY, newPosX, newPosY))
			// Update the tile that the player is on
			myPlayer->SetPlayerLocation(newPosX, newPosY);
	}
	// If new move is not within chunk bounds
	else if (newChunkX > -1 && newChunkY > -1 && newChunkX < map->GetNumColumns() && newChunkY < map->GetNumRows() && map->GetChunkAt(newChunkX, newChunkY).getType() == VALID) {
		newPosX = (newPosX % 16 + 16) % 16, newPosY = (newPosY % 16 + 16) % 16;
		if (!WillCollide(newChunkX, newChunkY, newPosX, newPosY)) {
			myPlayer->SetPlayerChunkLocation(newChunkX, newChunkY);
			myPlayer->SetPlayerLocation(newPosX, newPosY);
		}
	}
	else
		cout << "sorry pookie can't move here :(";
}

// Checks whether of not the new player position is collidable
bool GameManager::WillCollide(int cX, int cY, int pX, int pY) {
	return BLOCK_TYPES[map->GetChunkAt(cX, cY).GetTileAt(pX, pY).GetID()].collides;
}

/*
* Returns Tile object at current player location.
*/
Tile& GameManager::GetPlayerLocationTile()
{
	return map->GetChunkAt(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY()).GetTileAt(myPlayer->GetPlayerLocationX(), myPlayer->GetPlayerLocationY());
}

/*
* Returns Chunk object at current player location.
*/
Chunk& GameManager::GetPlayerLocationChunk()
{
	return map->GetChunkAt(myPlayer->GetPlayerChunkLocationX(), myPlayer->GetPlayerChunkLocationY());
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
	spellBook = new Item("Scrummius' Spell Book", { L"📖", 3 }, "A certain peculiar owl's spellbook, who knows what secrets it may hold...", Item::Type::KEY, 0,1);
	firstQuest = new Quest(name, desc, objective, spellBook);

	// Place the spellbook in location -- door: (7,7) and (7,8)
	// Spell book is in chunk (0,1) and tile (4,4)
	map->GetChunkAt(0, 1).GetTileAt(4,4).SetItem(spellBook);

	// Sets the doors to be unlocked in the house by changing the tile ID
	map->GetChunkAt(0, 1).GetTileAt(7, 7).SetID(3);
	map->GetChunkAt(0, 1).GetTileAt(7, 8).SetID(3);
}

/*
* Update fist quest flags to complete status and update NPC dialogue.
*/
void GameManager::TutorialQuestComplete()
{
	//String to hold large npc dialogue. May move to somewhere else later.
	string scrummiusDialogue = 
		"That was fast. I bet yooou just wanted that book for yourself. Either way, now yooou must get to the city if you want tooo make it to Lord Vallonious' lair. Like that's gonna happen. First, get throoough the forest by heading east. It will lead yooou straight there!";
	
	//Mark first quest as done
	firstQuest->SetQuestStart(false);
	firstQuest->SetQuestComplete(true);

	//Update npc dialgue
	map->GetChunkAt(1,1).GetTileAt(1,7).GetNPC()->SetDialogue(scrummiusDialogue);

	//Spawn Enemy that takes up two tiles. Use this method to generate enemies that can occupy multiple tiles.
	// Setting the Dust Golem
	// Dust Golem has 8 HP, drops a potion, it's attack name is Arm Swing and that attack does 2 HP
	string dustGolemDesc = "A small golem powered by magic. It gathers the dust around him to attack!";
	map->GetChunkAt(0, 1).GetTileAt(7, 7).SetEnemy(new Enemy("Dust Golem", { L"🗿", 3 }, 8, new Item("Potion", {L"🧋", 3}, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Arm Swing", 2, dustGolemDesc));
	map->GetChunkAt(0, 1).GetTileAt(7, 8).SetEnemy(map->GetChunkAt(0, 1).GetTileAt(7, 7).GetEnemy());

	//Update dialogue for Three Stones NPC
	map->GetChunkAt(3, 1).GetTileAt(2, 6).GetNPC()->SetDialogue("You thought the River to be uncrossable, but the 3 stones of Agile can now guide you on your path to safely cross.You must however answer their 3 questions to cross safely");
}

//First Quest getter
Quest* GameManager::GetFirstQuest()
{
	return firstQuest;
}

//Branches of Heros Puzzle Quest getter
Quest* GameManager::GetBranchesQuest()
{
	return branchesOfHeroesQuest;
}

//Three Stones Puzzle Quest getter
Quest* GameManager::GetThreeStonesQuest()
{
	return threeStonesQuest;
}
Quest* GameManager::GetCaptainQuest()
{
	return captainQuest;
}

/*
* Puzzle at the end of the Forest.
* Keeps the player in the puzzle unless LEAVE command is inputted or they have solved the puzzle.
* Returns true if puzzle is solved and false if the player chose to leave.
*/
bool GameManager::BranchesOfHerosPuzzle()
{
	//Control bool, input string, and input validation variable.
	bool isInPuzzle = true;
	string playerAnswer;
	UserInputValidation validator;

	//Reset cin to use std::getLine(). This is to allow for user input that includes spaces.
	cin.ignore();

	//Puzzle loop.
	while (isInPuzzle)
	{
		//Question 1.
		cout << "What is the item Scrummius told thee to gather?\n";
		getline(cin, playerAnswer);

		//Clean input
		NormalizeString(playerAnswer);

		//Check answer.
		if (playerAnswer == "SPELLBOOK" || playerAnswer == "SPELL BOOK")
		{
			cout << "Correct. ";

			//Question 2.
			cout << "What was the first enemy that thou encountered?\n";
			getline(cin, playerAnswer);

			//Clean input
			NormalizeString(playerAnswer);

			//Check answer.
			if (playerAnswer == "DUST GOLEM" || playerAnswer == "DUSTGOLEM")
			{
				cout << "Correct. ";

				//Question 3.
				cout << "How many stepping stones did thou hop on to cross the river?\n";
				getline(cin, playerAnswer);

				//Clean input
				NormalizeString(playerAnswer);

				//Check answer and exit puzzle on right answer.
				if (playerAnswer == "3 STONES" || playerAnswer == "3" || playerAnswer == "THREE STONES" || playerAnswer == "THREE")
				{
					cout << "Correct. Thou has proven thine self. Proceed along thine adventure!\n";
					branchesOfHeroesQuest->SetQuestComplete(true);

					//Add stones to map to allow player to cross the water.
					map->GetChunkAt(5, 3).GetTileAt(7, 8).SetID(2);
					map->GetChunkAt(5, 3).GetTileAt(8, 8).SetID(2);
					map->GetChunkAt(5, 3).GetTileAt(9, 8).SetID(2);

					return true;
				}
			}
		}

		//Check for leave command
		validator.ActionChecker(playerAnswer);
		if (validator.GetPlayerAction() == UserInputValidation::Action::LEAVE)
		{
			return false;
		}
		
		//Wrong answer message.
		cout << "Wrong. Thou must start from the begining. ";
	}
}

/*
* Puzzle at the river crossing.
* Keeps the player in the puzzle unless LEAVE command is inputted or they have solved the puzzle.
* Returns true if puzzle is solved and false if the player chose to leave.
*/
bool GameManager::ThreeStonesPuzzle()
{
	//Control bool, input string, and input validation variable.
	bool isInPuzzle = true;
	string playerAnswer;
	UserInputValidation validator;

	//Reset cin to use std::getLine(). This is to allow for user input that includes spaces.
	cin.ignore();

	//Puzzle loop.
	while (isInPuzzle)
	{
		//Question 1.
		cout << "What is the name of your pet apple?\n";
		getline(cin, playerAnswer);

		//Clean input
		NormalizeString(playerAnswer);

		//Check answer.
		if (playerAnswer == "GAPPLIN" || playerAnswer == "GAPLIN")
		{
			cout << "Correct. ";

			//Question 2.
			cout << "What is the name of the dragon wizard that stole your pet?\n";
			getline(cin, playerAnswer);

			//Clean input
			NormalizeString(playerAnswer);

			//Check answer.
			if (playerAnswer == "VALLONIOUS" || playerAnswer == "VALONIOUS" || playerAnswer == "VALLONIUS" || playerAnswer == "VALONIUS")
			{
				cout << "Correct. ";

				//Question 3.
				cout << "Is this a good game?\n";
				getline(cin, playerAnswer);

				//Clean input
				NormalizeString(playerAnswer);

				//Check answer and exit puzzle on right answer.
				if (playerAnswer == "YES" || playerAnswer == "Y")
				{
					cout << "Correct. Three stepping stones have appeared to allow you to cross the river.\n";
					threeStonesQuest->SetQuestComplete(true);

					//Add stones to map to allow player to cross the river.
					map->GetChunkAt(3, 1).GetTileAt(2, 7).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(2, 8).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(2, 9).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(6, 7).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(6, 8).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(6, 9).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(10, 7).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(10, 8).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(10, 9).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(14, 7).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(14, 8).SetID(2);
					map->GetChunkAt(3, 1).GetTileAt(14, 9).SetID(2);

					return true;
				}
			}
		}

		//Check for leave command
		validator.ActionChecker(playerAnswer);
		if (validator.GetPlayerAction() == UserInputValidation::Action::LEAVE)
		{
			return false;
		}

		//Wrong answer message.
		cout << "YOU FOOL! Now you must answer the questions again...";
	}
}

/*
This function will manage how battles will work and will be called in Game.cpp when a battle starts
3 player actions: ATTACK, DEFLECT, RUN
Enemy actions: ATTACK and DEFLECT
*/
void GameManager::GameBattleManager(Player &myPlayer)
{

	//Check if the battle is the tutorial battle against the dust golem
	if (!isFirstBattleDone && GetPlayerLocationTile().GetEnemy()->GetName() == "Dust Golem")
	{
		cout << "Before the battle begins, you hear Lord Vallonious' voice in your head... FOOL this seems to be your first battle. Let me teach you the basics, so that our final battle may at least be a fair one.\n";
		cout << "If you can not even defeat this simple Dust Golem, you hold no chance to defeat ME!\n\n";
		cout << "You have 3 actions. ATTACK, DEFLECT, and RUN. Attack and Run are self explanatory... unless your feeble mind cannot comprehend these concepts...\n";
		cout << "Deflect works like so: when an attack is deflected, the one who deflected takes half the damage, but so does the attacker.\n";
		cout << "May your future battles be bountiful... I await in the Land of Scrum for our EPIC ENCOUNTER!\n\n";

		//Update checker
		isFirstBattleDone = true;
	}

	// if the player chooses run and run succeeds, it should stop the battle, but not get rid of the enemy
	bool isActionRun = false;
	while (GetPlayerLocationTile().GetEnemy() != nullptr && GetPlayerLocationTile().GetEnemy()->GetHealth() > 0 && isActionRun == false && myPlayer.GetPlayerHealth() > 0)
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

		// Occurs when the enemy is defeated by reaching 0 or less health after player action
		if (GetPlayerLocationTile().GetEnemy()->GetHealth() <= 0)
		{
			//Notify player of enemy defeat
			cout << enemyName << " has been defeated!\n";

			//Drop item if Enemy was holding one
			if (GetPlayerLocationTile().GetEnemy()->GetItem() != nullptr)
			{
				GetPlayerLocationTile().SetItem(GetPlayerLocationTile().GetEnemy()->GetItem());
				cout << "The enemy dropped an item!\n";
			}

			//Heal the player if they just defeated the tutorial enemy, the dust golem.
			if (GetPlayerLocationTile().GetEnemy()->GetName() == "Dust Golem")
			{
				myPlayer.SetPlayerHealth(20);
				cout << "Lord Vallonious pities you, so he has healed you after your battle with the dust golem... he will not be so merciful next time...\n";
				cout << "Player health: " << myPlayer.GetPlayerHealth();
			}

			//Remove Enemy reference pointers to delete Enemy
			GetPlayerLocationChunk().EnemyDefeted(GetPlayerLocationTile().GetEnemy());

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

		// Occurs when the enemy is defeated by reaching 0 or less health after enemy action
		if (GetPlayerLocationTile().GetEnemy()->GetHealth() <= 0)
		{
			cout << enemyName << " has been defeated!\n";

			//Drop item if Enemy was holding one
			if (GetPlayerLocationTile().GetEnemy()->GetItem() != nullptr)
			{
				GetPlayerLocationTile().SetItem(GetPlayerLocationTile().GetEnemy()->GetItem());
				cout << "The enemy dropped an item!";
			}

			
			GetPlayerLocationChunk().EnemyDefeted(GetPlayerLocationTile().GetEnemy());
			return;
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

/*
* Normalize the user input
* remove white space & change to upper case
* modifies the user input string in place
*/
void GameManager::NormalizeString(string& input)
{
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	input = std::regex_replace(input, std::regex("^\\s+|\\s+$"), "");
}

/*
* Use an Item from the passed in Inventory object.
* Assumes Inventory is not empty.
*/
void GameManager::UseItem(Inventory& playerInv)
{
	//Initialize player input string.
	string playerInput;

	//Reset cin to use std::getLine(). This is to allow for user input that includes spaces.
	cin.ignore();

	//Prompt player for which item to use.
	cout << "Type in the name if the item you wish to use: ";
	getline(cin, playerInput);

	//Clean input.
	NormalizeString(playerInput);

	//Grab Item from Inventory.
	Item grabbedItem = playerInv.removeItem(playerInput);

	//Use Item based on type. If Item can't be used, return it to Inventory.
	switch (grabbedItem.GetType())
	{
		case Item::Type::HEALING:
			cout << "You just got healed by: " << grabbedItem.GetValue() << " HP\n";
			myPlayer->HealPlayer(grabbedItem.GetValue());
			break;
		case Item::Type::KEY:
			cout << "You can't use that key item right now. Returning to inventory.\n";
			playerInv.addItem(grabbedItem);
			break;
		case Item::Type::EQUIPMENT:
			cout << "You can't use that equipment item right now. To equip these, use the EQUIP command. Returning to inventory.\n";
			playerInv.addItem(grabbedItem);
			break;
		case Item::Type::WEAPON:
			cout << "You can't use that weapon item right now. To equip these, use the EQUIP command. Returning to inventory.\n";
			playerInv.addItem(grabbedItem);
			break;
		case Item::Type::TELEPORTER:
			cout << "You can't use that teleporter item right now. Returning to inventory.\n";
			playerInv.addItem(grabbedItem);
			break;
		case Item::Type::EMPTY:
			cout << "Wrong item name.\n";
			break;
	}
}

void GameManager::SpawnStartingAreaEnemies(Map worldMap)
{
	// Enemy Descriptions
	string squirrelDesc = "A magical squirrel with powers. You wonder how it passed it's Wizard Schoool exams to get it's wand...";
	string mushroomDesc = "A walking and talking mushroom. It may hold healing attributes, it may be poisonous... only you can be the judge of that!";

	// Wizard Squirrels-- first squirrel drops Leaf Sword
	// Chunk 2,1
	worldMap.GetChunkAt(2, 1).GetTileAt(2, 5).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Leaf Sword", { L"🗡️", 3 }, "Sword that does does 3 damage.", Item::Type::WEAPON, 3, 1), "Nut Throw", 2, squirrelDesc));
	worldMap.GetChunkAt(2, 1).GetTileAt(13, 1).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2,squirrelDesc));
	worldMap.GetChunkAt(2, 1).GetTileAt(13, 11).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Nut Throw", 2, squirrelDesc));

	// Chunk 1,2
	worldMap.GetChunkAt(1, 2).GetTileAt(6, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Nut Throw", 2, squirrelDesc));
	worldMap.GetChunkAt(1, 2).GetTileAt(9, 8).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Rusty Sword", { L"🗡️", 3 }, "Well-worn sword, but it still packs a punch!", Item::Type::WEAPON, 5, 1), "Nut Throw", 2, squirrelDesc));

	// Chunk 3,1
	worldMap.GetChunkAt(3,1).GetTileAt(4, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Rusty Sword", { L"🗡️", 3 }, "Well-worn sword, but it still packs a punch!", Item::Type::WEAPON, 5, 1), "Nut Throw", 2, squirrelDesc));
	worldMap.GetChunkAt(3, 1).GetTileAt(8, 1).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2, squirrelDesc));
	worldMap.GetChunkAt(3,1).GetTileAt(12, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2, squirrelDesc));




	// Mushroom Warriors
	// Chunk 4,2
	worldMap.GetChunkAt(4, 2).GetTileAt(14, 5).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));
	worldMap.GetChunkAt(4, 2).GetTileAt(1, 4).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3, mushroomDesc));
	worldMap.GetChunkAt(4, 2).GetTileAt(13, 8).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3, mushroomDesc));
	worldMap.GetChunkAt(4, 2).GetTileAt(1, 12).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));

	// Chunk 1,2
	worldMap.GetChunkAt(1, 2).GetTileAt(1, 4).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));
	worldMap.GetChunkAt(1, 2).GetTileAt(14, 2).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3, mushroomDesc));


	// Possessed Stumps
	

}
void GameManager::SpawnSprintVilleEnemies(Map worldMap) {

	// Enemy Descriptions
	string pigeonDesc = "A hybrid of pigeon and griffin, this creature combines the ferocity of a predator with the annoyance of a city pest. Approach with caution!";
	string goblinDesc = "A cunning and nimble foe, the Goblin Thief thrives in chaos. Known for its underhanded tactics, it will blind and distract its enemies before darting in for a devastating attack.";

	// Pigeon Griffin Enemies
	// Chunk 1,0
	worldMap.GetChunkAt(1, 1).GetTileAt(7, 6).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Winged Blade", { L"🗡️", 5 }, "A sword made from the sharp wings of the pigeon griffin.", Item::Type::WEAPON, 5, 1), "Sky Peck", 4, pigeonDesc));
	worldMap.GetChunkAt(1, 1).GetTileAt(8, 10).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));

	// Chunk 2,1
	worldMap.GetChunkAt(2, 1).GetTileAt(4, 10).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));
	worldMap.GetChunkAt(2, 1).GetTileAt(8, 14).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));
	worldMap.GetChunkAt(2, 1).GetTileAt(10, 7).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));
	worldMap.GetChunkAt(2, 1).GetTileAt(4, 2).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));

	// Chunk 2,0
	worldMap.GetChunkAt(2, 0).GetTileAt(6, 4).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Winged Blade", { L"🗡️", 5 }, "A sword made from the sharp wings of the pigeon griffin.", Item::Type::WEAPON, 5, 1), "Sky Peck", 4, pigeonDesc));

	// Chunk 3,0
	worldMap.GetChunkAt(3, 0).GetTileAt(1, 5).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));
	worldMap.GetChunkAt(3, 0).GetTileAt(13, 2).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));

	// Goblin Thief Enemies

	// Chunk 3,0
	worldMap.GetChunkAt(3, 0).GetTileAt(4, 9).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Sneaky Slash", 5, goblinDesc));
	worldMap.GetChunkAt(3, 0).GetTileAt(10, 7).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, "Sneaky Slash", 5, goblinDesc));
	worldMap.GetChunkAt(3, 0).GetTileAt(13, 13).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, "Sneaky Slash", 5, goblinDesc));

	// Chunk 4,0
	worldMap.GetChunkAt(4, 0).GetTileAt(2, 13).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Sneaky Slash", 5, goblinDesc));
	worldMap.GetChunkAt(4, 0).GetTileAt(14, 3).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Goblin's Dagger", { L"🗡️", 3 }, "The dagger of a goblin thief.", Item::Type::WEAPON, 8, 1), "Sneaky Slash", 5, goblinDesc));
}

void GameManager::SpawnLandOfScrumEnemies(Map worldMap) {

	// Enemy Descriptions
	string blobDesc = " A malevolent mass of darkness, the Evil Dark Blob lurks in the Land of Scrum, waiting to engulf unwary adventurers.";

	// Puts the enemies in the map. (Change to actual spots once Land of Scrum is incorporated)
	worldMap.GetChunkAt(1, 1).GetTileAt(14, 1).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 40, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 7, blobDesc));
	worldMap.GetChunkAt(1, 1).GetTileAt(14, 2).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 40, "Corrosive Strike", 7, blobDesc));
	worldMap.GetChunkAt(1, 1).GetTileAt(14, 3).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 40, "Corrosive Strike", 7, blobDesc));
}

/*
Quest Makers for the Ship Captain's Quest
Quest start- "thief" steals spellbook
Quest End- talking to ship captain
Story Beat: "Thief" was actually the ship captain, so now player can sail to Land of Scrum free of charge!
*/
void GameManager::InitializeCaptainQuest(Inventory inventory)
{
	captainQuest->SetQuestStart(true);
	// Implementing Spellbook Thief-- bumps into you the second you enter the city
	cout << "A man bumps your shoulder. Bump. You suddenly feel lighter. Your spellbook, it's gone. You throw this thief a glare. His eyes snap back at you and he says...\n";
	cout << "Arg sorry mate I am in a rush. I'll take this for now. Don't delay and be hasteful!\n";
	cout << "You watch the strange man run away. You feel encouraged to chase him down and retrieve the spellbook!\n";
	// Remove the spellbook from the player's inventory
	inventory.removeItem("SCRUMMIUS' SPELL BOOK");
}
bool GameManager::CaptainQuestComplete(Inventory* inventory)
{
	captainQuest->SetQuestStart(false);
	captainQuest->SetQuestComplete(true);
	// Prompting the player that their spellbook is back in the inventory
	cout << "You have completed the Captain's Quest. Your spellbook has been added back to your inventory\n\n";
	inventory->addItem(*spellBook);

	//Prompting the player that they can now go into the land of scrum
	cout << "Now go forth and sail the seas to the Land of Scrum! Who knows what troubles await you on your quest for Gapplin!\n";
	return true;
}
void GameManager::SetSprintVilleNPCs(Map worldMap)
{
	string shipCaptainDialogue = "Ahoy there, matey! Let’s see yer ticket. No ticket, no voyage to the fabled Land o’ Scrum, savvy?\nAye, step aboard if ye’ve got it, but mind ye keep to the code... or the sea'll sort ye out proper!\n Wait a minute... I rememeber you I took your ticket already!\n\n**Pulls out spellbook**\n\n Wait this is not a ticket, this be yer spellbook... My apologies matey. For ye troubles, I will sail ye to the the fabled Land o’ Scrum free o charge!\n\n **The Captain hands you back your spellbook**\n";
	worldMap.GetChunkAt(4, 2).GetTileAt(8, 10).SetNPC(new NPC("Ship Captain", { L"⚓", 3 }, shipCaptainDialogue));
}