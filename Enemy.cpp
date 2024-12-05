#include "Enemy.h"

/*
* Default constructor
*/
Enemy::Enemy()
{
	name = "";
	health = 0;
	startingHealth = 0; // Initialize startingHealth
	myItem = nullptr;
}

/*
* Initialize an Enemy with a name and HP value without an item drop.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp)
{
	name = n;
	health = hp;
	startingHealth = hp; // Set startingHealth
	myItem = nullptr;
	icon = i;
}

/*
* Initialize an Enemy with a name and HP value with an item drop.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp, Item* newItem)
{
	name = n;
	health = hp;
	startingHealth = hp; // Set startingHealth
	myItem = newItem;
	icon = i;
}

/*
* Initialize an Enemy with a name, HP, item drop, attack name, attack damage, and description.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp, Item* newItem, string attkName, int attkDmg, string enemyDesc)
{
	name = n;
	health = hp;
	startingHealth = hp; // Set startingHealth
	myItem = newItem;
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	icon = i;
	enemyDescription = enemyDesc;
}

/*
* Initialize an Enemy with a name, HP, attack name, and attack damage.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg)
{
	name = n;
	health = hp;
	startingHealth = hp; // Set startingHealth
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	icon = i;
}

/*
* Initialize an Enemy with a name, HP, attack name, attack damage, and description.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg, string enemyDesc)
{
	name = n;
	icon = i;
	health = hp;
	startingHealth = hp; // Set startingHealth
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	enemyDescription = enemyDesc;
}

// Name getters and setters
string Enemy::GetName()
{
	return name;
}
void Enemy::SetName(string n)
{
	name = n;
}

// Health getters and setters
int Enemy::GetHealth()
{
	return health;
}
void Enemy::SetHealth(int hp)
{
	health = hp;
}

// Getter for starting health
int Enemy::GetStartingHealth()
{
	return startingHealth;
}

// Item Setter/Getters, passed by reference
Item* Enemy::GetItem()
{
	return myItem;
}
void Enemy::SetItem(Item* newItem)
{
	myItem = newItem;
}

// Get/Set Enemy Attack Name
string Enemy::GetEnemyAttack()
{
	return enemyAttack;
}
void Enemy::SetEnemyAttack(string e_attk)
{
	enemyAttack = e_attk;
}

// Get/Set Enemy Attack Damage
int Enemy::GetEnemyAttackDamage()
{
	return enemyAttackDamage;
}
void Enemy::SetEnemyAttackDamage(int e_dmg)
{
	enemyAttackDamage = e_dmg;
}

// Get/Set the description of the enemy so the player may know who they are fighting
string Enemy::GetEnemyDescription()
{
	return enemyDescription;
}
void Enemy::SetEnemyDescription(string desc)
{
	enemyDescription = desc;
}

// Icon getter
enemyDisplay Enemy::GetIcon()
{
	return icon;
}
