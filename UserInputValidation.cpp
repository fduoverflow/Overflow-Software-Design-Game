#include "UserInputValidation.h"
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;
/*
Checks if the player made a valid move
Valid Moves include: W,A,S,D for (up, left, down, and right, respectively)
*/
bool UserInputValidation::CheckValidMove(Move playerMove)
{
	{
		switch (playerMove)
		{
			// Check if player move is WASD, if yes, return true
			// Input by user SHOULD NOT be case sensitive
		case Move::W:
		case Move::A:
		case Move::S:
		case Move::D:
			//SetPlayerMove(playerMove);
			return true;
			//If the player's move is not WASD, then return false
		case Move::X:
		default:
			return false;
		}
	}
}
void UserInputValidation::SetPlayerMove(Move move)
{
	playerMove = move;
}
UserInputValidation::Move UserInputValidation::GetPlayerMove()
{
	return playerMove;
}
void UserInputValidation::SetPlayerAction(Action action)
{
	playerAction = action;
}

UserInputValidation::Action UserInputValidation::GetPlayerAction()
{
	return playerAction;
}

// Treating the enemy actions the same way we would treat a player's action
// Enemy actions are for battles and are limited to ATTACK and DEFLECT

void UserInputValidation::SetEnemyAction(Action e)
{
	enemyAction = e;
}
UserInputValidation::Action UserInputValidation::GetEnemyAction()
{
	return enemyAction;
}


bool UserInputValidation::CheckMoveInputLength(string move)
{
	// Checks that the input move is one character (WASD)
	if (move.length() != 1)
	{
		return false;
	}
	return true;
}

bool UserInputValidation::CheckValidAction(Action action)
{
	//Check if action matches proper Action enum
	switch (action)
	{
	case Action::MAP:
	case Action::PICKUP:
	case Action::HEALTH:
	case Action::INV:
	case Action::INSPECT:
	case Action::TALK:
	case Action::ATTACK:
	case Action::DEFLECT:
	case Action::RUN:
	case Action::LEAVE:
	case Action::RULES:
	case Action::ENTER:
	case Action::USE:
		return true;
	case Action::ERROR:
	default:
		return false;
	}
}

UserInputValidation::Move UserInputValidation::CharToMove(char input)
{
	// returns the character (WASD) as a Move enum
	input = toupper(input);
	switch (input)
	{
		case 'W': return Move::W;
		case 'A': return Move::A;
		case 'S': return Move::S;
		case 'D': return Move::D;
		default: return Move::X;
	}
}

// Normalize the user input
//   remove white space & change to upper case
//   modifies the user input string in place
void UserInputValidation::NormalizeString(string& input) {
	transform(input.begin(), input.end(), input.begin(), ::toupper);
	input = std::regex_replace(input, std::regex("^\\s+|\\s+$"), "");
}

UserInputValidation::Action UserInputValidation::StringToAction(string input)
{

	NormalizeString(input);
	if (input == "MAP")
	{
		return Action::MAP;
	}
	else if (input == "PICKUP")
	{
		return Action::PICKUP;
	}
	else if (input == "INSPECT")
	{
		return Action::INSPECT;
	}
	else if (input == "HEALTH")
	{
		return Action::HEALTH;
	}
	else if (input == "INV")
	{
		return Action::INV;
	}
	else if (input == "TALK")
	{
		return Action::TALK;
	}
	else if (input == "ATTACK")
	{
		return Action::ATTACK;
	}
	else if (input == "DEFLECT")
	{
		return Action::DEFLECT;
	}
	else if (input == "RUN")
	{
		return Action::RUN;
	}
	else if (input == "LEAVE")
	{
		return Action::LEAVE;
	}
	else if (input == "ENTER")
	{
		return Action::ENTER;
	}
	else if (input == "RULES")
	{
		return Action::RULES;
	}
	else if (input == "USE")
	{
		return Action::USE;
	}
	else
	{
		return Action::ERROR;
	}
}

// Will check 
bool UserInputValidation::MoveChecker(string userInput)
{
	Move move;
	bool lengthCheck = CheckMoveInputLength(userInput);
	//Check that the length of the input is only 1 char long
	if (lengthCheck)
	{
		move = CharToMove((char)(userInput[0]));
		bool validMove = CheckValidMove(move);
		if (validMove)
		{
			SetPlayerMove(move);
			return true;
		}
		else
		{
			//cout << "Invalid Input! Please enter WASD!\n";
			// X move for invalid
			SetPlayerMove(move);
			return false;
		}
	}
	return false;
}

bool UserInputValidation::ActionChecker(string userInput)
{
	Action action;
	// Convert user input to usable Action ENUM
	action = StringToAction(userInput);

	// Check if the action input is valid
	bool validAction = CheckValidAction(action);
	if (validAction)
	{
		//Player action is set to valid action
		SetPlayerAction(action);
		return true;
	}
	else
	{
		//cout << "Please enter a valid action!\n";
		//Set Action to ERROR if player inputs an invalid action
		SetPlayerAction(action);
		return false;
	}
}

// Refactored version of UserInputValidation
//   removes need for CheckValidAction (and the duplication)
//   hardcodes ERROR to signify an invalid input (bad)
//    - better might be to use the original stringToAction() & have an error parameter updated

bool UserInputValidation::ActionChecker(string userInput, bool refactor)
{
	Action action;
	// Convert user input to usable Action ENUM
	action = StringToAction(userInput);
	SetPlayerAction(action);
	return (action != Action::ERROR);   // if action == error, returns false, otherwise returns true
}