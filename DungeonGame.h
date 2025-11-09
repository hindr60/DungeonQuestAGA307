#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
//array of textures go here



const static std::string path_Hero = "Textures/Hero_sword.png";
const static std::string path_Map = "Data/Rooms/Room05.bmp";
enum Direction{North, East, South, West};


const static int RoomSize = 10;


class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();

	SDL_Texture* textures[2];
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);

	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];

	Tile* NorthNeighbour(int currentX, int currentY, Direction dir);
	Tile* EastNeighbour(int currentX, int currentY, Direction dir);
	Tile* SouthNeighbour(int currentX, int currentY, Direction dir);
	Tile* WestNeighbour(int currentX, int currentY, Direction dir);
	

private:
	float tileSizeX;
	float tileSizeY;
};