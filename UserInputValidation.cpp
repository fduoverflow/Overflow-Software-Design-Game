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
		return true;
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
			cout << "Invalid Input! Please enter WASD!\n";
			// X move for invalid
			SetPlayerMove(move);
			return false;
		}
	}
	return false;
}


bool UserInputValidation::ActionChecker(string userInput)
{
	// Convert user input to usable Action ENUM
	Action action = StringToAction(userInput);

	// Check if the action input is valid
	bool validMove = CheckValidAction(action);
	if (validMove)
	{
		//Player action is set to valid action
		SetPlayerAction(action);
		return true;
	}
	else
	{
		return false;
	}
}

//Can scale to include other actions
void UserInputValidation::ProcessAction(string userInput, Map worldMap)
{
	// Function assumes that action is valid
	Action action = StringToAction(userInput);

	// Display the worldMap when the user enters the map command
	switch (action)
	{
	case Action::MAP:
		worldMap.DisplayMap();
		break;
	/*
	case Action::PICKUP:
		if (myPlayer.GetPlayerLocation().GetItem().GetType() != Item::Type::EMPTY)
		{
			myPlayer.GetPlayerLocation().PickUpItem();
			cout << "Item was picked up.\n";
		}
		break;
	case Action::INSPECT:
		if (myPlayer.GetPlayerLocation().GetItem().GetType() != Item::Type::EMPTY)
		{
			cout << "Item description: " + myPlayer.GetPlayerLocation().GetItem().GetDescription() + "\n";
		}
		break; */
	} 
}