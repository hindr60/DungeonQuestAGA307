#pragma once
#include "DungeonGame.h"
#include <SDL3_image/SDL_image.h>

class GameCharacter
{
public:
	GameCharacter();
	~GameCharacter();
	SDL_Texture* Texture;
	SDL_FRect Rect;
	
};

