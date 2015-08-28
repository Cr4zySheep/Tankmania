#include "Bullet.hpp"

Bullet::Bullet(TextureManager& textureManager, float x, float y, float direction, std::string const _shooter, int const _team) : damage(20), shooter(_shooter), team(_team), lifeTime(sf::seconds(10))
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
    lifeTime -= sf::seconds(dt);

    this->move(dt);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Bullet::alive() const
{
    if(lifeTime.asSeconds() > 0) return true;
    else return false;
}
