#include "Barrel.hpp"

Barrel::Barrel(TextureManager& textureManager, bool topdown, float x, float y, bool indestructible) : destroyed(false)
{
    this->indestructible = indestructible;
    this->setPosition(x, y);

    if(topdown) this->setTexture(textureManager.getRef("barrelUp"), 48, 48);
    else        this->setTexture(textureManager.getRef("barrelSide"), 44, 62);
}

Barrel::~Barrel()
{

}

void Barrel::handleInput()
{
}

void Barrel::update(float dt)
{

}

void Barrel::draw(sf::RenderWindow& window)
{
    if(!destroyed) window.draw(sprite);
}

bool Barrel::isDestroyed() const
{
    return destroyed;
}

void Barrel::destroy()
{
    destroyed = true;
}
