#include "DungeonGame.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{

	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
	textures[0] = nullptr;
	textures[1] = nullptr;

}

DungeonGame::~DungeonGame()
{
	delete this->Hero;

}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("Textures/Tile_carpet_base.bmp");
	this->textures[0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
	//if (!textures[0]) SDL_Log("Failed to load Tile_carpet_base.bmp!");

	surface = SDL_LoadBMP("Textures/Tile_Grey_base.bmp");
	this->textures[1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
	//if (!textures[1]) SDL_Log("Failed to load Tile_Grey_base.bmp!");

	this->Hero = new Player;
	//Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);
	this->Hero->Rect.x = 3 * tileSizeX;
	this->Hero->Rect.y = 1 * tileSizeY;
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

			this->Tiles[x][y].Configure(col, (float)x, (float)y, tileSizeX, this->textures);

		}
	}

	SDL_DestroySurface(surface);


	 //to double check if the map is being read from the files
	 /*
	 SDL_Surface* surface = SDL_LoadBMP(file);
	 if (!surface) {
		 SDL_Log("Failed to load BMP: %s", SDL_GetError());
		 return;
	 }
	 SDL_Log("Loaded BMP successfully!");
	 SDL_Log("Width: %d, Height %d", surface->w, surface->h);

	 const SDL_PixelFormatDetails* fmt = SDL_GetPixelFormatDetails(surface->format);
	 int bpp = SDL_BYTESPERPIXEL(surface->format);
	 SDL_Color col;

	 for (int y = 0; y < 3 && y < surface->h; y++) {
		 for (int x = 0; x < 3 && x < surface->w; x++) {
			 Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			 Uint32 pixelValue = 0;
			 memcpy(&pixelValue, pixel, bpp);

			 Uint8 r = (Uint8)((pixelValue & fmt->Rmask) >> fmt->Rshift);
			 Uint8 g = (Uint8)((pixelValue & fmt->Gmask) >> fmt->Gshift);
			 Uint8 b = (Uint8)((pixelValue & fmt->Bmask) >> fmt->Bshift);

			 if (fmt->Rbits < 8) r = (r * 255) / ((1 << fmt->Rbits) - 1);
			 if (fmt->Gbits < 8) g = (g * 255) / ((1 << fmt->Gbits) - 1);
			 if (fmt->Bbits < 8) b = (b * 255) / ((1 << fmt->Bbits) - 1);

			 col.r = r;
			 col.g = g;
			 col.b = b;

			 if (x < 3 && y < 3)
				 SDL_Log("Pixel (%d, %d): R=%d G=%d B=%d", x, y, col.r, col.g, col.b);

			 this->Tiles[x][y].Configure(col, (float)x, (float)y, tileSizeX, this->textures);

			 
		 }
	 }

	 SDL_DestroySurface(surface);
	 */
}

 Tile* DungeonGame::NorthNeighbour(int currentX, int currentY, Direction dir)
 {
	 if (dir == Direction::North && currentY > 0) {
		 return &Tiles[currentX][currentY - 1];
	 }
	 return nullptr;
 }

 Tile* DungeonGame::EastNeighbour(int currentX, int currentY, Direction dir)
 {
	 if (dir == Direction::East && currentX > 0) {
		 return &Tiles[currentX + 1][currentY];
	 }
	 return nullptr;
 }

 Tile* DungeonGame::SouthNeighbour(int currentX, int currentY, Direction dir)
 {
	 if (dir == Direction::South && currentY > 0) {
		 return &Tiles[currentX][currentY + 1];
	 }
	 return nullptr;
 }

 Tile* DungeonGame::WestNeighbour(int currentX, int currentY, Direction dir)
 {
	 if (dir == Direction::West && currentY > 0) {
		 return &Tiles[currentX - 1][currentY];
	 }
	 return nullptr;
 }

 
