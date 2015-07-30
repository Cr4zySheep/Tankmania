#include "Tree.hpp"

Tree::Tree(TextureManager& textureManager, float x, float y)
{
    this->setPosition(x, y);

    if(rand() % 2) this->setTexture(textureManager.getRef("treeSmall"), 87, 87);
    else           this->setTexture(textureManager.getRef("treeLarge"), 98, 107);
}

Tree::~Tree()
{

}

void Tree::handleInput()
{

}

void Tree::update(float dt)
{

}

void Tree::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
