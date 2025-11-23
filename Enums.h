#pragma once

enum Direction 
{ 
	North, 
	East, 
	South, 
	West 
};
//if enums are needed, in the class type #include "Enums.h"

enum MoveResultAction 
{
	Undefined = -1, 
	//this int value is at -1, enums by default start at tha value 0
	Blocked = 0,
	MoveOK = 1,
	Fight = 2,
	LoadNewRoom = 3,
};

enum TileType 
{
	Floor,
	Wall,
	NorthDoor,
	EastDoor,
	SouthDoor,
	WestDoor
};

enum class DoorDirection 
{
	None,
	North,
	South,
	East,
	West
};

enum class CombatChoice { Attack, Defend, Counter };
enum class CombatOutcome { PlayerWin, GoblinWin, Draw };



