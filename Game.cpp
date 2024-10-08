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

    ConsoleColors::EnableColor();

    Chunk dummyChunk(VALID);

    ConsoleColors::SetColor(GREEN);
    dummyChunk.DisplayChunk();
    ConsoleColors::DisableColor();
	return 0;
}