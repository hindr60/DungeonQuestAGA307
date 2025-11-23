#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
class Goblin
{
public:
	int tileX;
	int tileY;

	SDL_Texture* Texture;
	SDL_FRect Rect;

	Goblin(int x, int y, float tileSizeX, float tileSizeY, SDL_Texture* texture)
		: tileX(x), tileY(y), Texture(texture)
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
		Rect.w = tileSizeX;
		Rect.h = tileSizeY;
	}

	void Render(SDL_Renderer* renderer) 
	{
		SDL_RenderTexture(renderer, Texture, nullptr, &Rect);
	}

};

