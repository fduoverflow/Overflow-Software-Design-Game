#include "GameManager.h"

//Constructors.
GameManager::GameManager() 
{
	firstQuest = new Quest();
}

GameManager::GameManager(Player* p, Map* m) {
	player = p;
	map = m;
	firstQuest = new Quest();
}

/*
* Move player to adjacent Tile in given direction.
*/
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

/*
* Returns Tile object at current player location.
*/
Tile& GameManager::GetPlayerLocationTile()
{
	return map->GetChunkAt(player->GetPlayerChunkLocationX(), player->GetPlayerChunkLocationY()).GetTileAt(player->GetPlayerLocationX(), player->GetPlayerLocationY());
}

/*
* Initializes first quest by updating start bool and providing quest components.
*/
void GameManager::InitilizeTutorialQuest()
{
	//Setting the first quest to start as true -- Talking to Scrummius will trigger this
	firstQuest->SetQuestStart(true);

	// Tutorial Quest Name, Description, and Overall Objective
	string name = "Tutorial Quest- Retrieve the Spellbook from the house!";
	string desc = "Before you can set off on your quest, you must retrieve back your spellbook so you may harness your magic powers once again!";
	string objective = "Go to the house and gather the spellbook!";

	// Spell book is a key item that is gathered after the first quest-- not a weapon for now
	spellBook = new Item("Scrummius' Spell Book","book desc",Item::Type::KEY, 0);
	firstQuest = new Quest(name, desc, objective, spellBook);

	// Place the spellbook in location -- door: (7,7) and (7,8)
	// map->GetChunkAt(0, 1).GetTileAt(5,7).SetItem(spellBook);
	map->GetChunkAt(0, 0).GetTileAt(5, 4).SetItem(spellBook);
}

/*
* Update fist quest flags to complete status and update NPC dialogue.
*/
void GameManager::TutorialQuestComplete()
{
	//String to hold large npc dialogue. May move to somewhere else later.
	string scrummiusDialogue = 
		"That was fast. I bet yooou just wanted that book for yourself. Either way, now yooou must get to the city if you want tooo make it to Lord Vallonious‘ lair. Like that’s gonna happen. First, get throoough the forest by heading east. It will lead yooou straight there!";
	firstQuest->SetQuestStart(false);
	firstQuest->SetQuestComplete(true);
	map->GetChunkAt(0, 0).GetTileAt(5, 2).GetNPC()->SetDialogue(scrummiusDialogue);
}

//First Quest getters and setters
Quest* GameManager::GetFirstQuest()
{
	return firstQuest;
}
void GameManager::SetFirstQuest(Quest* newQuest)
{
	firstQuest = newQuest;
}
