#pragma once
#include "Item.h"
#include <string>

using namespace std;

/*
* Enemy class will be used to define combat opponents for the player to fight against.
*/
class Enemy
{
	private:
		//Name and health used for display and combat.
		string name;
		int health;

		//Item that the enemy drops on defeat
		Item* myItem;
												//May want to consider adding an Attack/Defense/EnemyAction object to allow enemies to have actions that can do varying amounts of damage in a variety of types.

		// Enemy Attack Name and Attack Damage
		string enemyAttack;
		int enemyAttackDamage;
	public:
		//Constructors
		Enemy();
		Enemy(string n, int hp);
		Enemy(string n, int hp, Item* newItem);
		Enemy(string n, int hp, Item* newItem, string attkName, int attkDmg);

		//Name getters and setters
		string GetName();
		void SetName(string n);

		//Health getters and setters
		int GetHealth();
		void SetHealth(int hp);

		//Item Setter/Getters, passed by reference
		Item* GetItem();
		void SetItem(Item* newItem);

		// Enemy Attack Name/Attack Damage Setters/Getters
		string GetEnemyAttack();
		void SetEnemyAttack(string);

		int GetEnemyAttackDamage();
		void SetEnemyAttackDamage(int);
};

