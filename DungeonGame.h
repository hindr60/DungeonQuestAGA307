#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"
#include "Goblin.h"
#include "Pickup.h"


class Pickup;

const static std::string path_Hero = "Textures/Hero_no_sword.png";
const static std::string path_Goblin = "Textures/Enemy_orc_blue.png";

//const static std::string path_Map = "Data/Rooms/Room05.bmp";

//combat system setup
extern Goblin* ActiveGoblin;

extern int currentRoomIndex;
const static int RoomSize = 10;

//extern tells the system that this code exists elsewhere
extern std::vector<Goblin*> Goblins;
extern SDL_Texture* goblinTexture;

class DungeonGame
{
public:
	bool InCombat = false;

	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();

	Pickup* SwordPickup = nullptr;
	int swordX = 5;
	int swordY = 5;

	SDL_Texture* textures[2];
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	void LoadNextRoom(Direction dir);

	void Update(double dt);
	bool GoblinPosition(int x, int y);

	SDL_Renderer* Renderer = nullptr;

	bool SwordCollected = false;
	SDL_Texture* swordTexture = nullptr;
	SDL_Texture* heroSwordTexture = nullptr;

	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];

	void ResolveCombat(CombatChoice player);
	SDL_Texture* boneTexture = nullptr;

	//to give each room its own "state
	struct RoomState
	{
		bool GoblinAlive[3];
	};

	RoomState roomStates[3][3];

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