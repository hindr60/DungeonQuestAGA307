#include "Goblin.h"
#include "DungeonGame.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void Goblin::Update(double dt, DungeonGame* game)
{
	if (!game) return;

	moveTimer -= dt;

	if (moveTimer <= 0.0) 
	{

		moveTimer = moveInterval;

		int r = prevDir;
		while (r == prevDir)
		{
			r = std::rand() % 4;
		}

		prevDir = r;

		switch (r) 
		{
		case 0: dirX = 0; dirY = -1; break; //north direction
		case 1: dirX = 1; dirY = 0; break; //east direction
		case 2: dirX = 0; dirY = 1; break; //south direction
		case 3: dirX = -1; dirY = 0; break; //west direction
		}

		int nextX = tileX + dirX;
		int nextY = tileY + dirY;


		if (nextX >= 0 && nextX < RoomSize && nextY >= 0 && nextY < RoomSize && game->Tiles[nextX][nextY].Walkable)
		{
			tileX = nextX;
			tileY = nextY;
			UpdateRect(game->tileSizeX, game->tileSizeY);
		}
		else
		{
			dirX = 0;
			dirY = 0;
		}

	}

	
	
	
	//std::cout << "Goblin dt: " << dt << " | timer: " << moveTimer << "\n";
}
