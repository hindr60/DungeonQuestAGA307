#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
//array of textures go here

const static std::string path_Hero = "Textures/Hero_sword.png";
enum Direction{North, East, South, West};
const static int RoomSize = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];

private:
	float tileSizeX;
	float tileSizeY;
};

