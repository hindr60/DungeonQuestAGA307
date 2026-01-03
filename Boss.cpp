#include "Boss.h"
#include "DungeonGame.h"

extern Boss* ActiveBoss;
extern Goblin* ActiveGoblin;

// ====================================================================================
//                                 BOSS UPDATE FUNCTION
// ====================================================================================
// o This function handles the boss enemy's AI Behaviour
// o The boss will use A* pathfinding to chase the player across the room, recalculating its path at fixed intervals.
// o The movement is tile-based and controlled by the move timer to ensure the boss moves one tile at a time at a speed that can be changed.
//   In which I have marked out if changes need to be made. 

//used chatgpt here to help compile bits of code i had researched into the below:
void Boss::Update(double dt, DungeonGame* game)
{
	//safety checks
	if (!game) return;
	if (!alive) return;

	//prevents the boss from moving while combat is active
	if (game->InCombat) return;

	repathTimer -= dt;

	GridPos start{ tileX, tileY };
	GridPos goal{ game->Hero->playerTileX, game->Hero->playerTileY };

	if (repathTimer <= 0.0)
	{
		repathTimer = repathInterval;
		path = game->PF.FindPath(start, goal, game->RoomBlocked);
		pathIndex = 0;
	}

	//no valid path found
	if (path.empty()) return;

	//movement timer to control the boss speed
	moveTimer -= dt;
	if (moveTimer > 0.0)
		return;

	moveTimer = moveInterval;

	if (pathIndex < (int)path.size() && path[pathIndex].x == tileX && path[pathIndex].y == tileY)
		pathIndex++;

	if (pathIndex >= (int)path.size()) return;

	GridPos next = path[pathIndex];

	if (next.x < 0 || next.x >= RoomSize || next.y < 0 || next.y >= RoomSize)
		return;

	//prevents the boss from stepping onto the player's tile
	bool playerBlocking = (game->Hero->playerTileX == next.x && game->Hero->playerTileY == next.y);

	if (!playerBlocking && game->Tiles[next.x][next.y].Walkable)
	{
		tileX = next.x;
		tileY = next.y;
		UpdateRect(game->tileSizeX, game->tileSizeY);
		pathIndex++;

	}

	bool adjacent = 
		(abs(game->Hero->playerTileX - tileX) == 1 && game->Hero->playerTileY == tileY) ||
		(abs(game->Hero->playerTileY - tileY) == 1 && game->Hero->playerTileX == tileX);

	if (adjacent)
	{
		//had to add this line in so resolve combat doesn't crash and clears any existing goblin combat references
		ActiveGoblin = nullptr;

		game->InCombat = true;

		//player must have the sword to be able to fight the boss
		if (!game->SwordCollected)
		{
			SDL_Log("Collect the sword to fight the big guy!");
			game->InCombat = false;
			return;
		}

		ActiveBoss = this;
		SDL_Log("Boss combat has started!");
		SDL_Log("Press 1 to Attach, press 2 to Block, or press 3 to Counter.");

	}

}
	