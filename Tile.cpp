#include "Tile.h"
#include "DungeonGame.h"
#include <cmath>

bool Tile::CompareColours(const SDL_Color& a, const SDL_Color& b, int tolerance)
{

	//return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
	return (abs(a.r - b.r) <= tolerance &&
		abs(a.g - b.g) <= tolerance &&
		abs(a.b - b.b) <= tolerance);
	//this determines that the two colours are the same
	
}


void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
	Rect.x = x * size;
	Rect.y = y * size;
	Rect.w = size;
	Rect.h = size;

	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };

	if (CompareColours(color, black, 10)) {
		Walkable = false;
		Texture = textures[1];
		//Texture = nullptr;
	}
	else if (CompareColours(color, white, 20)) {
		Walkable = true;
		Texture = textures[0];
	}
	else {
		Walkable = true;
		Texture = textures[0];
	}

}
