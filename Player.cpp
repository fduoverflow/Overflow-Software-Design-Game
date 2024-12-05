#include "Player.h"
using namespace std;

/*
* Player constructor that assigns a name, health, and tile x and y location.
*/
Player::Player(string name, int health, int tileX, int tileY)
{
	playerName = name;
	playerTileLocation[0] = tileY;
	playerTileLocation[1] = tileX;
	maxPlayerHealth = health;
	currentPlayerHealth = health;
	playerAttack = "Knuckle Sandwich"; // Initial player attack is just their fists (until they get the spellbook)
	playerAttackDamage = 2; // When player is initialized, any attack they have can only do 2 dmg
	evasiveness = 0;
	weapon = nullptr;
	hat = nullptr;
	body = nullptr;
}
/*
* Default Player constructor.
*/
Player::Player()
{
	playerName = "";
	playerTileLocation[0] = 0;
	playerTileLocation[1] = 0;
	maxPlayerHealth = 0;
	currentPlayerHealth = 0;
	playerAttack = "";
	playerAttackDamage = 1; // Default damage is 1
	evasiveness = 0;
	weapon = nullptr;
	hat = nullptr;
	body = nullptr;
}

//Player Location Setters/Getters
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

//Player Health Setters/Getters
int Player::GetPlayerHealth()
{
	return currentPlayerHealth;
}
int Player::GetPlayerMaxHealth()
{
	return maxPlayerHealth;
}
void Player::SetPlayerMaxHealth(int health)
{
	maxPlayerHealth = health;
}
void Player::SetPlayerHealth(int health)
{
	currentPlayerHealth = health;
}

/*
* Heal player by the passed amount.
* Caps healing to not go above max health.
*/
void Player::HealPlayer(int val)
{
	if (val >= 0)			//Check to make sure passed val is not negative.
	{
		currentPlayerHealth += val;
		if (currentPlayerHealth > maxPlayerHealth)
			currentPlayerHealth = maxPlayerHealth;
	}
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

//Player evasiveness setter/getter;
int Player::GetPlayerEvade()
{
	return evasiveness;
}
void Player::SetPlayerEvade(int val)
{
	evasiveness = val;
}

//Equipment Setters/Getters
Item* Player::GetEquippedWeapon()
{
	return weapon;
}
Item* Player::GetEquippedHat()
{
	return hat;
}
Item* Player::GetEquippedBody()
{
	return body;
}
void Player::SetEquippedWeapon(Item* newItem)
{
	weapon = newItem;
}
void Player::SetEquippedHat(Item* newItem)
{
	hat = newItem;
}
void Player::SetEquippedBody(Item* newItem)
{
	body = newItem;
}