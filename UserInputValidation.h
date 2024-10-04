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
	private:
		string playerMove;
		string playerAction;

		// WASD is player movement - W (up), A (left), S (down), D (right)
		enum Move
		{
			W,A,S,D
		};
		// Constants for player actions
		enum Action
		{
			RULES, INV, MAP
		};

	public:
		// Call Setters inside check functions in .cpp
		// Only set player moves/actions to valid ones
		bool CheckValidMove(string playerMove);
		bool CheckValidAction(string playerAction);

		// Player Move Setter/Getters
		Move GetPlayerMove();
		void SetPlayerMove();

		// Player Actions Setter/Getters
		Action GetPlayerAction();
		void SetPlayerAction(); 
};

