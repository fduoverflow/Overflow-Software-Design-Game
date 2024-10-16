#pragma once
#include <string>
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
			RULES, INV, MAP
		};
		// Call Setters inside check functions in .cpp
		// Only set player moves/actions to valid ones
		bool CheckValidMove(Move);
		bool CheckValidAction(Action);
		bool MoveChecker(string);
		

		// Player Move Setter/Getters
		Move GetPlayerMove();
		void SetPlayerMove(Move move);

		// Player Actions Setter/Getters
		Action GetPlayerAction();
		void SetPlayerAction(Action); 

		// Check length of user input-- movement is only WASD
		bool CheckMoveInputLength(string);

		Move CharToMove(char);

	private:
		Move playerMove;
		string playerAction;
};

