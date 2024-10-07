#include "UserInputValidation.h"
using namespace std;
/*
Checks if the player made a valid move
Valid Moves include: W,A,S,D for (up, left, down, and right, respectively)
*/
bool UserInputValidation::CheckValidMove(Move playerMove)
{
	switch (playerMove)
	{
		// Check if player move is WASD, if yes, return true
		case Move::W:
		case Move::A:
		case Move::S:
		case Move::D:
			SetPlayerMove(playerMove);
			return true;
		//If the player's move is not WASD, then return false
		default:
			return false;
	}
}
void UserInputValidation::SetPlayerMove(Move move)
{
	playerMove = (char)move;
}

bool CheckValidAction(string playerAction)
{
	return false;
}

// Player Move Setter/Getters