
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "DungeonGame.h"
#include "Player.h"
#include "Goblin.h"
#include "Tile.h"
#include "Enums.h"


static Uint64 now;
static Uint64 last;

using namespace std;

const int resX = 1000;
const int resY = 1000;
const int GridSizeX = 10;
const int GridSizeY = 10;
const float TileSize = resY / GridSizeX;
//const = makes an integer unchangeable, in this case the resolution

static const char* heroPath = "Textures/Hero_no_sword.png";
static SDL_Texture* heroTexture;

static const int TileWidth = resX / 10;
static const int TileHeight = resY / 10;




 /* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

static const char* ProjectName = "JMC Starter Project";

static DungeonGame* Game;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{     
    SDL_SetAppMetadata(ProjectName, "1.0", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE; 
    }

    if (!SDL_CreateWindowAndRenderer(ProjectName, resX, resY, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Game = new DungeonGame(TileSize, TileSize);
    Game->LoadTextures(renderer);
    Game->LoadRoom(DungeonGame::RoomGrid[1][1].c_str());


    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void PlayerMove(DungeonGame* Game, Direction dir) 
{
    Tile* targetTile = Game->GetNeighbour(Game->Hero->playerTileX, Game->Hero->playerTileY, dir);
    MoveResult move(targetTile);

    if (targetTile)
    {
        if (targetTile->Walkable)
        {
            move.SetAction(MoveResultAction::MoveOK);
            Game->Hero->Move(dir);
            Game->Hero->Rect.x = Game->Hero->playerTileX * Game->tileSizeX;
            Game->Hero->Rect.y = Game->Hero->playerTileY * Game->tileSizeY;
        }
        else
        {
            move.SetAction(MoveResultAction::Blocked);
        }
    }
    else
    {
    //void tiles need to be handled here
        if (Game->Hero->CurrentTileAllowsVoidMovement(dir, Game)) 
        {
            move.SetAction(MoveResultAction::MoveOK);
            Game->LoadNextRoom(dir);
            Game->Hero->SetPositionForNewRoom(dir, RoomSize, RoomSize, Game->tileSizeX, Game->tileSizeY);
        } 
        else {
            move.SetAction(MoveResultAction::Blocked);
        }
    }
}
  
/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    
    
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        // keyboard events
        // used CHATGPT to help clean up this section   
        if (event->key.scancode == SDL_SCANCODE_W) 
        {
            PlayerMove(Game, Direction::North);           
        }
        if (event->key.scancode == SDL_SCANCODE_S)
        {
            PlayerMove(Game, Direction::South);
            
        }
        if (event->key.scancode == SDL_SCANCODE_A)
        {

            PlayerMove(Game, Direction::West);
            
        }
        if (event->key.scancode == SDL_SCANCODE_D)
        {
            PlayerMove(Game, Direction::East);
        }

    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
   
    
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{    
    last = now;
    now = SDL_GetPerformanceCounter();
    double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
    Game->Update(deltaTime);



    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);


    for (int y = 0; y < RoomSize; y++) 
    {
        for (int x = 0; x < RoomSize; x++) 
        {
            Tile& tile = Game->Tiles[x][y];
            if (tile.Texture != nullptr)
                SDL_RenderTexture(renderer, tile.Texture, nullptr, &tile.Rect);
        }

    }

    SDL_RenderTexture(renderer, Game->Hero->Texture, NULL, &Game->Hero->Rect);

    SDL_RenderPresent(renderer);  /* put it all on the screen! */
    return SDL_APP_CONTINUE;  /* carry on with the program! */

}


  

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    delete Game;
    /* SDL will clean up the window/renderer for us. */
}
    