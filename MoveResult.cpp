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

	return nullptr;
}

void MoveResult::SetAction(MoveResultAction a)
{
}

MoveResultAction MoveResult::GetAction()
{
	return MoveResultAction();
}
