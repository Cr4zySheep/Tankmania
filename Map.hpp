#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Core/CollisionManager.hpp"
#include "Tank.hpp"
#include "Barrel.hpp"
#include "Tree.hpp"
#include <iostream>
#include <cstdlib>

#define uint unsigned int

constexpr unsigned int map_width(30);
constexpr unsigned int map_height(30);
constexpr unsigned int total_tiles(map_width * map_height);

struct PuddleOfOil
{
    Barrel barrel;
    sf::Sprite oil;
};

class Map
{
private:
    TextureManager& textureManager;
    sf::Sprite tiles[total_tiles];
    std::vector<Barrel> borders;
    std::vector<Barrel> barrels;
    std::vector<PuddleOfOil> puddleOfOils;
    std::vector<Tree> forest;

    void create_puddleOfOil(float x, float y); //Cr�er une flaque d'huile aux coordonn�es
    void create_barrel(float x, float y); //Cr�er un baril aux coordonn�es
    void create_forest(float x, float y, uint number_of_tree); //Cr�er une for�t avec un nombre d'arbre pr�d�termin�

public:
    Map(TextureManager& tM);
    ~Map();

    void create();

    //G�re les collisions avec le d�cor
    bool handle_collision(Object& object, float dt);

    //Affiche les �l�ments en dessous des chars
    void draw_below(sf::RenderWindow& window);
    //Affiche les �l�ments au dessus des chars
    void draw_above(sf::RenderWindow& window);
};

#endif // MAP_HPP_INCLUDED
