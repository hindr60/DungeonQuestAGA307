#pragma once
#include "GameCharacter.h"
#include "Enums.h"
#include "Tile.h"


class DungeonGame;

class Player : public GameCharacter
{
public:
	int playerTileX = 1;
	int playerTileY = 5;
	void Move(Direction dir);
	bool CurrentTileAllowsVoidMovement(Direction dir, DungeonGame* game);
	void SetPositionForNewRoom(Direction dir, int GridSizeX, int GridSizeY, float tileSizeX, float tileSizeY); //sets player's new position in the new room


};

