#include "Pathfinder.h"
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

static float Heuristic(const GridPos& a, const GridPos& b)
{
    return (float)(std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

struct Node
{
    float g = std::numeric_limits<float>::infinity();
    float h = 0.0f;
    int parentX = -1;
    int parentY = -1;
    bool hasParent = false;

    float f() const { return g + h; }
};

struct OpenRec
{
    int x, y;
    float f;
};

struct OpenRecCompare
{
    bool operator()(const OpenRec& a, const OpenRec& b) const
    {
        return a.f > b.f;
    }
};

std::vector<GridPos> Pathfinder::FindPath(GridPos start, GridPos goal, const std::vector<std::vector<bool>>& blocked)
{
    std::vector<GridPos> empty;

    if (blocked.empty() || blocked[0].empty()) return empty;

    const int H = (int)blocked.size();
    const int W = (int)blocked[0].size();

    auto InBounds = [&](int x, int y) { return x >= 0 && x < W && y >= 0 && y < H; };
    auto Walkable = [&](int x, int y) { return InBounds(x, y) && !blocked[y][x]; };

    if (!Walkable(start.x, start.y) || !Walkable(goal.x, goal.y))
        return empty;

    std::vector<std::vector<Node>> nodes(H, std::vector<Node>(W));
    std::vector<std::vector<bool>> closed(H, std::vector<bool>(W, false));

    std::priority_queue<OpenRec, std::vector<OpenRec>, OpenRecCompare> open;

    nodes[start.y][start.x].g = 0.0f;
    nodes[start.y][start.x].h = Heuristic(start, goal);
    open.push({ start.x, start.y, nodes[start.y][start.x].f() });

    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };

    while (!open.empty())
    {
        OpenRec cur = open.top();
        open.pop();

        if (closed[cur.y][cur.x]) continue;
        closed[cur.y][cur.x] = true;

        if (cur.x == goal.x && cur.y == goal.y)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (!Walkable(nx, ny) || closed[ny][nx]) continue;

            float tentativeG = nodes[cur.y][cur.x].g + 1.0f;

            if (tentativeG < nodes[ny][nx].g)
            {
                nodes[ny][nx].g = tentativeG;
                nodes[ny][nx].h = Heuristic({ nx, ny }, goal);
                nodes[ny][nx].parentX = cur.x;
                nodes[ny][nx].parentY = cur.y;
                nodes[ny][nx].hasParent = true;

                open.push({ nx, ny, nodes[ny][nx].f() });
            }
        }
    }

    if (!(start == goal) && !nodes[goal.y][goal.x].hasParent)
        return empty;

    std::vector<GridPos> path;
    GridPos p = goal;
    path.push_back(p);

    while (!(p == start))
    {
        Node& n = nodes[p.y][p.x];
        if (!n.hasParent) break;
        p = { n.parentX, n.parentY };
        path.push_back(p);
    }

    std::reverse(path.begin(), path.end());
    return path;
}
