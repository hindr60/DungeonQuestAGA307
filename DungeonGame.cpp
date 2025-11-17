#include "DungeonGame.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>


int currentRoomIndex = 0;

const std::string DungeonGame::RoomGrid[Grid_Size][Grid_Size] =
{
	{"Data/Rooms/Room01.bmp", "Data/Rooms/Room02.bmp", "Data/Rooms/Room03.bmp",},
	{"Data/Rooms/Room02.bmp", "Data/Rooms/Room01.bmp", "Data/Rooms/Room04.bmp",},
	{"Data/Rooms/Room04.bmp", "Data/Rooms/Room05.bmp", "Data/Rooms/Room03.bmp",}
};

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{

	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;

	textures[0] = nullptr;
	textures[1] = nullptr;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

	this->Hero->Rect.x = 0 * tileSizeX;
	this->Hero->Rect.y = 4 * tileSizeY;
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
}

 void DungeonGame::LoadNextRoom(Direction dir)
 {
	 // if you want it randomised: int nextRoomIndex = std::rand() % 9;

	 switch (dir)
	 {
	 case Direction::North: 
		 if (currentGridY > 0) currentGridY--; 
		 break;

	 case Direction::South: 
		 if (currentGridY < Grid_Size - 1) currentGridY++;
		 break;

	 case Direction::East: 
		 if (currentGridX < Grid_Size - 1) currentGridX++;
		 break;

	 case Direction::West: 
		 if (currentGridX > 0) currentGridX--;
		 break;

	 }

	 const std::string& nextRoom = RoomGrid[currentGridY][currentGridX];
	 LoadRoom(nextRoom.c_str());

	 Hero->SetPositionForNewRoom(dir, RoomSize, RoomSize, tileSizeX, tileSizeY);
 }

 //used chatgpt to help create a clean neighbouring system
 Tile* DungeonGame::GetNeighbour(int currentX, int currentY, Direction dir)
 {
	 switch (dir) 
	 {
	 case Direction::North:
		 if (currentY > 0) 
			 return &Tiles[currentX][currentY - 1];
		 break;

	 case Direction::East:
		 if (currentX < RoomSize - 1) 
			 return &Tiles[currentX + 1][currentY];
		 break;

	 case Direction::South:
		 if (currentY < RoomSize - 1) 
			 return &Tiles[currentX][currentY + 1];
		 break;

	 case Direction::West:
		 if (currentX > 0) 
			 return &Tiles[currentX - 1][currentY];
		 break;

	 }
	 return nullptr; // for out of bounds
 }

 
