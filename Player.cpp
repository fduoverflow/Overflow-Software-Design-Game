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
void Player::SetPlayerChunkLocation(int r, int c)
{
	playerChunkLoc[0] = r;
	playerChunkLoc[1] = c;
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
		{
			//Check if player can move to a valid adjacent Chunk
			if (playerChunkLoc[0] > 0)
			{
				//Move player to valid chunk while keeping relative Tile position
				if (myMap.GetChunkAt(playerChunkLoc[0] - 1, playerChunkLoc[1]).getType() == VALID)
				{
					cout << movingChunkMessage;
					playerChunkLoc[0]--;
					SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(15, playerLocation->GetColumn()));
				}
				else
				{
					cout << outOfBoundsMessage;
				}
			}
			else
				cout << outOfBoundsMessage;
		}
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
		{
			//Check if player can move to a valid adjacent Chunk
			if (playerChunkLoc[0] < 4)
			{
				//Move player to valid chunk while keeping relative Tile position
				if (myMap.GetChunkAt(playerChunkLoc[0] + 1, playerChunkLoc[1]).getType() == VALID)
				{
					cout << movingChunkMessage;
					playerChunkLoc[0]++;
					SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(0, playerLocation->GetColumn()));
				}
				else
				{
					cout << outOfBoundsMessage;
				}
			}
			else
				cout << outOfBoundsMessage;
		}
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
		{
			//Check if player can move to a valid adjacent Chunk
			if (playerChunkLoc[1] < 6)
			{
				//Move player to valid chunk while keeping relative Tile position
				if (myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1] + 1).getType() == VALID)
				{
					cout << movingChunkMessage;
					playerChunkLoc[1]++;
					SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(playerLocation->GetRow(), 0));
				}
				else
				{
					cout << outOfBoundsMessage;
				}
			}
			else
				cout << outOfBoundsMessage;
		}
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
		{
			//Check if player can move to a valid adjacent Chunk
			if (playerChunkLoc[1] > 0)
			{
				//Move player to valid chunk while keeping relative Tile position
				if (myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1] - 1).getType() == VALID)
				{
					cout << movingChunkMessage;
					playerChunkLoc[1]--;
					SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(playerLocation->GetRow(), 15));
				}
				else
				{
					cout << outOfBoundsMessage;
				}
			}
			else
				cout << outOfBoundsMessage;
		}
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