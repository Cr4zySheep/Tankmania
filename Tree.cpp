#include "Tree.hpp"

Tree::Tree(Loader<sf::Texture>& textureLoader, float x, float y)
{
    this->setPosition(x, y);

    if(rand() % 2) this->setTexture(textureLoader.getRef("treeSmall"), 87, 87);
    else           this->setTexture(textureLoader.getRef("treeLarge"), 98, 107);

    sprite.setColor(sf::Color(255, 255, 255, 210));
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
    if(CollisionManager::isVisible(sprite.getGlobalBounds(), window.getView())) window.draw(sprite);
}
