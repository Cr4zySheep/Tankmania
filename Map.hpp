#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Core/CollisionManager.hpp"
#include "Tank.hpp"
#include "Barrel.hpp"
#include <iostream>

constexpr unsigned int map_width(30);
constexpr unsigned int map_height(30);
constexpr unsigned int total_tiles(map_width * map_height);

/*
struct Node
{
    sf::Vector2f position;
    bool accessible;
    std::map<std::string, Node&> neightbors;
    std::map<std::string, unsigned int> neightborsValue;
};*/

class Map
{
private:
    sf::Sprite tiles[total_tiles];
    std::vector<Barrel> barrels;

public:
    Map();
    ~Map();

    void create(TextureManager& textureManager);

    void handle_collision(Tank& tank, float dt);
    void draw(sf::RenderWindow& window);
};

#endif // MAP_HPP_INCLUDED
