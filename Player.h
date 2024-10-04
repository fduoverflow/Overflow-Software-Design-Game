#pragma once
#include <string>
#include "Tile.h"
using namespace std;

/*
Player class will hold variables relevant to the player.
*/
class Player
{
	private: 
		string playerName;
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

		//Constructors for Player Class
		Player(string name, int health, Tile location);
		//To use until health aspect is implemented
		Player(string name, Tile location);
};

