#include "Tile.h"

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
	//this determines that the two colours are the same
	
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{

}
