#include <iostream>
#include "ConsoleColors.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"

using namespace std;

int main() {
	cout << "Overflow Game!" << endl;
	/*
	//TEST CASE FOR MOVECHECKER
	string userInput;
	cout << "Enter test value for input validation:";
	cin >> userInput;
	UserInputValidation valid;
	
	valid.MoveChecker(userInput);
	*/

    ConsoleColors::EnableColor();

    Chunk dummyChunk(VALID);

    ConsoleColors::SetColor(GREEN);
    dummyChunk.DisplayChunk();
    ConsoleColors::DisableColor();
	return 0;
}