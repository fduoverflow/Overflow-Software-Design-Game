#include "Player.h"
using namespace std;

//Constructors
Player::Player(string name, int health, Tile location)
{
	playerName = name;
	playerLocation = location;
	playerHealth = health;
}
Player::Player(string name, Tile location)
{
	playerName = name;
	playerLocation = location;
	playerHealth = 0;
}
Player::Player()
{
	playerName = "";
	playerLocation = Tile();
	playerHealth = 0;
}

//Player Location Setter/Getter
Tile Player::GetPlayerLocation()
{
	return playerLocation;
}
void Player::SetPlayerLocation(Tile location)
{
	playerLocation = location;
}

//Move player methods. Checks for out of bounds.
void Player::MovePlayerNorth()
{
	try
	{
		SetPlayerLocation(playerLocation.GetNorthTile());
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
		SetPlayerLocation(playerLocation.GetSouthTile());
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
		SetPlayerLocation(playerLocation.GetEastTile());
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
		SetPlayerLocation(playerLocation.GetWestTile());
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