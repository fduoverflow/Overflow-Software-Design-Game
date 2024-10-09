#pragma once
#include <iostream>
#include <string>
#include "Tile.h"
using namespace std;

/*
* Player class will hold variables relevant to the player.
* MovePlayer() methods exists to help readability of code when class is implemented.
* This helps remove try catch blocks which are needed when using SetPlayerLocation().
*/
class Player
{
	private: 
		string playerName;
		string outOfBoundsMessage = "\nThe player can not move to that location.\n";
		int playerHealth;
		Tile playerLocation;

	public:
		//Player Name Setter/Getter
		string GetPlayerName();
		void SetPlayerName(string name);

		//Player Health Setter/Getter
		int GetPlayerHealth();
		void SetPlayerHealth(int health);

		//Player Location Setter/Getter
		Tile GetPlayerLocation();
		void SetPlayerLocation(Tile location);

		//Move Player
		void MovePlayerNorth();
		void MovePlayerSouth();
		void MovePlayerEast();
		void MovePlayerWest();

		//Constructors for Player Class
		Player(string name, int health, Tile location);
		//To use until health aspect is implemented
		Player(string name, Tile location);
		Player();
};