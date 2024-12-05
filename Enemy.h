#pragma once
#include "Item.h"
#include <string>

using namespace std;

//Display stuct to hold an emoji and size
struct enemyDisplay {
    wstring emoji;
    int size;
};

/*
* Enemy class will be used to define combat opponents for the player to fight against.
*/
class Enemy
{
private:
    // Name and health used for display and combat.
    string name;
    int health;

    // Starting health of the enemy.
    int startingHealth;

    // Item that the enemy drops on defeat.
    Item* myItem;

    // Enemy Attack Name and Attack Damage.
    string enemyAttack;
    int enemyAttackDamage;

    // Enemy icon.
    enemyDisplay icon;

    // Enemy description.
    string enemyDescription;

    // Unique ID for each enemy.
    int enemyID;

public:
    // Constructors
    Enemy();
    Enemy(string n, enemyDisplay i, int hp);
    Enemy(string n, enemyDisplay i, int hp, Item* newItem);
    Enemy(string n, enemyDisplay i, int hp, Item* newItem, string attkName, int attkDmg, string enemyDesc);
    Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg, string enemyDesc);
    Enemy(string n, enemyDisplay i, int hp, Item* newItem, string attkName, int attkDmg);
    Enemy(string n, enemyDisplay i, int hp, string attkName, int attkDmg);

    // Name getters and setters.
    string GetName();
    void SetName(string n);

    // Health getters and setters.
    int GetHealth();
    void SetHealth(int hp);

    // Starting health getter.
    int GetStartingHealth(); // New getter for starting health.

    // Item Setter/Getters, passed by reference.
    Item* GetItem();
    void SetItem(Item* newItem);

    // Enemy Attack Name/Attack Damage Setters/Getters.
    string GetEnemyAttack();
    void SetEnemyAttack(string);
    int GetEnemyAttackDamage();
    void SetEnemyAttackDamage(int);

    // Enemy Description Setters/Getters -- player needs to know who they are fighting.
    string GetEnemyDescription();
    void SetEnemyDescription(string);

    // Display getter.
    enemyDisplay GetIcon();
};
