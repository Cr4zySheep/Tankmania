#ifndef GAMEPLAY_HPP_INCLUDED
#define GAMEPLAY_HPP_INCLUDED

#include "Core/GameState.hpp"
#include "Human.hpp"
#include "IA/IA.hpp"
#include "Map.hpp"
#include <iostream>

class Gameplay : public GameState
{
private:
    sf::View view;
    void adapt_view_to_window();

    TextureManager textureManager;
    void load_textures();

    Map map;
    std::map<std::string, Tank*> tanks;
    std::vector<Bullet*> bullets;

    //Centre la view sur ce char
    std::string tankToFollow;
    void scrolling();

public:
    Gameplay(Game* game);
    ~Gameplay();

    void handleInput();
    void update(float dt);
    void draw();
};

#endif // GAMEPLAY_HPP_INCLUDED
