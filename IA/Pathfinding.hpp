#ifndef PATHFINDING_HPP_INCLUDED
#define PATHFINDING_HPP_INCLUDED

#include <map>
#include <vector>
#include "../Core/CollisionManager.hpp"
#include <iostream>

constexpr int limit_x = 128 * 30 / 32;
constexpr int limit_y = 128 * 30 / 32;

struct Node {
    Node() : G(0), H(0), F(1)
    {
    }

    Node(std::pair<int, int> _parent) : G(0), H(0), F(1), parent(_parent)
    {

    }

    uint G, //Cost to go to this node
         H, //Heuristic (0 if obstacle)
         F; //Final cost

    std::pair<int, int> parent; //Previous node in the path
};

struct Square {
    Square(bool _obs = false, uint _H = 1) : obstacle(_obs), H(_H)
    {

    }

    bool obstacle;
    uint H;
};

typedef std::map<std::pair<int, int>, Node> Graph;

class Pathfinding
{
private:
    static bool exist(std::pair<int, int> n, Graph& graph);
    static int heuristic(std::pair<int, int> p1, std::pair<int, int> p2);
    static bool enough_place(std::pair<int, int> node);
public:
    static bool enable;
    static std::map<std::pair<int, int>, Square> graph;

    static std::pair<int, int> convert_pos(sf::Vector2f pos);
    static std::vector<Point> find_path(std::pair<int, int> const start, std::pair<int, int> const finish);

};

#endif // PATHFINDING_HPP_INCLUDED
