#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Player.h"
#include "../Player.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OverflowTestPlayerClass
{
    TEST_CLASS(TestPlayer)
    {
    public:
        TEST_METHOD(TestPlayerInitialization)
        {
            // Arrange
            Player player("Hero", 100, 5, 5);

            
            Assert::AreEqual(std::string("Hero"), player.GetPlayerName(), L"Player name mismatch");
            Assert::AreEqual(100, player.GetPlayerHealth(), L"Player health mismatch");
            Assert::AreEqual(5, player.GetPlayerLocationX(), L"Player X location mismatch");
            Assert::AreEqual(5, player.GetPlayerLocationY(), L"Player Y location mismatch");
        }
        TEST_METHOD(TestPlayerMovement)
        {
            // Arrange
            Player player("Hero", 100, 5, 5);

            // Act
            player.SetPlayerLocation(10, 15);

            // Assert
            Assert::AreEqual(10, player.GetPlayerLocationX(), L"Player X location mismatch after movement");
            Assert::AreEqual(15, player.GetPlayerLocationY(), L"Player Y location mismatch after movement");
        }
        
        TEST_METHOD(TestPlayerHealthUpdate)
        {
            // Arrange
            Player player("Hero", 100, 5, 5);

            // Act
            player.SetPlayerHealth(80); // Update health to 80

            // Assert
            Assert::AreEqual(80, player.GetPlayerHealth(), L"Player health mismatch after update");
        }

    };
}
