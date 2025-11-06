#pragma once
#include "GameCharacter.h"

class Player : public GameCharacter
{
public:
	void Move(int dir, int dist);

};

