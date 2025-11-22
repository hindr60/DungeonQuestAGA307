#pragma once
class Goblin
{
public:
	int tileX
	int tileY

	SDL_Texture* Texture;
	SDL_FRect Rect;

	Goblin(int x, int y, float tileSizeX, float tileSizeY, SDL_Texture* texture)
		: tileX(x), tileY(y), Texture(texturee)\
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

