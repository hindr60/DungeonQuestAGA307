#include "Tile.h"
#include "DungeonGame.h"

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{

	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
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

	if (CompareColours(color, black)) {
		Walkable = false;
		Texture = textures[1];
	}
	else if (CompareColours(color, white)) {
		Walkable = true;
		Texture = textures[0];
	}

}
