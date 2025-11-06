#include "DungeonGame.h"


DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{

	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;

}

DungeonGame::~DungeonGame()
{
	delete this->Hero;

}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	//Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);

	this->Hero->Rect.x = 0;
	this->Hero->Rect.y = 0;
	this->Hero->Rect.w = tileSizeX;
	this->Hero->Rect.h = tileSizeY;
	//determines the hero rect size

}

 void DungeonGame::LoadRoom(const char* file)
{
	SDL_Surface* surface = SDL_LoadBMP(file);
	//loads the bitmap and stores the surface into "surface"

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	//this gets the surface format
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	//stores the value into a format, Uint8 = unsigned integer of 8 bit (the smallest piece of data that we can use)
	SDL_Color col;

	for (int y = 0; y < surface->h; y++) 
	{
		for (int x = 0; x < surface->w; x++) 
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			//look into this
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);
			//this compares the pixel colour to the RGB values, giving information about the surface.
			//col now contains pixel colour at position x,y.

			//Now configure the tile at x,y with col

			//this->Tiles[x][y].Configure(col, x, y, tileSizeX, add in the array of textures)

		}
	}


}
