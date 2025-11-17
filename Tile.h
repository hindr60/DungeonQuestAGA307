#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "Enums.h"


class DungeonGame;

class Tile
{

	static bool CompareColours(const SDL_Color& a, const SDL_Color& b, int tolerance = 20);

	//this allows for us to compare two colours to then determine the actions after

public:
	bool Walkable;
	TileType type;
	SDL_Texture* Texture = nullptr;
	SDL_FRect Rect;
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[]);
	//we configure the colour, the direction and the texture the tile will use.
	DoorDirection Door = DoorDirection::None;
	bool CurrentTileAllowsVoidMovement(int playerX, int playerY, Direction dir, DungeonGame* game);

};

