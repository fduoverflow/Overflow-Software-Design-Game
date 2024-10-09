#include <iostream>
#include "ConsoleColors.h"
#include "Map.h"
#include "Player.h"
#include "Chunk.h"
#include "Tile.h"
#include "UserInputValidation.h"
#include "UserInterface.h"

using namespace std;

int main() 
{
	cout << "Overflow Game!" << endl;
	
	//Initialize Player then place them in middle of starting chunk
	Player myPlayer("Shakir");
	myPlayer.SetPlayerLocation(myPlayer.GetMap().GetChunkAt(1, 1).GetTileAt(7, 7));
	myPlayer.SetPlayerChunkLocation(1, 1);

	return 0;
}