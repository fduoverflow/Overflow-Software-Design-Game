#pragma once
#include "Player.h"
#include "Map.h"
#include "UserInputValidation.h"
#include "Tile.h"

class GameManager
{
private:
	Player* player;
	Map* map;
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
};

