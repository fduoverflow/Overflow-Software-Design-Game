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
	Quest* firstQuest;
	Quest* branchesOfHeroesQuest;
	Quest* threeStonesQuest;
	Quest* captainQuest;
	Item* spellBook;
	bool WillCollide(int, int, int, int);	// Checks whether of not the new player position is collidable

	//Bool to check if player has completed tutorial battle.
	bool isFirstBattleDone;

public:
	// Constructors
	GameManager();
	GameManager(Player*, Map*);

	// Moves to the next world, thus changing the map
	// Sets the coordinates of the player on the new world
	void MoveToWorld(Map*, int, int, int, int);

	//Moves player in given direction enum
	void MovePlayer(UserInputValidation::Move);

	// Displays the map and anything within it
	void Display();
	void DisplayMap();

	//Returns the Tile address at player's current location.
	Tile& GetPlayerLocationTile();

	//Return the Chunk address at player's current location.
	Chunk& GetPlayerLocationChunk();

	void InitilizeTutorialQuest(); // First Quest -- Retrieve spellbook from house after talking to Scrummius (owl)
	void TutorialQuestComplete();

	void InitializeCaptainQuest(Inventory); //Quest Where player must retrieve their spellbook after it has been stolen by the thief as the player entered SprintVille
	bool CaptainQuestComplete(Inventory*);

	//Quest getters and setters
	Quest* GetFirstQuest();
	Quest* GetBranchesQuest();
	Quest* GetThreeStonesQuest();
	Quest* GetCaptainQuest();

	void GameBattleManager(Player&); // Function that will manage how battles work and the interactions between the ATTACK, DEFLECT, and RUN actions
	UserInputValidation::Action ProcessEnemyTurn(int currentEnemyHealth, int startEnemyhealth);

	//Puzzles methods that the player will encounter.
	bool BranchesOfHerosPuzzle();
	bool ThreeStonesPuzzle();

	//Normalize string method
	void NormalizeString(string& input);

	//Initialize starting area enemies
	Map* GetMap();
	void SpawnStartingAreaEnemies(Map);

	//Use item from passed Inventory
	void UseItem(Inventory& playerInv);
	void SpawnSprintVilleEnemies(Map);
	void SpawnLandOfScrumEnemies(Map);

	// Setting the NPCs of Sprintville
	void SetSprintVilleNPCs(Map);
};
