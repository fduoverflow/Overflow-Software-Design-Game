#include "Player.h"
using namespace std;

//Constructors
Player::Player(string name, int health, int tileX, int tileY)
{
	playerName = name;
	playerTileLocation[0] = tileX;
	playerTileLocation[1] = tileY;
	playerHealth = health;
}
Player::Player()
{
	playerName = "";
	playerTileLocation[0] = 0;
	playerTileLocation[1] = 0;
	playerHealth = 0;
}

//Player Location Setter/Getter
int Player::GetPlayerLocationX()
{
	return playerTileLocation[1];
}
int Player::GetPlayerLocationY()
{
	return playerTileLocation[0];
}
int Player::GetPlayerChunkLocationX() {
	return playerChunkLoc[1];
}
int Player::GetPlayerChunkLocationY() {
	return playerChunkLoc[0];
}
void Player::SetPlayerLocation(int tileX, int tileY)				//Only set to a tile that is instantiated to avoid a nullptr error
{
	playerTileLocation[0] = tileY;
	playerTileLocation[1] = tileX;
}
void Player::SetPlayerChunkLocation(int x, int y)
{
	playerChunkLoc[0] = y;
	playerChunkLoc[1] = x;
}

//Move player methods. Checks for out of bounds.
//void Player::MovePlayerTo(UserInputValidation::Move dir)
//{
//	switch (dir)
//	{
//		case UserInputValidation::Move::W:
//			try
//			{
//				SetPlayerLocation(GetPlayerLocation().GetNorthTile());
//			}
//			catch (int errCode)
//			{
//				if (errCode == 404)
//				{
//					//Check if player can move to a valid adjacent Chunk
//					if (playerChunkLoc[0] > 0)
//					{
//						//Move player to valid chunk while keeping relative Tile position
//						if (myMap.GetChunkAt(playerChunkLoc[0] - 1, playerChunkLoc[1]).getType() == VALID)
//						{
//							cout << movingChunkMessage;
//							playerChunkLoc[0]--;
//							SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(15, playerLocation->GetColumn()));
//						}
//						else
//						{
//							cout << outOfBoundsMessage;
//						}
//					}
//					else
//						cout << outOfBoundsMessage;
//				}
//			}
//			break;
//		case UserInputValidation::Move::S:
//			try
//			{
//				SetPlayerLocation(GetPlayerLocation().GetSouthTile());
//			}
//			catch (int errCode)
//			{
//				if (errCode == 404)
//				{
//					//Check if player can move to a valid adjacent Chunk
//					if (playerChunkLoc[0] < 4)
//					{
//						//Move player to valid chunk while keeping relative Tile position
//						if (myMap.GetChunkAt(playerChunkLoc[0] + 1, playerChunkLoc[1]).getType() == VALID)
//						{
//							cout << movingChunkMessage;
//							playerChunkLoc[0]++;
//							SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(0, playerLocation->GetColumn()));
//						}
//						else
//						{
//							cout << outOfBoundsMessage;
//						}
//					}
//					else
//						cout << outOfBoundsMessage;
//				}
//			}
//			break;
//		case UserInputValidation::Move::D:
//			try
//			{
//				SetPlayerLocation(GetPlayerLocation().GetEastTile());
//			}
//			catch (int errCode)
//			{
//				if (errCode == 404)
//				{
//					//Check if player can move to a valid adjacent Chunk
//					if (playerChunkLoc[1] < 6)
//					{
//						//Move player to valid chunk while keeping relative Tile position
//						if (myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1] + 1).getType() == VALID)
//						{
//							cout << movingChunkMessage;
//							playerChunkLoc[1]++;
//							SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(playerLocation->GetRow(), 0));
//						}
//						else
//						{
//							cout << outOfBoundsMessage;
//						}
//					}
//					else
//						cout << outOfBoundsMessage;
//				}
//			}
//			break;
//		case UserInputValidation::Move::A:
//			try
//			{
//				SetPlayerLocation(GetPlayerLocation().GetWestTile());
//			}
//			catch (int errCode)
//			{
//				if (errCode == 404)
//				{
//					//Check if player can move to a valid adjacent Chunk
//					if (playerChunkLoc[1] > 0)
//					{
//						//Move player to valid chunk while keeping relative Tile position
//						if (myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1] - 1).getType() == VALID)
//						{
//							cout << movingChunkMessage;
//							playerChunkLoc[1]--;
//							SetPlayerLocation(myMap.GetChunkAt(playerChunkLoc[0], playerChunkLoc[1]).GetTileAt(playerLocation->GetRow(), 15));
//						}
//						else
//						{
//							cout << outOfBoundsMessage;
//						}
//					}
//					else
//						cout << outOfBoundsMessage;
//				}
//			}
//			break;
//	}
//}

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