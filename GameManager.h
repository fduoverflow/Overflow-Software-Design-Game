#pragma once
#include "Player.h"
#include "Map.h"
#include "UserInputValidation.h"
#include "Tile.h"
#include "Quest.h"

class GameManager
{
private:
	Player* player;
	Map* map;
	Quest* firstQuest;
public:
	//Constructors
	GameManager();
	GameManager(Player*, Map*);

	/*
	* Moves player in given direction enum
	*/
	void MovePlayer(UserInputValidation::Move);

	/*
	* Returns the Tile address at player's current location.
	*/
	Tile& GetPlayerLocationTile();
	void TutorialQuest(); // First Quest -- Retrieve spellbook from house after talking to Scrummius (owl)

};

