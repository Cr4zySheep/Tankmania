#include "Bullet.hpp"


Bullet::Bullet(TextureManager& textureManager, float x, float y, float direction)
{
    this->change_movement(direction * -1, 1500);
    sprite.rotate(direction - 90 + 180);

    this->setTexture(textureManager.getRef("bulletBeige"), 20, 34);
    this->setPosition(x, y);
    collisionData.circle.radius = 5;
}

Bullet::~Bullet()
{

}

void Bullet::handleInput()
{

}

void Bullet::update(float dt)
{
    this->move(dt);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
