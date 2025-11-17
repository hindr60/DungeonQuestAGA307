#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"

const static std::string path_Hero = "Textures/Hero_sword.png";



//const static std::string path_Map = "Data/Rooms/Room05.bmp";


extern int currentRoomIndex;
const static int RoomSize = 10;



class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();

	SDL_Texture* textures[2];
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	void LoadNextRoom(Direction dir);

	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];


	Tile* GetNeighbour(int currentX, int currentY, Direction dir);
	float tileSizeX;
	float tileSizeY;
	int maxX = 9;
	int maxY = 9;
	//Rect.x = playerTileX * tileSizeX;
	//Rect.y = playerTileY * tileSizeY;
	int currentGridX = 1;
	int currentGridY = 1;

	static const int Grid_Size = 3;
	static const std::string RoomGrid[Grid_Size][Grid_Size];
};