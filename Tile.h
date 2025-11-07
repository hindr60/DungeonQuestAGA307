#pragma once
#include <SDL3/SDL.h>

class Tile
{

	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

	//this allows for us to compare two colours to then determine the actions after

public:
	bool Walkable;
	SDL_Texture* Texture;
	SDL_FRect Rect;
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[]);
	//we configure the colour, the direction and the texture the tile will use.



};

