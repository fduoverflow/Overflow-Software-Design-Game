#pragma once
#include "Player.h"
#include "Map.h"
#include "UserInputValidation.h"
#include "Tile.h"
#include "Quest.h"


class GameManager
{
private:
	Player* myPlayer;
	Map* map;
	Quest* firstQuest;
	Quest* branchesOfHeroesQuest;
	Quest* threeStonesQuest;
	Item* spellBook;

	//Bool to check if player has completed tutorial battle.
	bool isFirstBattleDone;

public:
	//Constructors
	GameManager();
	GameManager(Player*, Map*);

	/*
	* Moves player in given direction enum
	*/
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

	//Quest getters and setters
	Quest* GetFirstQuest();
	Quest* GetBranchesQuest();
	Quest* GetThreeStonesQuest();

	void GameBattleManager(Player&); // Function that will manage how battles work and the interactions between the ATTACK, DEFLECT, and RUN actions
	UserInputValidation::Action ProcessEnemyTurn(int currentEnemyHealth, int startEnemyhealth);

	//Puzzles methods that the player will encounter.
	bool BranchesOfHerosPuzzle();
	bool ThreeStonesPuzzle();

	//Normalize string method
	void NormalizeString(string& input);
};

