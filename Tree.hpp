#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"
#include <cstdlib>

class Tree : public Object
{
private:

public:
    Tree(TextureManager& textureManager, float x, float y);
    ~Tree();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
};

#endif // TREE_HPP_INCLUDED
