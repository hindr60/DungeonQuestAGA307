#include "Boss.h"
#include "DungeonGame.h"

void Boss::Update(double dt, DungeonGame* game)
{
	if (!game) return;
	if (!alive) return;

	repathTimer -= dt;

	GridPos start{ tileX, tileY };
	GridPos goal{ game->Hero->playerTileX, game->Hero->playerTileY };

	if (repathTimer <= 0.0 || path.empty() || pathIndex >= (int)path.size())
	{
		repathTimer = repathInterval;

		path = game->PF.FindPath(start, goal, game->RoomBlocked);
		pathIndex = 0;
	}

	if (path.empty()) return;

	if (pathIndex < (int)path.size() && path[pathIndex].x == tileX && path[pathIndex].y == tileY)
		pathIndex++;

	if (pathIndex >= (int)path.size()) return;

	GridPos next = path[pathIndex];

	bool playerBlocking = (game->Hero->playerTileX == next.x && game->Hero->playerTileY == next.y);

	if (!playerBlocking && game->Tiles[next.x][next.y].Walkable)
	{
		tileX = next.x;
		tileY = next.y;
		UpdateRect(game->tileSizeX, game->tileSizeY);
		pathIndex++;

	}
}
	