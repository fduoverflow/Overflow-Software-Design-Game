#include "UserInputValidation.h"
#include <iostream>
#include <algorithm>
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
UserInputValidation::Action UserInputValidation::StringToAction(string input)
{
	//convert user input to uppercase
	transform(input.begin(), input.end(), input.begin(), ::toupper);
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