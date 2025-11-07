#include "Player.h"

void Player::Move(int dir, int dist)
{
	if (dir == 1)
		Rect.y -= dist;
	if (dir == 2)
		Rect.x += dist;
	if (dir == 3)
		Rect.y += dist;
	if (dir == 4)
		Rect.x -= dist;
}
