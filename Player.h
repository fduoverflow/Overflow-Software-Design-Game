#pragma once
#include <iostream>
#include <string>
#include "Tile.h"
#include "Map.h"
#include "Chunk.h"
#include "UserInputValidation.h"
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
		string movingChunkMessage = "\nMoving to new Chunk.\n";
		int playerHealth;
		int playerChunkLoc[2];		//Player chunk location stored as row and column
		Tile* playerLocation;		//Tile that the player is located on
		Map myMap;

	public:
		//Player Name Setter/Getter
		string GetPlayerName();
		void SetPlayerName(string name);

		//Player Health Setter/Getter
		int GetPlayerHealth();
		void SetPlayerHealth(int health);

		//Player Location Setter/Getter
		Map& GetMap();
		Tile& GetPlayerLocation();
		void SetPlayerLocation(Tile &location);
		int GetPlayerChunkLocationX();
		int GetPlayerChunkLocationY();
		void SetPlayerChunkLocation(int r, int c);

		//Move Player
		void MovePlayerTo(UserInputValidation::Move dir);

		/*
		void MovePlayerNorth();
		void MovePlayerSouth();
		void MovePlayerEast();
		void MovePlayerWest();
		*/

		//Constructors for Player Class
		Player(string name, int health, Tile &location);
		//To use until health aspect is implemented
		Player(string name, Tile &location);
		Player(string name, Map map);
		Player();
};