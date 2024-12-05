#pragma once
#include "Player.h"
#include "Map.h"
#include "UserInputValidation.h"
#include "Tile.h"
#include "Quest.h"
#include "Inventory.h"


class GameManager
{
private:
	Player* myPlayer;
	Map* map;
	Inventory* inventory;
	Quest* firstQuest;
	Quest* branchesOfHeroesQuest;
	Quest* threeStonesQuest;
	Quest* captainQuest;
	Quest* ninjaQuest;
	Item* spellBook;
	int enemiesToDefeat;					//Number of enemies that need to be defeated to move on to the next area
	bool WillCollide(int, int, int, int);	// Checks whether of not the new player position is collidable

	//Bool to check if player has completed tutorial battle.
	bool isFirstBattleDone;

	// Functions to initialize different worlds
	void InitializeStartingAreaWorld();
	void InitializeCityWorld();
	void InitializeLandOfScrumWorld();

public:
	// Constructors
	GameManager();
	GameManager(Player*);
	GameManager(Player*, Inventory*);

	// Moves to the next world, thus changing the map
	// Sets the coordinates of the player on the new world
	void SetNewWorld();

	//Moves player in given direction enum
	void MovePlayer(UserInputValidation::Move);

	// Displays the map and anything within it
	void Display();
	void DisplayMap();
	
	void ClearScreenAndPrompt();
	void ClearBattleMessages();

	//Returns the Tile address at player's current location.
	Tile& GetPlayerLocationTile();

	//Return the Chunk address at player's current location.
	Chunk& GetPlayerLocationChunk();

	//Quest initializers
	void InitilizeTutorialQuest();	// First Quest -- Retrieve spellbook from house after talking to Scrummius (owl)
	void TutorialQuestComplete();

	void InitializeCaptainQuest();	//Quest Where player must retrieve their spellbook after it has been stolen by the thief as the player entered SprintVille
	bool CaptainQuestComplete();

	void InitializeNinjaQuest();	//Quest given by the ninja
	void EnterHouseNinjaQuest();
	void NinjaQuestComplete();

	//Quest getters and setters
	Quest* GetFirstQuest();
	Quest* GetBranchesQuest();
	Quest* GetThreeStonesQuest();
	Quest* GetCaptainQuest();
	Quest* GetNinjaQuest();

	void GameBattleManager(Player&); // Function that will manage how battles work and the interactions between the ATTACK, DEFLECT, and RUN actions
	UserInputValidation::Action ProcessEnemyTurn(int currentEnemyHealth, int startEnemyhealth);

	//Puzzles methods that the player will encounter.
	bool BranchesOfHerosPuzzle();
	bool ThreeStonesPuzzle();

	//Normalize string method
	void NormalizeString(string& input);

	//Initialize starting area enemies
	Map* GetMap();
	void SpawnStartingAreaEnemies();
	void SpawnSprintVilleEnemies();
	void SpawnLandOfScrumEnemies();

	//Respawn player on death
	void RespawnPlayer();

	//Initialize starting area items
	void SpawnStartingAreaItems();

	//Initialize Land of Scrum items
	void SpawnLandOfScrumItems();
  
	//Initialize SpintVille items
	void SpawnSprintVilleItems();


	//Use Item from passed Inventory
	void UseItem(Inventory& playerInv);

	//Equip Item from passed Inventory
	void EquipItem(Inventory& playerInv);

	// Setting the NPCs of Sprintville
	void SetSprintVilleNPCs();

	//Control variable getters
	int GetCurrentMap();
	int GetEnemiesLeftToDefeat();

	//Checking to see if the player is at the doors of Vallonious' room
	void CheckForValloniousRoom();

	// Checking to see if the player has finished the game
	void RollEndCredits();
};
