#include "MoveResult.h"

MoveResult::MoveResult()
{

}

MoveResult::MoveResult(Tile* n)
{
	action = MoveResultAction::MoveOK;
	tile = n;
	character = nullptr;
}

MoveResult::~MoveResult()
{

}

Tile* MoveResult::GetTile()
{
	//check if the player can step on the movement tile in here

	return nullptr;
}

void MoveResult::SetAction(MoveResultAction a)
{
	//this part allows you to see what happens when a player moves onto the tile, for eg taking damage, blocked, pickup, etc

}

MoveResultAction MoveResult::GetAction()
{
	//this decides whether to actually move the player
	return MoveResultAction();
}
