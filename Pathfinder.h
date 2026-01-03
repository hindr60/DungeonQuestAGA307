#pragma once
#include <vector>

struct GridPos 
{
	int x = 0;
	int y = 0;

	bool operator==(const GridPos& other) const { return x == other.x && y == other.y; }
};

class Pathfinder
{
public:
	std::vector<GridPos> FindPath(
		GridPos start,
		GridPos goal,
		const std::vector<std::vector<bool>>& blocked
	);
};

