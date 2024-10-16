#include "UserInputValidation.h"
#include <iostream>
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

bool UserInputValidation::CheckMoveInputLength(string move)
{
	if (move.length() != 1)
	{
		return false;
	}
	return true;
}

UserInputValidation::Move UserInputValidation::CharToMove(char input)
{
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