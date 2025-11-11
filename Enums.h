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


