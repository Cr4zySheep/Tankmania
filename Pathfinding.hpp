#ifndef PATHFINDING_HPP_INCLUDED
#define PATHFINDING_HPP_INCLUDED

#include <map>
#include <vector>
#include "Core/CollisionManager.hpp"

typedef unsigned int uint;

constexpr int limit_x = 128 * 30 / 32;
constexpr int limit_y = 128 * 30 / 32;

struct Node {
    uint G, //Cost to go to this node
         H, //Heuristic (0 if obstacle)
         F; //Final cost

    std::pair<int, int> parent; //Previous node in the path
};

typedef std::map<std::pair<int, int>, Node> Graph;

class Pathfinding
{
private:
    static bool exist(std::pair<int, int> n, Graph& graph);
    static int heuristic(std::pair<int, int> p1, std::pair<int, int> p2);
public:
    static std::map<std::pair<int, int>, bool> graph; //True if obstacle
    static std::vector<Point> find_path(std::pair<int, int> const start, std::pair<int, int> const finish);

};

#endif // PATHFINDING_HPP_INCLUDED
