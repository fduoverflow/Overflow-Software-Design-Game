#pragma once
#include <string>
#include "Map.h"
using namespace std;

/*
This class will check if user input is valid
will check different types of user input and 
check that the input is valid according to game rules
*/
class UserInputValidation
{
	// movement
	// player actions - view map, view health, view rules

	public:
		// WASD is player movement - W (up), A (left), S (down), D (right)
		// Set to their ASCII Values
		enum class Move
		{
			W = 'W',
			A = 'A',
			S = 'S',
			D = 'D',

			//For invalid inputs
			X = 'X'
		};
		// Constants for player actions
		enum class Action
		{
			// Common player actions - Error occurs when invalid input is entered 
			RULES, INV, MAP, PICKUP, INSPECT, ERROR, HEALTH, TALK, ATTACK, DEFLECT, RUN, LEAVE, ENTER, USE, EQUIP
		};
		// Call Setters inside check functions in .cpp
		// Only set player moves/actions to valid ones
		bool CheckValidMove(Move);
		bool CheckValidAction(Action);
		bool MoveChecker(string);
		bool ActionChecker(string);
		bool ActionChecker(string, bool);
		

		// Player Move Setter/Getters
		Move GetPlayerMove();
		void SetPlayerMove(Move move);

		// Player Actions Setter/Getters
		Action GetPlayerAction();
		void SetPlayerAction(Action);
		
		// Enemy Actions Setter/Getters
		Action GetEnemyAction();
		void SetEnemyAction(Action);

		// Check length of user input-- movement is only WASD
		bool CheckMoveInputLength(string);

		// Changing characters/string to respective enum type
		// WASD movement is char
		// Actions (i.e MAP) are string
		Move CharToMove(char);
		Action StringToAction(string);

	private:
		Move playerMove;
		Action playerAction;
		Action enemyAction;
		void NormalizeString(string& input);  // helper function to remove white space & convert to a standard case, input is updated in-place
};

