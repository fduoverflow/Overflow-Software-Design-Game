#pragma once
#include "Player.h"
#include "Map.h"
#include "UserInputValidation.h"

class GameManager
{
private:
	Player* player;
	Map* map;
public:
	GameManager();
	GameManager(Player*, Map*);
	void MovePlayer(UserInputValidation::Move);
};

