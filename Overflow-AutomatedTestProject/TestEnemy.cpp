#include "pch.h"
#include "../Enemy.cpp"
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Player.h"
#include "../Enemy.h"
#include "../Item.h"
#include "../Map.h"

// use this class to test enemies

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OverflowTestEnemy
{
	TEST_CLASS(TestEnemy)
	{
	public:
		TEST_METHOD(TestPlayerMovesAndAttacksEnemy)
		{
			
			
			Player player("Hero", 100, 5, 5);
			player.SetPlayerAttackDamage(10); // Player attack damage is set to 10
			player.SetPlayerAttack("Sword Slash"); // Player attack set to "Sword Slash"

			// Enemy starts at position (7, 7)
			Enemy enemy("Dust Golem", { L"🪨", 1 }, 20);

			// Simulate movement toward the enemy
			while (player.GetPlayerLocationX() != 7 || player.GetPlayerLocationY() != 7)
			{
				if (player.GetPlayerLocationX() < 7)
				{
					player.SetPlayerLocation(player.GetPlayerLocationX() + 1, player.GetPlayerLocationY());
				}
				else if (player.GetPlayerLocationY() < 7)
				{
					player.SetPlayerLocation(player.GetPlayerLocationX(), player.GetPlayerLocationY() + 1);
				}
			}

			// Simulate attacking the enemy
			while (enemy.GetHealth() > 0)
			{
				int currentHealth = enemy.GetHealth();
				int newHealth = currentHealth - player.GetPlayerAttackDamage();
				enemy.SetHealth(newHealth > 0 ? newHealth : 0); // Reduce enemy health to zero or more
			}

			// Player reached the enemy and defeated it
			Assert::AreEqual(7, player.GetPlayerLocationX(), L"Player did not reach the correct X location");
			Assert::AreEqual(7, player.GetPlayerLocationY(), L"Player did not reach the correct Y location");
			Assert::AreEqual(0, enemy.GetHealth(), L"Enemy did not die after sufficient attacks");
		}
	};
}
