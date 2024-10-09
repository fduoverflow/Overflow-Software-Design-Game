#include "Player.h"
using namespace std;

//Constructors
Player::Player(string name, int health, Tile &location)
{
	playerName = name;
	playerLocation = &location;
	playerHealth = health;
}
Player::Player(string name, Tile &location)
{
	playerName = name;
	playerLocation = &location;
	playerHealth = 0;
}
Player::Player(string name)
{
	playerName = name;
	playerLocation = new Tile();
	playerHealth = 0;
}
Player::Player()
{
	playerName = "";
	playerLocation = new Tile();
	playerHealth = 0;
}

//Player Location Setter/Getter
Map& Player::GetMap()
{
	return myMap;
}
Tile& Player::GetPlayerLocation()
{
	return *playerLocation;
}
void Player::SetPlayerLocation(Tile &location)
{
	playerLocation = &location;
}

//Move player methods. Checks for out of bounds.
void Player::MovePlayerNorth()
{
	try
	{
		SetPlayerLocation(GetPlayerLocation().GetNorthTile());
	}
	catch (int errCode)
	{
		if (errCode == 404)
			cout << outOfBoundsMessage;
	}
}
void Player::MovePlayerSouth()
{
	try
	{
		SetPlayerLocation(GetPlayerLocation().GetSouthTile());
	}
	catch (int errCode)
	{
		if (errCode == 404)
			cout << outOfBoundsMessage;
	}
}
void Player::MovePlayerEast()
{
	try
	{
		SetPlayerLocation(GetPlayerLocation().GetEastTile());
	}
	catch (int errCode)
	{
		if (errCode == 404)
			cout << outOfBoundsMessage;
	}
}
void Player::MovePlayerWest()
{
	try
	{
		SetPlayerLocation(GetPlayerLocation().GetWestTile());
	}
	catch (int errCode)
	{
		if (errCode == 404)
			cout << outOfBoundsMessage;
	}
}

//Player Name Setter/Getter
string Player::GetPlayerName()
{
	return playerName;
}
void Player::SetPlayerName(string name)
{
	playerName = name;
}

//Player Health Setter/Getter
int Player::GetPlayerHealth()
{
	return playerHealth;
}
void Player::SetPlayerHealth(int health)
{
	playerHealth = health;
}