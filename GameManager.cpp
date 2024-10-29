#include "GameManager.h"


GameManager::GameManager() {

}

GameManager::GameManager(Player* p, Map* m) {
	player = p;
	map = m;
}

void GameManager::MovePlayer(UserInputValidation::Move dir) {
	int x = 0, y = 0;	// Transposition magnitude per direction
	switch (dir)
	{
	case UserInputValidation::Move::W:
		y--;
		break;
	case UserInputValidation::Move::S:
		y++;
		break;
	case UserInputValidation::Move::D:
		x++;
		break;
	case UserInputValidation::Move::A:
		x--;
		break;
	}
	int posX = player->GetPlayerLocationX(), posY = player->GetPlayerLocationY();

	// Check where the player would be if they moved to the new location, and if that location would be valid
	int newPosX = posX + x, newPosY = posY + y;
	int newChunkX = player->GetPlayerChunkLocationX() + x, newChunkY = player->GetPlayerChunkLocationY() + y;
	// If new move is within the chunk bounds, check that the new tile is valid and move there
	if (-1 < newPosX && newPosX < 16 && -1 < newPosY && newPosY < 16) {
		// Update the tile that the player is on
		player->SetPlayerLocation(newPosX, newPosY);
	}
	// If new move is not within chunk bounds
	else if (newChunkX > -1 && newChunkY > -1 && newChunkX < map->GetNumColumns() && newChunkY < map->GetNumRows() && map->GetChunkAt(newChunkX, newChunkY).getType() == VALID) {
		player->SetPlayerChunkLocation(newChunkX, newChunkY);
		player->SetPlayerLocation((newPosX % 16 + 16) % 16, (newPosY % 16 + 16) % 16);
	}
	else
		cout << "sorry pookie can't move here :(";
}

Tile& GameManager::GetPlayerLocationTile()
{
	return map->GetChunkAt(player->GetPlayerChunkLocationX(), player->GetPlayerChunkLocationY()).GetTileAt(player->GetPlayerLocationX(), player->GetPlayerLocationY());
}

void GameManager::Display() {
	map->Display(player->GetPlayerChunkLocationX(), player->GetPlayerChunkLocationY(), player->GetPlayerLocationX(), player->GetPlayerLocationY());
}