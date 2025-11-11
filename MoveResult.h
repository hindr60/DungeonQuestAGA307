#pragma once
#include "Tile.h"
#include "GameCharacter.h"
#include "Enums.h"

class MoveResult
{
public: 
	MoveResult();
	MoveResult(Tile* n);
	~MoveResult();
	//deconstructor, destroys and cleans the script
	Tile* GetTile();
	void SetAction(MoveResultAction a);
	MoveResultAction GetAction();

private:
	MoveResultAction action;
	GameCharacter* character;
	Tile* tile;
};

