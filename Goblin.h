#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>


//forward decleration to avoid circular dependancies
class DungeonGame;

class Goblin
{
public:
	int tileX;
	int tileY;

	int dirX = 0;
	int dirY = 0;
	int prevDir = -1;

	double moveTimer = 0.0;
	double moveInterval = 2.0;
	
	SDL_Texture* Texture;
	SDL_FRect Rect;	

	Goblin(int x, int y, float tileSizeX, float tileSizeY, SDL_Texture* texture)
		: tileX(x), tileY(y), dirX(0), dirY(0), moveInterval(2.0), moveTimer((double)(std::rand() % 2000) / 1000.0), Texture(texture)
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
		Rect.w = tileSizeX;
		Rect.h = tileSizeY;

		moveTimer = (double)(std::rand() % 2000) / 1000.0;
	}

	~Goblin() = default;

	

	void Update(double dt, DungeonGame* game);

	void UpdateRect(float tileSizeX, float tileSizeY) 
	{
		Rect.x = tileX * tileSizeX;
		Rect.y = tileY * tileSizeY;
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_RenderTexture(renderer, Texture, nullptr, &Rect);
	}

};

