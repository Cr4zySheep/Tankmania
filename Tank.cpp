#include "Tank.hpp"

Tank::Tank(TextureManager& textureManager, float x, float y) : Object(textureManager.getRef("tankBeige"), x, y, 83, 78)
{
    sprite.rotate(90);
    barrel.rotate(90);
    this->init_barrel(textureManager);
    this->update_barrel();
}


Tank::~Tank()
{

}

void Tank::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(barrel);
}

void Tank::init_barrel(TextureManager& textureManager)
{
    barrel.setOrigin(sf::Vector2f(12, 58));
    barrel.setTexture(textureManager.getRef("barrelBeige"));
    float sx((float)20 / (float)barrel.getTexture()->getSize().x),
          sy((float)58 / (float)barrel.getTexture()->getSize().y);
    barrel.scale(sx, sy);
}

void Tank::update_barrel()
{
    barrel.setPosition(this->left() + this->getWidth() / 2, this->top() + this->getHeight() / 2);
}

void Tank::regulate_velocity()
{
    if(velocity < tank_velocity_max * -1) velocity = tank_velocity_max * -1;
    if(velocity > tank_velocity_max) velocity = tank_velocity_max;
}
