#include "GameManager.h"
#include <algorithm>
#include <regex>

using namespace std;

const int NUM_MAPS = 3;
int currentMap = -1;
const string maps[NUM_MAPS] = {"startingAreaMap.txt", "cityMap.txt", "landOfScrumMap.txt"};

struct worldData {
	string fileName;
	int numRows;
	int numColumns;
	int chunkX;
	int chunkY;
	int tileX;
	int tileY;
	int health;
};

// World data for the three game worlds the player traverses
worldData startingArea{ maps[0], 5, 6, 1, 1, 5, 4, 20 };
worldData city{ maps[1], 3, 5, 0, 1, 2, 8, 40 };
worldData landOfScrum{ maps[2], 3, 6, 0, 1, 0, 7, 80 };

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
	ninjaQuest = new Quest("The Old King's Crown", "Find the crown of The Old King", "Go to the city to find the crown.", nullptr);
	//Initialize tutorial battle checker
	isFirstBattleDone = false;
	inventory = nullptr;
	enemiesToDefeat = 0;
}
/*
* Constructor with passed player and map.
*/
GameManager::GameManager(Player* p) 
{
	//Pass player and map
	myPlayer = p;

	//Initialize quests
	firstQuest = new Quest();
	branchesOfHeroesQuest = new Quest("Branches of Heroes", "Three roots block your path and you must pass them by answering their questions.", "Answer the 3 questions.", nullptr);
	threeStonesQuest = new Quest("Three Stones", "The 3 stones of Agile can now guide you on your path to safely cross. You must answer their 3 questions to cross safely.", "Answer the 3 questions.", nullptr);
	captainQuest = new Quest("Ship Captain", "", "", nullptr);
	ninjaQuest = new Quest("The Old King's Crown", "Find the crown of The Old King", "Go to the city to find the crown.", nullptr);
	//Initialize tutorial battle checker
	isFirstBattleDone = false;
	inventory = nullptr;
	enemiesToDefeat = 0;
}
GameManager::GameManager(Player* p, Inventory* i)
{
	//Pass player and map
	myPlayer = p;

	//Initialize quests
	firstQuest = new Quest();
	branchesOfHeroesQuest = new Quest("Branches of Heroes", "Three roots block your path and you must pass them by answering their questions.", "Answer the 3 questions.", nullptr);
	threeStonesQuest = new Quest("Three Stones", "The 3 stones of Agile can now guide you on your path to safely cross. You must answer their 3 questions to cross safely.", "Answer the 3 questions.", nullptr);
	captainQuest = new Quest("Ship Captain", "", "", nullptr);
	ninjaQuest = new Quest("The Old King's Crown", "Find the crown of The Old King", "Go to the city to find the crown.", nullptr);
	//Initialize tutorial battle checker
	isFirstBattleDone = false;
	inventory = i;
	enemiesToDefeat = 0;
}
int GameManager::GetCurrentMap()
{
	return currentMap;
}
void GameManager::InitializeStartingAreaWorld() {

	//Initialize map
	map = new Map(maps[0], startingArea.numRows, startingArea.numColumns);

	// Adjust player's position
	myPlayer->SetPlayerChunkLocation(startingArea.chunkX, startingArea.chunkY);
	myPlayer->SetPlayerLocation(startingArea.tileX, startingArea.tileY);

	//Strings to hold large npc dialogue. May move to somewhere else later.
	string scrummiusDialogue = "Hellooo! My name is Scrummius the Owl, and I am quite pleased to meet yooou! What is your name?\nYooou said your name is " + myPlayer->GetPlayerName() +
		" and Lord Vallonious has taken your pet, Gapplin? I don't believe you. But if I did I would say yooou are going to need a spell book if you are going tooo face him. Head west from your house and enter the old chateau. I believe yooou may find what you're looking for in there... liar.";
	string herosTreeDialogue = "Greetings. I am the Hero's Tree. Thou must pass the Branches of Heroes to continue your adventure. These branches have chronicled the tales of these lands and to clear them, you must answer their three questions.";
	string threeStonesDialogue = "The river seems to be uncrossable at the current moment...";
	string ninjaNPCDialogue = "Huh? Who are you? Oh I get it, you're after The Old King's Crown too!";

	//Place items near player's starting 
	/*
	map->GetChunkAt(1, 1).GetTileAt(6, 5).SetItem(new Item("Key", { L"🗝️", 3 }, "This key might unlock a door somewhere.", Item::Type::KEY, 0, 1));
	map->GetChunkAt(1, 1).GetTileAt(4, 5).SetItem(new Item("Ring", { L"💍", 3 }, "This Ring can be equipped to increase your magic power.", Item::Type::EQUIPMENT, 5, 1));
	map->GetChunkAt(1, 1).GetTileAt(6, 6).SetItem(new Item("Key", { L"🗝️", 3 }, "This key might unlock a door somewhere.", Item::Type::KEY, 0, 1));
	map->GetChunkAt(1, 1).GetTileAt(5, 6).SetItem(new Item("Wand", { L"🪄", 3 }, "This Wand can be used as a weapon against your enemies.", Item::Type::WEAPON, 25, 1));
	*/

	// Place teleporter into the city
	map->GetChunkAt(5, 3).GetTileAt(15, 8).SetItem(new Item("Gate", { L"🚪", 3 }, "You're at the city gates; would you like to enter now?", Item::Type::TELEPORTER, 0, 0));


	//Initialize first NPC Scrummius 3 tiles north of where the player starts. Placement is temporary until map gets further implementation.
	map->GetChunkAt(1, 1).GetTileAt(1, 7).SetNPC(new NPC("Scrummius", { L"🦉", 3 }, scrummiusDialogue));

	//Initialize 3 Stones NPC to offer the 3 Stepping Stone Questions puzzle.
	map->GetChunkAt(3, 1).GetTileAt(2, 6).SetNPC(new NPC("Three Stones", { L"🪨", 3 }, threeStonesDialogue));

	//Initialize Hero's Tree NPC to offer the Branches of Heroes puzzle.
	map->GetChunkAt(5, 3).GetTileAt(6, 8).SetNPC(new NPC("Hero's Tree", { L"🌲", 3 }, herosTreeDialogue));

	//Initalize Ninja NPC for their quest line.
	map->GetChunkAt(1, 3).GetTileAt(7, 12).SetNPC(new NPC("Ninja", { L"🥷", 3 }, ninjaNPCDialogue));


	//SpawnStartingAreaEnemies();
	//Initialize starting area items
	SpawnStartingAreaItems();
}

void GameManager::InitializeCityWorld() {
	//Initialize map
	map = new Map(maps[1], city.numRows, city.numColumns);

	// Adjust player's position
	myPlayer->SetPlayerChunkLocation(city.chunkX, city.chunkY);
	myPlayer->SetPlayerLocation(city.tileX, city.tileY);
	if (myPlayer->GetEquippedHat() != nullptr)
	{
		myPlayer->SetPlayerMaxHealth(40 + myPlayer->GetEquippedHat()->GetValue());
		myPlayer->SetPlayerHealth(40 + myPlayer->GetEquippedHat()->GetValue());
	}
	else 
	{
		myPlayer->SetPlayerMaxHealth(40);
		myPlayer->SetPlayerHealth(40);
	}
	

	// Place all item, NPC, and enemy initializations for the city in this function
	SetSprintVilleNPCs();
	SpawnSprintVilleEnemies();
	SpawnSprintVilleItems();
	
	// Teleporter into Land of Scrum
	map->GetChunkAt(4, 2).GetTileAt(8, 12).SetItem(new Item("Gate", { L"🚪", 3 }, "You're at the dock; would you like to take the ride to the Land of Scrum?", Item::Type::TELEPORTER, 0, 0));

}

void GameManager::InitializeLandOfScrumWorld() {
	//Initialize map
	map = new Map(maps[2], landOfScrum.numRows, landOfScrum.numColumns);

	// Adjust player's position
	myPlayer->SetPlayerChunkLocation(landOfScrum.chunkX, landOfScrum.chunkY);
	myPlayer->SetPlayerLocation(landOfScrum.tileX, landOfScrum.tileY);
	if (myPlayer->GetEquippedHat() != nullptr)
	{
		myPlayer->SetPlayerMaxHealth(80 + myPlayer->GetEquippedHat()->GetValue());
		myPlayer->SetPlayerHealth(80 + myPlayer->GetEquippedHat()->GetValue());
	}
	else
	{
		myPlayer->SetPlayerMaxHealth(80);
		myPlayer->SetPlayerHealth(80);
	}

	// Place all item, NPC, and enemy initializations for the city in this 
	SpawnLandOfScrumEnemies();
	SpawnLandOfScrumItems();

	// Lock of Vallonious final boss room until the player answers that they would like to proceed
	map->GetChunkAt(5, 1).GetTileAt(0, 6).SetID(10);
	map->GetChunkAt(5, 1).GetTileAt(0, 7).SetID(10);
	map->GetChunkAt(5, 1).GetTileAt(0, 8).SetID(10);
	map->GetChunkAt(5, 1).GetTileAt(0, 9).SetID(10);
}

/*
* Respawn the player to the starting position of the current map with max health.
*/
void GameManager::RespawnPlayer()
{
	myPlayer->SetPlayerHealth(myPlayer->GetPlayerMaxHealth());
	switch(currentMap) 
	{
		case 0:
			myPlayer->SetPlayerChunkLocation(startingArea.chunkX, startingArea.chunkY);
			myPlayer->SetPlayerLocation(startingArea.tileX, startingArea.tileY);
			break;
		case 1:
			myPlayer->SetPlayerChunkLocation(city.chunkX, city.chunkY);
			myPlayer->SetPlayerLocation(city.tileX, city.tileY);
			break;
		case 2:
			myPlayer->SetPlayerChunkLocation(landOfScrum.chunkX, landOfScrum.chunkY);
			myPlayer->SetPlayerLocation(landOfScrum.tileX, landOfScrum.tileY);
			break;
		default:
			break;
	}
}

// Moves to the next work, thus changing the map
void GameManager::SetNewWorld() {
	currentMap++;

	switch (currentMap) {
	case 0:
		InitializeStartingAreaWorld();
		enemiesToDefeat = 4;
		break;
	case 1:
		InitializeCityWorld();
		enemiesToDefeat = 4;
		break;
	case 2:
		InitializeLandOfScrumWorld();
		enemiesToDefeat = 1;
		break;
	default:
		break;
	}
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
	spellBook = new Item("Scrummius' Spell Book", { L"📖", 3 }, "A certain peculiar owl's spellbook, who knows what secrets it may hold...", Item::Type::WEAPON, 4,1);
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

void GameManager::InitializeNinjaQuest()
{
	//Reset cin to use std::getLine(). This is to allow for user input that includes spaces.
	cin.ignore();

	//Ask player if they want to start
	string playerResponse;
	cout << "Your response? (Y/N): ";
	getline(cin, playerResponse);

	//Clean input
	NormalizeString(playerResponse);

	//Dialgue with NPC
	if (playerResponse == "Y" || playerResponse == "YES")
	{
		cout << "\nIs that so? Tell you what, I know where it is. Meet me in the city and I'll show it to you.\n";
		map->GetChunkAt(1, 3).GetTileAt(7, 12).GetNPC()->SetDialogue("Meet me in the city.");
		ninjaQuest->SetQuestStart(true);
	}
	else
	{
		cout << "\nThat's what I thought.\n";
		map->GetChunkAt(1, 3).GetTileAt(7, 12).GetNPC()->SetDialogue("You're back? Did you change your answer?");
	}
}
void GameManager::EnterHouseNinjaQuest()
{
	myPlayer->SetPlayerChunkLocation(3, 2);
	myPlayer->SetPlayerLocation(7, 4);
}
void GameManager::NinjaQuestComplete()
{
	//Drop crown
	map->GetChunkAt(3, 2).GetTileAt(9, 9).SetItem(new Item("Old Crown Hat", { L"👑", 3 }, "Crown of The Old King. Is it whispering to you?", Item::Type::EQUIPMENT, 50, 1));

	//Update king's dialogue
	map->GetChunkAt(3, 2).GetTileAt(9, 8).GetNPC()->SetDialogue("If that's all you needed, I would appreciate you leaving now.");

	//Update ninja status
	string ninjaDesc = "An evil ninja. It seems you've been betrayed.";
	map->GetChunkAt(4, 0).GetTileAt(9, 4).SetNPC(nullptr);
	map->GetChunkAt(4, 0).GetTileAt(9, 4).SetEnemy(new Enemy("Ninja", { L"🥷", 3 }, 30, new Item("Ninja Kunai", { L"🗡️", 3 }, "A kunai with some writting on it. It reminds you of a summoning rune.", Item::Type::WEAPON, 15, 1), "Shuriken Throw", 4, ninjaDesc));

	//Update complete bool
	ninjaQuest->SetQuestComplete(true);
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

//Ninja Quest getter
Quest* GameManager::GetNinjaQuest()
{
	return ninjaQuest;
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

void GameManager::GameBattleManager(Player& myPlayer)
{
	// Check if the battle is the tutorial battle against the Dust Golem
	if (!isFirstBattleDone && GetPlayerLocationTile().GetEnemy()->GetName() == "Dust Golem")
	{
		cout << "Before the battle begins, you hear Lord Vallonious' voice in your head...\n";
		cout << "FOOL! This seems to be your first battle. Let me teach you the basics, so that our final battle may at least be a fair one.\n";
		cout << "If you cannot even defeat this simple Dust Golem, you hold no chance to defeat ME!\n\n";
		cout << "You have 3 actions: ATTACK, DEFLECT, and RUN. Attack and Run are self-explanatory...\n";
		cout << "Deflect works like so: when an attack is deflected, the one who deflected takes half the damage, but so does the attacker.\n";
		cout << "May your future battles be bountiful... I await in the Land of Scrum for our EPIC ENCOUNTER!\n\n";

		// Update checker
		isFirstBattleDone = true;
	}

	// Flag to determine if the player successfully runs
	bool isActionRun = false;

	// Battle loop
	while (GetPlayerLocationTile().GetEnemy() != nullptr &&
		GetPlayerLocationTile().GetEnemy()->GetHealth() > 0 &&
		!isActionRun &&
		myPlayer.GetPlayerHealth() > 0)
	{
		//  Whats being siad for player action
		string battleAction;
		cout << "Enter Attack, Deflect, or Run for your action: ";
		cin >> battleAction;

		// Valiii input
		UserInputValidation playerChecker;
		bool validAction = playerChecker.ActionChecker(battleAction);

		// Fetch player and enemy data
		string enemyName = GetPlayerLocationTile().GetEnemy()->GetName();
		string playerName = myPlayer.GetPlayerName();
		int playerAttackDamage = myPlayer.GetPlayerAttackDamage();
		string playerAttackName = myPlayer.GetPlayerAttack();
		int enemyAttackDamage = GetPlayerLocationTile().GetEnemy()->GetEnemyAttackDamage();
		string enemyAttackName = GetPlayerLocationTile().GetEnemy()->GetEnemyAttack();
		int currentEnemyHealth = GetPlayerLocationTile().GetEnemy()->GetHealth();
		int currentPlayerHealth = myPlayer.GetPlayerHealth();

		// Making random chance for running
		srand((unsigned)time(nullptr));
		int runChance = 1 + (rand() % 100); // Random chance between 1 and 100

		// Clear the screen after a valid action
		system("cls");

		if (validAction)
		{
			switch (playerChecker.GetPlayerAction())
			{
			case UserInputValidation::Action::ATTACK:
				cout << playerName << " uses " << playerAttackName << " and deals " << playerAttackDamage << " HP!\n";
				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - playerAttackDamage);
				break;

			case UserInputValidation::Action::DEFLECT:
				cout << playerName << " deflects!\n";
				myPlayer.SetPlayerHealth(currentPlayerHealth - (enemyAttackDamage / 2));
				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - (enemyAttackDamage / 2));
				break;

			case UserInputValidation::Action::RUN:
				if (GetPlayerLocationTile().GetEnemy()->GetName() == "Dust Golem")
				{
					cout << "Lord Vallonious laughs at you for trying to run from the tutorial battle...\n";
				}
				else if (runChance <= (15 + (myPlayer.GetPlayerEvade() * 5))) // run success chance based on player evade stat
				{
					cout << "You ran away successfully! The " << enemyName << " still remains...\n";
					isActionRun = true;
					continue; // Exit  loop
				}
				else
				{
					cout << "You were not able to run away...\n";
				}
				break;

			default:
				cout << "Invalid action. You lost your turn.\n";
				break;
			}
		}
		else
		{
			cout << "Invalid command. You lost your turn.\n";
		}

		// Check if the enemy is defeated
		if (GetPlayerLocationTile().GetEnemy()->GetHealth() <= 0)
		{
			cout << enemyName << " has been defeated!\n";
			if (GetPlayerLocationTile().GetEnemy()->GetItem() != nullptr)
			{
				GetPlayerLocationTile().SetItem(GetPlayerLocationTile().GetEnemy()->GetItem());
				cout << "The enemy dropped an item!\n";
			}
			if (enemyName == "Dust Golem")
			{
				myPlayer.SetPlayerHealth(myPlayer.GetPlayerMaxHealth());
				cout << "Lord Vallonious heals you after your battle with the Dust Golem.\n";
				SpawnStartingAreaEnemies(); // Ensure enemies spawn after tutorial
			}
			GetPlayerLocationChunk().EnemyDefeted(GetPlayerLocationTile().GetEnemy());
			enemiesToDefeat--;
			if (enemiesToDefeat <= 0)
				cout << "\n!!! You have defeated the required number of enemies to proceed to the next area. Do your best to find its entrance. !!!\n";
			return;
		}

		// Enemy turn
		if (!isActionRun && GetPlayerLocationTile().GetEnemy()->GetHealth() > 0)
		{
			UserInputValidation::Action enemyAction = ProcessEnemyTurn(
				GetPlayerLocationTile().GetEnemy()->GetHealth(),
				GetPlayerLocationTile().GetEnemy()->GetStartingHealth()
			);
			if (enemyAction == UserInputValidation::Action::ATTACK)
			{
				cout << enemyName << " uses " << enemyAttackName << " and deals " << enemyAttackDamage << " HP!\n";
				myPlayer.SetPlayerHealth(currentPlayerHealth - enemyAttackDamage);
			}
			else if (enemyAction == UserInputValidation::Action::DEFLECT)
			{
				cout << enemyName << " deflects your attack, reducing damage taken!\n";
				GetPlayerLocationTile().GetEnemy()->SetHealth(currentEnemyHealth - (playerAttackDamage / 2));
				myPlayer.SetPlayerHealth(currentPlayerHealth - (playerAttackDamage / 2));
			}
		}

		// Display updated player and enemy health
		cout << "\nUpdated Status:\n";
		cout << "Enemy: " << enemyName << " | Health: " << GetPlayerLocationTile().GetEnemy()->GetHealth() << "\n";
		cout << "Player: " << playerName << " | Health: " << myPlayer.GetPlayerHealth() << "\n\n";
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

/*
* Equip an Item from the passed in Inventory object.
* Assumes Inventory is not empty.
*/
void GameManager::EquipItem(Inventory& playerInv)
{
	//Initialize player input string.
	string playerInput;

	//Reset cin to use std::getLine(). This is to allow for user input that includes spaces.
	cin.ignore();

	//Prompt player for which item to use.
	cout << "Type in the name if the item you wish to equip: ";
	getline(cin, playerInput);

	//Clean input.
	NormalizeString(playerInput);

	//Grab Item from Inventory.
	Item* grabbedItem = playerInv.findItem(playerInput);
	if (grabbedItem == nullptr)
	{
		cout << "Wrong item name.\n";
		return;
	}

	//Equip Item based on type. If Item can't be equipped, return it to Inventory.
	switch (grabbedItem->GetType())
	{
	case Item::Type::HEALING:
		cout << "Sorry, you can not equip a healing item. Utilize the USE command if you wish to use it.\n";
		break;
	case Item::Type::KEY:
		cout << "Sorry, you can not equip a key item.\n";
		break;
	case Item::Type::EQUIPMENT:
		if (grabbedItem->GetName().find("Hat") != string::npos)				//string::npos is the return type if the substring was not found
		{
			if (!grabbedItem->IsCurrentlyEquipped())
			{
				//Check for previous equipment and unequip it.
				if (myPlayer->GetEquippedHat() != nullptr)
				{
					myPlayer->SetPlayerMaxHealth(myPlayer->GetPlayerMaxHealth() - myPlayer->GetEquippedHat()->GetValue());
					myPlayer->SetPlayerHealth(myPlayer->GetPlayerHealth() - myPlayer->GetEquippedHat()->GetValue());
					myPlayer->GetEquippedHat()->Equip();
				}

				//Equip and update values
				myPlayer->SetPlayerMaxHealth(myPlayer->GetPlayerMaxHealth() + grabbedItem->GetValue());
				myPlayer->SetPlayerHealth(myPlayer->GetPlayerHealth() + grabbedItem->GetValue());
				myPlayer->SetEquippedHat(grabbedItem);
				cout << "You have equipped: " << grabbedItem->GetName() << ". Marking as equipped in inventory.\n";
			}
			else
			{
				//Unequip item
				myPlayer->SetPlayerMaxHealth(myPlayer->GetPlayerMaxHealth() - grabbedItem->GetValue());
				myPlayer->SetPlayerHealth(myPlayer->GetPlayerHealth() - grabbedItem->GetValue());
				myPlayer->SetEquippedHat(nullptr);
				cout << "You have unequipped: " << grabbedItem->GetName() << ". Marking as unequipped in inventory.\n";
			}
			cout << "Current max HP: " << myPlayer->GetPlayerMaxHealth() << endl;
		}
		else if (grabbedItem->GetName().find("Robe") != string::npos)		//string::npos is the return type if the substring was not found
		{
			if (!grabbedItem->IsCurrentlyEquipped())
			{
				//Check for previous equipment and unequip it.
				if (myPlayer->GetEquippedBody() != nullptr)
				{
					myPlayer->SetPlayerEvade(myPlayer->GetPlayerEvade() - myPlayer->GetEquippedBody()->GetValue());
					myPlayer->GetEquippedBody()->Equip();
				}

				//Equip and update values
				myPlayer->SetPlayerEvade(myPlayer->GetPlayerEvade() + grabbedItem->GetValue());
				myPlayer->SetEquippedBody(grabbedItem);
				cout << "You have equipped: " << grabbedItem->GetName() << ". Marking as equipped in inventory.\n";
			}
			else
			{
				//Unequip item
				myPlayer->SetPlayerEvade(myPlayer->GetPlayerEvade() - grabbedItem->GetValue());
				myPlayer->SetEquippedBody(nullptr);
				cout << "You have unequipped: " << grabbedItem->GetName() << ". Marking as unequipped in inventory.\n";
			}
			cout << "Current evade status: " << myPlayer->GetPlayerEvade() << endl;
		}
		grabbedItem->Equip();
		break;
	case Item::Type::WEAPON:
		if (!grabbedItem->IsCurrentlyEquipped())
		{
			//Check for previous equipment and unequip it.
			if (myPlayer->GetEquippedWeapon() != nullptr)
			{
				myPlayer->GetEquippedWeapon()->Equip();
			}

			//Equip and update values
			myPlayer->SetPlayerAttackDamage(grabbedItem->GetValue());
			myPlayer->SetPlayerAttack(grabbedItem->GetName());
			myPlayer->SetEquippedWeapon(grabbedItem);
			cout << "You have equipped: " << grabbedItem->GetName() << ". Marking as equipped in inventory.\n";
		}
		else
		{
			//Unequip item
			myPlayer->SetPlayerAttackDamage(2);
			myPlayer->SetPlayerAttack("Knuckle Sandwich");
			myPlayer->SetEquippedWeapon(nullptr);
			cout << "You have unequipped: " << grabbedItem->GetName() << ". Marking as unequipped in inventory.\n";
		}
		grabbedItem->Equip();
		break;
	case Item::Type::TELEPORTER:
		cout << "Sorry, you can not equip a teleporter item.\n";
		break;
	case Item::Type::EMPTY:
		cout << "Wrong item name.\n";
		break;
	}
}

void GameManager::SpawnStartingAreaEnemies()
{
	// Enemy Descriptions
	string squirrelDesc = "A magical squirrel with powers. You wonder how it passed it's Wizard Schoool exams to get it's wand...";
	string mushroomDesc = "A walking and talking mushroom. It may hold healing attributes, it may be poisonous... only you can be the judge of that!";
	string stumpDesc = "A gnarled, rotting tree stump brought to life by dark magic.";

	// Wizard Squirrels-- first squirrel drops Leaf Sword
	// Chunk 2,1
	map->GetChunkAt(2, 1).GetTileAt(2, 5).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Leaf Sword", { L"🗡️", 3 }, "Sword that does does 3 damage.", Item::Type::WEAPON, 3, 1), "Nut Throw", 2, squirrelDesc));
	map->GetChunkAt(2, 1).GetTileAt(13, 1).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2,squirrelDesc));
	map->GetChunkAt(2, 1).GetTileAt(13, 11).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Nut Throw", 2, squirrelDesc));

	// Chunk 1,2
	map->GetChunkAt(1, 2).GetTileAt(6, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Nut Throw", 2, squirrelDesc));
	map->GetChunkAt(1, 2).GetTileAt(9, 8).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Rusty Sword", { L"🗡️", 3 }, "Well-worn sword, but it still packs a punch!", Item::Type::WEAPON, 5, 1), "Nut Throw", 2, squirrelDesc));

	// Chunk 3,1
	map->GetChunkAt(3,1).GetTileAt(4, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, new Item("Rusty Sword", { L"🗡️", 3 }, "Well-worn sword, but it still packs a punch!", Item::Type::WEAPON, 5, 1), "Nut Throw", 2, squirrelDesc));
	map->GetChunkAt(3, 1).GetTileAt(8, 1).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2, squirrelDesc));
	map->GetChunkAt(3,1).GetTileAt(12, 14).SetEnemy(new Enemy("Wizard Squirrel", { L"🐿️", 3 }, 15, "Nut Throw", 2, squirrelDesc));

	// Mushroom Warriors
	// Chunk 4,2
	map->GetChunkAt(4, 2).GetTileAt(14, 5).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));
	map->GetChunkAt(4, 2).GetTileAt(1, 4).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3, mushroomDesc));
	map->GetChunkAt(4, 2).GetTileAt(13, 8).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));

	// Chunk 1,2
	map->GetChunkAt(1, 2).GetTileAt(1, 4).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, new Item("Healing Mushroom", { L"🧋", 3 }, "Use this mushroom to heal your HP!", Item::Type::HEALING, 8, 1), "Mushroom Drop", 3, mushroomDesc));
	map->GetChunkAt(1, 2).GetTileAt(14, 2).SetEnemy(new Enemy("Mushroom Warrior", { L"🍄", 3 }, 12, "Mushroom Drop", 3, mushroomDesc));


	// Possessed Stumps
	// Chunk 4, 4
	map->GetChunkAt(4, 4).GetTileAt(8, 12).SetEnemy(new Enemy("Possessed Stump", { L"👿", 3 }, 16, new Item("Elixer of Renewal", { L"🧋", 3 }, "Use this potion to heal your HP!", Item::Type::HEALING, 12, 1), "Splinter Swipe", 3, stumpDesc));

	// Chunck 4,2
	map->GetChunkAt(4, 2).GetTileAt(1, 12).SetEnemy(new Enemy("Possessed Stump", { L"👿", 3 }, 16, "Splinter Swipe", 3, stumpDesc));
}

void GameManager::SpawnStartingAreaItems()
{
	// Item Descriptions
	string wandOfSparkingDesc = "A spark of inspiration... or just a spark. Deals minor ouchies.";
	string platinumSwordDesc = "Shiny and sharp! This sword looks fancier than it actually is.";
	string maceDesc = "For when you want to flatten foes medieval style.";
	string moltenFuryDesc = "Lava-hot. Perfect for warming up enemies... permanently.";
	string charmedHatDesc = "Stylish and slightly enchanted. It won't make you smarter, but it might make you luckier.";
	string charmedRobeDesc = "Run away in style with this robe of questionable evasiveness.";
	string lesserHealingPotionDesc = "Tiny but mighty! It's like a hug for your HP";

	// Chunk 1,0 Items
	map->GetChunkAt(1, 0).GetTileAt(5, 6).SetItem(new Item("Wand of Sparking", { L"🪄", 3 }, wandOfSparkingDesc, Item::Type::WEAPON, 5, 1));
	map->GetChunkAt(1, 0).GetTileAt(5, 13).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// Chunk 1,2 Items
	map->GetChunkAt(1, 2).GetTileAt(3, 8).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// Chunk 1,3 Items
	map->GetChunkAt(1, 3).GetTileAt(7, 14).SetItem(new Item("Platinum Sword", { L"🗡️", 3 }, platinumSwordDesc, Item::Type::WEAPON, 6, 1));

	// Chunk 2,1 Items
	map->GetChunkAt(2, 1).GetTileAt(5, 13).SetItem(new Item("Charmed Hat", { L"🎓", 3 }, charmedHatDesc, Item::Type::EQUIPMENT, 3, 1));

	// Chunk 3,1 Items
	map->GetChunkAt(3, 1).GetTileAt(8, 6).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// Chunk 4,1 Items
	map->GetChunkAt(4, 1).GetTileAt(5, 13).SetItem(new Item("Molten Fury", { L"🏹", 3 }, moltenFuryDesc, Item::Type::WEAPON, 4, 1));

	// Chunk 4,2 Items
	map->GetChunkAt(4, 2).GetTileAt(13, 14).SetItem(new Item("Charmed Robe", { L"👘", 3 }, charmedRobeDesc, Item::Type::EQUIPMENT, 1, 1));

	// Chunk 4,3 Items
	map->GetChunkAt(4, 3).GetTileAt(4, 7).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// Chunk 4,4 Items
	map->GetChunkAt(4, 4).GetTileAt(8, 14).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));
}
void GameManager::SpawnSprintVilleEnemies() {

	// Enemy Descriptions
	string pigeonDesc = "A hybrid of pigeon and griffin, this creature combines the ferocity of a predator with the annoyance of a city pest. Approach with caution!";
	string goblinDesc = "A cunning and nimble foe, the Goblin Thief thrives in chaos. Known for its underhanded tactics, it will blind and distract its enemies before darting in for a devastating attack.";
	string trashManDesc = "A small garbage bag come to life. So much for recycling...";

	// Pigeon Griffin Enemies
	// Chunk 1,0
	map->GetChunkAt(1, 1).GetTileAt(7, 6).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Winged Blade", { L"🗡️", 3 }, "A sword made from the sharp wings of the pigeon griffin.", Item::Type::WEAPON, 5, 1), "Sky Peck", 4, pigeonDesc));
	map->GetChunkAt(1, 1).GetTileAt(8, 10).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));

	// Chunk 2,1
	map->GetChunkAt(2, 1).GetTileAt(4, 10).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));
	map->GetChunkAt(2, 1).GetTileAt(8, 14).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));
	map->GetChunkAt(2, 1).GetTileAt(10, 7).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));
	map->GetChunkAt(2, 1).GetTileAt(4, 2).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));

	// Chunk 2,0
	map->GetChunkAt(2, 0).GetTileAt(6, 4).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Winged Blade", { L"🗡️", 3 }, "A sword made from the sharp wings of the pigeon griffin.", Item::Type::WEAPON, 5, 1), "Sky Peck", 4, pigeonDesc));

	// Chunk 3,0
	map->GetChunkAt(3, 0).GetTileAt(1, 5).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, new Item("Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 5, 1), "Sky Peck", 4, pigeonDesc));
	map->GetChunkAt(3, 0).GetTileAt(13, 2).SetEnemy(new Enemy("Pigeon Griffin", { L"🦅", 3 }, 20, "Sky Peck", 4, pigeonDesc));

	// Goblin Thief Enemies

	// Chunk 3,0
	map->GetChunkAt(3, 0).GetTileAt(4, 9).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Sneaky Slash", 5, goblinDesc));
	map->GetChunkAt(3, 0).GetTileAt(10, 7).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, "Sneaky Slash", 5, goblinDesc));
	map->GetChunkAt(3, 0).GetTileAt(13, 13).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, "Sneaky Slash", 5, goblinDesc));

	// Chunk 4,0
	map->GetChunkAt(4, 0).GetTileAt(2, 13).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Sneaky Slash", 5, goblinDesc));
	map->GetChunkAt(4, 0).GetTileAt(14, 3).SetEnemy(new Enemy("Goblin Thief", { L"🧌", 3 }, 25, new Item("Goblin's Dagger", { L"🗡️", 3 }, "The dagger of a goblin thief.", Item::Type::WEAPON, 8, 1), "Sneaky Slash", 5, goblinDesc));

	// Magical Trash man Enemies-- same Health as Goblin, but does 1 HP damage more
	//Chunk 4,1
	map->GetChunkAt(4, 1).GetTileAt(2, 3).SetEnemy(new Enemy("Magical Trash Man", { L"🗑️", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Waste Hurl", 6, trashManDesc));
	map->GetChunkAt(4, 1).GetTileAt(12, 12).SetEnemy(new Enemy("Magical Trash Man", { L"🗑️", 3 }, 25,  "Waste Hurl", 5, trashManDesc));
	map->GetChunkAt(4, 1).GetTileAt(3, 10).SetEnemy(new Enemy("Magical Trash Man", { L"🗑️", 3 }, 25, new Item("Mega Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 10, 1), "Waste Hurl", 6, trashManDesc));
}

/* This function is used to initialize the enemies in the Land of Scrum Area
*/
void GameManager::SpawnSprintVilleItems()
{
	// Weapon Descriptions and Initialization
	string platinumSwordDesc = "A sword dropped from a knight. It yearns to be wielded once again.";
	string blueMoonDesc = "Pack a wallop once in a blue moon—or every day!";
	map->GetChunkAt(2, 1).GetTileAt(12,3).SetItem(new Item("Platinum Sword",{L"🗡️",5},platinumSwordDesc,Item::Type::WEAPON,8,1));
	map->GetChunkAt(4, 0).GetTileAt(14, 7).SetItem(new Item("Blue Morning Star", { L"🏹",3 }, blueMoonDesc, Item::Type::WEAPON, 9, 1));

	// Item Description and Initialization
	string healingPotionDesc = "A mid-level pick-me-up. Better than an apple a day!";
	string lesserHealingPotionDesc = "Tiny but mighty! It's like a hug for your HP";
	map->GetChunkAt(2, 0).GetTileAt(7, 3).SetItem(new Item("Healing Potion", {L"🍵",3}, healingPotionDesc,Item::Type::HEALING,10,1));
	map->GetChunkAt(4, 0).GetTileAt(12, 4).SetItem(new Item("Healing Potion", { L"🍵",3 }, healingPotionDesc, Item::Type::HEALING, 10, 1));
	map->GetChunkAt(3, 0).GetTileAt(8, 12).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// SprintVille Robe
	string enchantedRobeDesc = "Like the charmed robe, but with extra swish and dodge.";
	map->GetChunkAt(4, 1).GetTileAt(6, 13).SetItem(new Item("Enchanted Robe", { L"👘",3 },enchantedRobeDesc, Item::Type::EQUIPMENT,  2, 1));

	// SprintVille Hat
	string enchantedHatDesc = "Guaranteed to add a mystical flair to your headgear collection.";
	map->GetChunkAt(2, 1).GetTileAt(12, 13).SetItem(new Item("Enchanted Hat", {L"🎓",3},enchantedHatDesc, Item::Type::EQUIPMENT,6,1));

}

void GameManager::SpawnLandOfScrumEnemies() {

	// Enemy Descriptions
	string blobDesc = "A malevolent mass of darkness, the Evil Dark Blob lurks in the Land of Scrum, waiting to engulf unwary adventurers.";
	string shadowDesc = "A sinister wisp of darkness that floats eerily, its faint whispers sowing unease in the hearts of adventurers.";
	string valloniousDesc = "The wicked dragon of the land of Restrospecta. Defeat him and finish your quest!";

	// Puts the enemies in the map
	// Dark Evil Blob Enemies
	// Chunk 1,1
	map->GetChunkAt(1, 1).GetTileAt(2, 5).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(1, 1).GetTileAt(13, 10).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Venombrand", { L"🗡️", 3 }, "A sinister sword forged from toxic metals, its blade drips with a corrosive venom", Item::Type::WEAPON, 12, 1), "Corrosive Strike", 6, blobDesc));

	// Chunk 2,2
	map->GetChunkAt(2, 2).GetTileAt(8, 14).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));

	// Chunk 4,0
	map->GetChunkAt(4, 0).GetTileAt(5, 13).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(4, 0).GetTileAt(8, 1).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, "Corrosive Strike", 6, blobDesc));

	// Chunk 3,0
	map->GetChunkAt(3, 0).GetTileAt(5, 6).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(3, 0).GetTileAt(5, 11).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Venomshot", { L"🏹", 3 }, "A bow that shoots arrows filled with a corrosive venom", Item::Type::WEAPON, 14, 1), "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(3, 0).GetTileAt(10, 14).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, "Corrosive Strike", 6, blobDesc));

	// Chunk 3,2
	map->GetChunkAt(3, 2).GetTileAt(5, 6).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(3, 2).GetTileAt(5, 11).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, "Corrosive Strike", 6, blobDesc));
	map->GetChunkAt(3, 2).GetTileAt(10, 14).SetEnemy(new Enemy("Dark Evil Blob", { L"🌑", 3 }, 27, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Corrosive Strike", 6, blobDesc));

	// Gloomy Shadow Enemies
	// Chunk 2,1
	map->GetChunkAt(2, 1).GetTileAt(5, 2).SetEnemy(new Enemy("Gloomy Shadow", {L"👤", 3}, 30, new Item("Shadowfang Blade", {L"🗡️", 3}, "A lightweight sword imbued with dark energy. Deals 9 HP per hit.", Item::Type::WEAPON, 9, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(2, 1).GetTileAt(5, 13).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));

	// Chunk 2,2
	map->GetChunkAt(2, 2).GetTileAt(13, 5).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));

	// Chunk 2,0
	map->GetChunkAt(2, 0).GetTileAt(13, 10).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(2, 0).GetTileAt(8, 1).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, "Dreadful Embrace", 7, shadowDesc));

	// Chunck 3,0
	map->GetChunkAt(3, 0).GetTileAt(5, 1).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(3, 0).GetTileAt(10, 4).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Darkvein Bow", { L"🏹", 3 }, "A bow imbued with dark energy. Deals 11 HP per hit.", Item::Type::WEAPON, 11, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(3, 0).GetTileAt(10, 9).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, "Dreadful Embrace", 7, shadowDesc));

	// Chunk 4,2
	map->GetChunkAt(4, 2).GetTileAt(8, 14).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(4, 2).GetTileAt(5, 2).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Eclipse Blade", { L"🗡", 3 }, "A long sword imbued with dark energy. Deals 13 HP per hit.", Item::Type::WEAPON, 13, 1), "Dreadful Embrace", 7, shadowDesc));

	// Chunk 3,2
	map->GetChunkAt(3, 2).GetTileAt(5, 1).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(3, 2).GetTileAt(10, 4).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, "Dreadful Embrace", 7, shadowDesc));
	map->GetChunkAt(3, 2).GetTileAt(10, 9).SetEnemy(new Enemy("Gloomy Shadow", { L"👤", 3 }, 30, new Item("Super Potion", { L"🧋", 3 }, "Use this potion to restore your HP", Item::Type::HEALING, 25, 1), "Dreadful Embrace", 7, shadowDesc));

	// Lord Vallonious
	map->GetChunkAt(5, 1).GetTileAt(10, 7).SetEnemy(new Enemy("Lord Vallonious", { L"🐉",3 }, 65, new Item("Legendary Gapplin", { L"🍏", 9 }, "The reason for your journey. Take good care of him! :)", Item::Type::KEY, 100, 1), "Dragon Breath", 9, valloniousDesc));
}

/* This function is used to initalize any items placed in the Land of Scrum Area
*/
void GameManager::SpawnLandOfScrumItems()
{
	// Land of Scrum Weapons
	string excaliburSwordDesc =  "Legend has it this blade is invincible. Your mileage may vary.";
	string phantomPhoenixDesc = "A mystical bird of fire, now available in bow form.";
	map->GetChunkAt(1, 1).GetTileAt(4, 1).SetItem(new Item("Excalibur", { L"🗡️",5 }, excaliburSwordDesc, Item::Type::WEAPON, 10, 1));
	map->GetChunkAt(2, 0).GetTileAt(11, 14).SetItem(new Item("Phantom Phoenix", { L"🏹",3 }, phantomPhoenixDesc, Item::Type::WEAPON, 10, 1));

	// Item Description and Initialization
	string greaterHealingPotionDesc = "This one packs a real punch—right to your health bar!";
	string lesserHealingPotionDesc = "Tiny but mighty! It's like a hug for your HP";
	map->GetChunkAt(1, 1).GetTileAt(11, 14).SetItem(new Item("Greater Healing Potion", { L"🍵",3 }, greaterHealingPotionDesc, Item::Type::HEALING, 15, 1));
	map->GetChunkAt(2, 2).GetTileAt(11, 1).SetItem(new Item("Greater Healing Potion", { L"🍵",3 }, greaterHealingPotionDesc, Item::Type::HEALING, 15, 1));
	map->GetChunkAt(4, 2).GetTileAt(1, 4).SetItem(new Item("Lesser Healing Potion", { L"🧋", 3 }, lesserHealingPotionDesc, Item::Type::HEALING, 6, 1));

	// Land of Scrum Robe
	string arcaneRobeDesc = "Arcane fabric, made for escaping danger—now in limited supply!";
	map->GetChunkAt(4, 0).GetTileAt(1, 11).SetItem(new Item("Arcane Robe", { L"👘",3 }, arcaneRobeDesc, Item::Type::EQUIPMENT, 4, 1));

	// Land of Scrum Hat
	string arcaneHatDesc = "Woven with arcane magic... and maybe a bit of thread from Granny's attic.";
	map->GetChunkAt(3, 0).GetTileAt(14, 1).SetItem(new Item("Arcane Hat", { L"🎓",3 }, arcaneHatDesc, Item::Type::EQUIPMENT, 9, 1));
}

void GameManager::CheckForValloniousRoom()
{
	// Check that the player has enter Vallonious' Room
	// Chunk 4,1 and since the entrance way is 4 tiles long, you have to account for Rows 6-9, but all the same column of 15
	string playerAnswer;
	if ((myPlayer->GetPlayerChunkLocationX() == 4 && myPlayer->GetPlayerChunkLocationY() == 1) && map->GetChunkAt(5, 1).GetTileAt(0, 6).GetID() == 10)
	{
		if ((myPlayer->GetPlayerLocationY() == 6 || myPlayer->GetPlayerLocationY() == 7 || myPlayer->GetPlayerLocationY() == 8 || myPlayer->GetPlayerLocationY() == 9) && myPlayer->GetPlayerLocationX() == 15)
		{
			if (enemiesToDefeat <= 0)
			{
				// Give story beat/Dialogue if the player has entered the room with Lord Vallonious
				cout << "\n\nLord Vallonious says: Welcome FOOL! I hope you've prepared well enough for our final battle\n If you must turn back now and prepare further, I will be merciful and allow you to do so.\n";
				cout << "This may be thy final battle after all... the choice is yours...\n\n";
				cout << "You feel as though there is no turning back after this point...\n";
				cout << "As you think that, you hear Gapplin's cry coming from behind Vallonious' throne...\n";
				cout << "Would you like to proceed? ";
				cin >> playerAnswer;
				cout << endl;
				NormalizeString(playerAnswer);
				if (playerAnswer == "YES")
				{
					cout << "Lord Vallonious says: VERY WELL THEN FOOL! Our battle will be legendary.\n I will laugh my way as I take Gapplin and make him mine own.\n I hope your journey has been bountiful, but I'm afraid it ends HERE!!!!\n\n";
					map->GetChunkAt(5, 1).GetTileAt(0, 6).SetID(9);
					map->GetChunkAt(5, 1).GetTileAt(0, 7).SetID(17);
					map->GetChunkAt(5, 1).GetTileAt(0, 8).SetID(17);
					map->GetChunkAt(5, 1).GetTileAt(0, 9).SetID(9);
				}
				else
				{
					cout << "Lord Vallonious says: Go prepare and ready yourself for the final battle then... I'll be merciful as this will certainly be your last fight... MUAHAHAHAHAHHAHAH.\n\n";
				}
			}
			else
				cout << "\n\nLord Vallonious says: FOOL! You'll need to defeat " << enemiesToDefeat << " more enemies before you can even dream to reach me!\n\n";
		}
	}
}
/*
Quest Makers for the Ship Captain's Quest
Quest start- "thief" steals spellbook
Quest End- talking to ship captain
Story Beat: "Thief" was actually the ship captain, so now player can sail to Land of Scrum free of charge!
*/
void GameManager::InitializeCaptainQuest()
{
	captainQuest->SetQuestStart(true);
	// Implementing Spellbook Thief-- bumps into you the second you enter the city
	cout << "A man bumps your shoulder. Bump. You suddenly feel lighter. Your spellbook, it's gone. You throw this thief a glare. His eyes snap back at you and he says...\n";
	cout << "Arg sorry mate I am in a rush. I'll take this for now. Don't delay and be hasteful!\n";
	cout << "You watch the strange man run away. You feel encouraged to chase him down and retrieve the spellbook!\n";
	// Remove the spellbook from the player's inventory
	if (inventory->findItem("SCRUMMIUS' SPELL BOOK")->IsCurrentlyEquipped())
	{
		//Unequip item
		myPlayer->SetPlayerAttackDamage(2);
		myPlayer->SetPlayerAttack("Knuckle Sandwich");
		myPlayer->GetEquippedWeapon()->Equip();
		myPlayer->SetEquippedWeapon(nullptr);
	}
	inventory->removeItem("SCRUMMIUS' SPELL BOOK");
}
bool GameManager::CaptainQuestComplete()
{
	captainQuest->SetQuestStart(false);
	captainQuest->SetQuestComplete(true);
	// Prompting the player that their spellbook is back in the inventory

	// Updating the Ship captain dialogue once the quest has been completed
	map->GetChunkAt(4, 2).GetTileAt(8, 10).GetNPC()->SetDialogue("Sorry for the mix up matey!\n");
	if (inventory->findItem("SCRUMMIUS' SPELL BOOK") == nullptr)
	{
		cout << "You have completed the Captain's Quest. Your spellbook has been added back to your inventory\n\n";
		inventory->addItem(*spellBook);

	}
	else
	{
		cout << "Walk over yonder and get ready to sail!\n";
	}

	//Prompting the player that they can now go into the land of scrum
	cout << "Now go forth and sail the seas to the Land of Scrum! Who knows what troubles await you on your quest for Gapplin!\n";
	return true;
}

void GameManager::SetSprintVilleNPCs()
{
	//Ship captain
	string shipCaptainDialogue = "Ahoy there, matey! Let's see yer ticket. No ticket, no voyage to the fabled Land o Scrum, savvy?\nAye, step aboard if ye've got it, but mind ye keep to the code... or the sea'll sort ye out proper!\n Wait a minute... I remember you I took your ticket already!\n\n**Pulls out spellbook**\n\n Wait this is not a ticket, this be yer spellbook... My apologies matey. For ye troubles, I will sail ye to the the fabled Land o' Scrum free o charge!\n\n **The Captain hands you back your spellbook**\n";
	map->GetChunkAt(4, 2).GetTileAt(8, 10).SetNPC(new NPC("Ship Captain", { L"⚓", 3 }, shipCaptainDialogue));

	//Ninja
	string ninjaNPCDialogue = "";
	if(ninjaQuest->GetQuestStart())
		ninjaNPCDialogue = "You made it. The crown is just through that door. But be prepared for a fight.";
	else
		ninjaNPCDialogue = "There is a dead ninja here. How strange.";
	map->GetChunkAt(4, 0).GetTileAt(9, 4).SetNPC(new NPC("Ninja", { L"🥷", 3 }, ninjaNPCDialogue));

	//Old King
	string oldKingDialogue = "Huh? You're here looking for a crown? Sure, take it. If it brought you here then I'd rather get rid of it.";
	map->GetChunkAt(3, 2).GetTileAt(9, 8).SetNPC(new NPC("The Old King", { L"🥷", 3 }, oldKingDialogue));

	//Doors
	map->GetChunkAt(4, 0).GetTileAt(9, 5).SetItem(new Item("HouseDoor", { L"🚪", 3 }, "This is a door to someone's house.", Item::Type::TELEPORTER, 0, 0));
	map->GetChunkAt(3, 2).GetTileAt(7, 4).SetItem(new Item("HouseDoorExit", { L"🚪", 3 }, "This is a door to someone's house.", Item::Type::TELEPORTER, 0, 0));
}

void GameManager::RollEndCredits()
{
	if (inventory->findItem("LEGENDARY GAPPLIN") != nullptr && myPlayer->GetEquippedHat()->GetName() == "Old Crown Hat")
	{
		cout << endl;
		cout << "Lord Vallonious turns to ash. Leaving an empty throne behind.\n";
		cout << "You feel strangely calm. The ambient quiet room seems serene.\n";
		cout << "An instinct beckons you to slowly sit down on the throne.\n";
		cout << "You hold Gapplin in your hand and each of you looks at each other with a strange sense of understanding.\n";
		cout << "You put your hand to the ground and let Gapplin go. You watch as he walks out of the room.\n";
		cout << "Maybe this spot isn't so bad. Finally, some peace and quiet.\n\n";
		cout << "-------------------------------------------------------------------------------------------------------\n";
		cout << "Thank you so much for playing our game!\n";
		cout << "Even though you cannot go back to previous areas, you are free to walk around the Land of Scrum!\n";
		cout << "---------------------------------------------------------------------------------------------------------\n\n";
		cout << "Gapplin says: Thank you for saving me! I hope your journey here was a good one!\n\n";
		cout << "A voice from beyond says: you may now close the game. Thanks for playing!\n";
	}
	else if (inventory->findItem("LEGENDARY GAPPLIN") != nullptr)
	{
		cout << endl;
		cout << "Lord Vallonious says: ARGHHHHHHHHHH. This is not my end.\n";
		cout << "This is not the last you see of me! I WILL HAVE MY REVENGE.\n\n";
		cout << "A voice from beyond says: With Vallonious now defeated, Restrospecta can be at peace once again.\n";
		cout << "You feel strongly however, that this is not the last you will see of Vallonious...\n\n";
		cout << "-------------------------------------------------------------------------------------------------------\n";
		cout << "Thank you so much for playing our game!\n";
		cout << "Even though you cannot go back to previous areas, you are free to walk around the Land of Scrum!\n";
		cout << "Legend of Gapplin was created by Team Overflow!\n";
		cout << "Credits to the team behind the creation of this game!:\n";
		cout << "Xavier Orrala, Tiffany Coelho, Shakir Templeman, Drilon Toska, Ryan Benyahia, and Joe Cangiano\n";
		cout << "---------------------------------------------------------------------------------------------------------\n\n";
		cout << "Gapplin says: Thank you for saving me! I hope your journey here was a good one!\n\n";
		cout << "A voice from beyond says: you may now close the game. Thanks for playing!\n";
	}
}
/*
* Return the number of enemies left to defeat before the player can proceed to the next area.
*/
int GameManager::GetEnemiesLeftToDefeat()
{
	return enemiesToDefeat;
}