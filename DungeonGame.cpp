#include "DungeonGame.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int currentRoomIndex = 0;

//combat setup
Goblin* ActiveGoblin = nullptr;

//using this will prevent circular dependancy errors
std::vector<Goblin*> Goblins;
SDL_Texture* goblinTexture = nullptr;

//to cleanly spawn the goblins in every room, we will use arrays
struct GoblinSpawn 
{
	int x;
	int y;
};

//using 3 sets of 3 to be in line with our room amount
static std::vector<GoblinSpawn> GoblinRoomPositions[3][3] =
{
	{
		{ {7, 4} },
		{ {2, 4} },
		{ {8, 5} }
	},
	{
		{ {3, 2} },
		{ {3, 4} },
		{ {4, 8} }
	},
	{
		{ {6, 1} },
		{ {4, 6} },
		{ {1, 2} }
	},

};

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

	goblinTexture = IMG_LoadTexture(renderer, path_Goblin.c_str());
	SDL_SetTextureScaleMode(goblinTexture, SDL_SCALEMODE_NEAREST);

	boneTexture = IMG_LoadTexture(renderer, "Textures/Tile_carpet_bones.bmp");
	SDL_SetTextureScaleMode(boneTexture, SDL_SCALEMODE_NEAREST);

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


	for (Goblin* g : Goblins) 
	{
		delete g;
	}
	Goblins.clear();

	for (const GoblinSpawn& spawn : GoblinRoomPositions[currentGridY][currentGridX])
	{
		Goblin* g = new Goblin(
			spawn.x,
			spawn.y,
			tileSizeX,
			tileSizeY,
			goblinTexture
		);

		Goblins.push_back(g);
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

 void DungeonGame::Update(double dt)
 {
	 for (Goblin* g : Goblins)
		 g->Update(dt, this);
 }

 //sets a position for the goblin and updates as it moves around the map
 bool DungeonGame::GoblinPosition(int x, int y)
 {
	 for (Goblin* g : Goblins)
	 {
		 if (g->tileX == x && g->tileY == y)
			 return true;
	 }
	 return false;
 }

 void DungeonGame::ResolveCombat(CombatChoice player)
 {
	 CombatChoice goblin = (CombatChoice)(std::rand() % 3);

	 CombatOutcome result;
	 std::string resultText;

	 if (player == goblin)
	 {
		 result = CombatOutcome::Draw;
		 resultText = "Draw!";
	 }
	 else if (
		 (player == CombatChoice::Attack && goblin == CombatChoice::Counter) ||
		 (player == CombatChoice::Defend && goblin == CombatChoice::Attack) ||
		 (player == CombatChoice::Counter && goblin == CombatChoice::Defend)
		 )
	 {
		 result = CombatOutcome::PlayerWin;
		 resultText = "Player wins!";
	 }
	 else
	 {
		 result = CombatOutcome::GoblinWin;
		 resultText = "Goblin wins!";
	 }
		 
	 std::cout << "Combat outcome: " << resultText << std::endl;

	 if (result == CombatOutcome::Draw)
	 {
		 SDL_Log("Draw! Choose from the options again: 1 is Attack, 2 is Defend, 3 is Counter");
		 return;
	 }

	 InCombat = false;

	 if (result == CombatOutcome::PlayerWin)
	 {
		 SDL_Log("Congrats! You have defeated the Goblin!");
		 //then the goblin gets removed here
		 int gx = ActiveGoblin->tileX;
		 int gy = ActiveGoblin->tileY;

		 for (int i = 0; i < Goblins.size(); i++)
		 {
			 if (Goblins[i] == ActiveGoblin)
			 {
				 delete Goblins[i];
				 Goblins.erase(Goblins.begin() + i);
				 break;
			 }
		 }

		 Tile& tile = Tiles[gx][gy];
		 tile.Texture = boneTexture;
		 tile.type = TileType::Floor;

		 ActiveGoblin = nullptr;
		 InCombat = false;
		 return;

	 }
	 else
	 {
		 SDL_Log("You lost, try again!");
		 //then the player moves back to the original position at the start of the game.
	 }

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

 
