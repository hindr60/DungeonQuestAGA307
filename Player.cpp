#include "Player.h"
#include "DungeonGame.h"
#include <iostream>

void Player::Move(Direction dir)
{
//to make the player move by grid tile, we need to change int dir and int dist to pixelx and pixely
	
	if (dir == Direction::North)
		playerTileY --;

	if (dir == Direction::East)
		playerTileX ++;

	if (dir == Direction::South)
		playerTileY ++;

	if (dir == Direction::West)
		playerTileX --;

	// to log the player tile coordinates --
	// std::cout << "Player coordinates: (" << playerTileX << ", " << playerTileY << ")\n";

}

bool Player::CurrentTileAllowsVoidMovement(Direction dir, DungeonGame* game)
{
	Tile* nextTile = game->GetNeighbour(playerTileX, playerTileY, dir);
	//if (!nextTile) return true;
	return (nextTile == nullptr);
}

void Player::SetPositionForNewRoom(Direction dir, int GridSizeX, int GridSizeY, float tileSizeX, float tileSizeY)
{
	switch (dir)
	{
	case Direction::North: playerTileY = GridSizeY -1; break;
	case Direction::South: playerTileY = 0; break;
	case Direction::East: playerTileX = 0; break;
	case Direction::West: playerTileX = GridSizeX - 1; break;
	}

	Rect.x = playerTileX * tileSizeX;
	Rect.y = playerTileY * tileSizeY;
}


