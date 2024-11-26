#pragma once
#include <iostream>
#include <string>
#include "UserInputValidation.h"
#include "Item.h"
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
	int maxPlayerHealth;
	int currentPlayerHealth;
	int playerChunkLoc[2];			// Player chunk location stored as row and column
	int playerTileLocation[2];		// Tile that the player is located on
	string playerAttack;			// Player Attack Name
	int playerAttackDamage;			// Player Attack damage number
	int evasiveness;				// Player Evasiveness number
	wstring playerIcon = L"🧙‍♂️";

	//Equipped items
	Item* weapon;
	Item* hat;
	Item* body;

public:
	//Player Name Setter/Getter
	string GetPlayerName();
	void SetPlayerName(string name);

	// Player Icon Getter
	wstring GetPlayerIcon();

	//Player Health Setter/Getter
	int GetPlayerHealth();
	int GetPlayerMaxHealth();
	void SetPlayerMaxHealth(int health);
	void SetPlayerHealth(int health);
	void HealPlayer(int val);

	//Player Attacks Setters/Getters
	string GetPlayerAttack();
	void SetPlayerAttack(string playerAttack);
	int GetPlayerAttackDamage();
	void SetPlayerAttackDamage(int playerAttackDamage);

	//Player evasiveness setter/getter;
	int GetPlayerEvade();
	void SetPlayerEvade(int val);


	//Player Location Setter/Getter
	int GetPlayerLocationX();
	int GetPlayerLocationY();
	void SetPlayerLocation(int tileX, int tileY);
	int GetPlayerChunkLocationX();
	int GetPlayerChunkLocationY();
	void SetPlayerChunkLocation(int r, int c);

	//Equipment Setters/Getters.
	Item* GetEquippedWeapon();
	Item* GetEquippedHat();
	Item* GetEquippedBody();
	void SetEquippedWeapon(Item* newItem);
	void SetEquippedHat(Item* newItem);
	void SetEquippedBody(Item* newItem);

	//Constructors for Player Class
	Player(string name, int health, int tileX, int tileY);
	Player();
};