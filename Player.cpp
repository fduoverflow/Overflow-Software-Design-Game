#include "Player.h"
using namespace std;

//Constructors
Player::Player(string name, int health, int tileX, int tileY)
{
	playerName = name;
	playerTileLocation[0] = tileX;
	playerTileLocation[1] = tileY;
	playerHealth = health;
	playerAttack = "Knuckle Sandwich"; // Initial player attack is just their fists (until they get the spellbook)
	playerAttackDamage = 2; // When player is initialized, any attack they have can only do 1 dmg
}
Player::Player()
{
	playerName = "";
	playerTileLocation[0] = 0;
	playerTileLocation[1] = 0;
	playerHealth = 0;
	playerAttack = "";
	playerAttackDamage = 2; // Default damage is 1
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

//Player Name Setter/Getter
string Player::GetPlayerName()
{
	return playerName;
}
void Player::SetPlayerName(string name)
{
	playerName = name;
}

// Player Icon Getter
wstring Player::GetPlayerIcon() {
	return playerIcon;
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

// Player Attack Name Setter/Getter
string Player::GetPlayerAttack()
{
	return playerAttack;
}
void Player::SetPlayerAttack(string p_attk)
{
	playerAttack = p_attk;
}

// Player Attack Damage Setter/Getter
int Player::GetPlayerAttackDamage()
{
	return playerAttackDamage;
}
void Player::SetPlayerAttackDamage(int p_dmg)
{
	playerAttackDamage = p_dmg;
}