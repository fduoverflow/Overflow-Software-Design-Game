#pragma once
#include <iostream>
#include <string>
#include "UserInputValidation.h"
using namespace std;

/*
* Player class will hold variables relevant to the player.
*/
class Player
{
private:
	string playerName;
	string outOfBoundsMessage = "\nThe player can not move to that location.\n";
	string movingChunkMessage = "\nMoving to new Chunk.\n";
	int playerHealth;
	int playerChunkLoc[2];			// Player chunk location stored as row and column
	int playerTileLocation[2];		// Tile that the player is located on
	string playerAttack;			// Player Attack Name
	int playerAttackDamage;			// Player Attack damage number

public:
	//Player Name Setter/Getter
	string GetPlayerName();
	void SetPlayerName(string name);

	//Player Health Setter/Getter
	int GetPlayerHealth();
	void SetPlayerHealth(int health);

	//Player Attacks Setters/Getters
	string GetPlayerAttack();
	void SetPlayerAttack(string playerAttack);

	int GetPlayerAttackDamage();
	void SetPlayerAttackDamage(int playerAttackDamage);

	//Player Location Setter/Getter
	int GetPlayerLocationX();
	int GetPlayerLocationY();
	void SetPlayerLocation(int tileX, int tileY);
	int GetPlayerChunkLocationX();
	int GetPlayerChunkLocationY();
	void SetPlayerChunkLocation(int r, int c);

	//Constructors for Player Class
	Player(string name, int health, int tileX, int tileY);
	Player();
};