#pragma once
#include <SDL3/SDL.h>

class Pickup
{
public:
	int tileX;
	int tileY;

	bool collected = false;

	SDL_Texture* Texture = nullptr;
	SDL_FRect Rect;

	Pickup(int x, int y, float tileSizeX, float tileSizeY, SDL_Texture* text) : tileX(x), tileY(y), Texture(text)
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
		Rect.w = tileSizeX;
		Rect.h = tileSizeY;
	}

	void Render(SDL_Renderer* renderer)
	{
		if (!collected && Texture)
		{
			SDL_RenderTexture(renderer, Texture, nullptr, &Rect);
		}
	}
};

