#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Pathfinder.h"

class DungeonGame;

class Boss
{
public:
	int tileX = 0;
	int tileY = 0;

	bool alive = true;
	
	std::vector<GridPos> path;
	int pathIndex = 0;

	double repathTimer = 0.0;
	double repathInterval = 0.5;

	double moveTimer = 0.0;
	double moveInterval = 0.60;

	SDL_Texture* Texture = nullptr;
	SDL_FRect Rect{};

	Boss(int x, int y, float tileSizeX, float tileSizeY, SDL_Texture* texture)
		: tileX(x), tileY(y), Texture(texture)
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
		Rect.w = tileSizeX;
		Rect.h = tileSizeY;
	}

	void UpdateRect(float tileSizeX, float tileSizeY)
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_RenderTexture(renderer, Texture, nullptr, &Rect);
	}

	void Update(double dt, DungeonGame* game);
	
};

