#include "Enemy.h"

/*
* Default constructor
*/
Enemy::Enemy()
{
	name = "";
	health = 0;
	myItem = nullptr;
}

/*
* Initalize an Enemy with a name and HP value without an item drop.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp)
{
	name = n;
	health = hp;
	myItem = nullptr;
	icon = i;
}

/*
* Initalize an Enemy with a name and HP value with an item drop.
*/
Enemy::Enemy(string n, enemyDisplay i, int hp, Item* newItem)
{
	name = n;
	health = hp;
	myItem = newItem;
	icon = i;
}
Enemy::Enemy(string n, enemyDisplay i, int hp, Item* newItem, string attkName, int attkDmg, string enemyDesc)
{
	name = n;
	health = hp;
	myItem = newItem;
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	icon = i;
	enemyDescription = enemyDesc;
}
Enemy::Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg)
{
	name = n;
	health = hp;
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	icon = i;
}
Enemy::Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg, string enemyDesc)
{
	name = n;
	icon = i;
	health = hp;
	enemyAttack = attkName;
	enemyAttackDamage = attkDmg;
	enemyDescription = enemyDesc;
}


//Name getters and setters
string Enemy::GetName()
{
	return name;
}
void Enemy::SetName(string n)
{
	name = n;
}

//Health getters and setters
int Enemy::GetHealth()
{
	return health;
}
void Enemy::SetHealth(int hp)
{
	health = hp;
}

//Item Setter/Getters, passed by reference
Item* Enemy::GetItem()
{
	return myItem;
}
void Enemy::SetItem(Item* newItem)
{
	myItem = newItem;
}

string Enemy::GetEnemyAttack()
{
	return enemyAttack;
}

void Enemy::SetEnemyAttack(string e_attk)
{
	enemyAttack = e_attk;
}

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



//Icon getter
enemyDisplay Enemy::GetIcon() {
	return icon;
}