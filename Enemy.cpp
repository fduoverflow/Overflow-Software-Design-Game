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
Enemy::Enemy(string n, int hp)
{
	name = n;
	health = hp;
	myItem = nullptr;
}

/*
* Initalize an Enemy with a name and HP value with an item drop.
*/
Enemy::Enemy(string n, int hp, Item* newItem)
{
	name = n;
	health = hp;
	myItem = newItem;
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