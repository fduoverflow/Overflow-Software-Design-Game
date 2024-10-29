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
	Item* spellBook;
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

	/*
	* Returns the Tile address at player's current location.
	*/
	Tile& GetPlayerLocationTile();
	void InitilizeTutorialQuest(); // First Quest -- Retrieve spellbook from house after talking to Scrummius (owl)
	void TutorialQuestComplete();

	//Quest getters and setters
	Quest* GetFirstQuest();
	void SetFirstQuest(Quest* newQuest);		//May not need but it's here just in case.

};

