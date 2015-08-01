#include "Tank.hpp"

Tank::Tank(TextureManager& tM, float x, float y) : Object(tM.getRef("tankBeige"), x, y, 83, 78), textureManager(tM), bullet(nullptr)
{
    sprite.rotate(90);
    barrel.rotate(90);
    this->init_barrel();
    this->update_barrel();

    collisionData.circle.radius = 40;
    collisionData.circle.center = this->getPosition();
}


Tank::~Tank()
{
    delete bullet;
}

void Tank::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    if(bullet != 0) bullet->draw(window);
    window.draw(barrel);
}

void Tank::init_barrel()
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

void Tank::change_direction(float const new_direction)
{
    float angle = direction - new_direction;
    sprite.rotate(angle);
    direction = new_direction;
}

void Tank::align_barrel(sf::Vector2f point)
{
    float angle = atan2(point.y - this->getPosition().y, point.x - this->getPosition().x) * 180 / PI;
    barrel.rotate(angle - barrel_angle);
    barrel_angle = angle;
}

void Tank::fire()
{
    sf::Time time = reloading.getElapsedTime();
    if(time.asSeconds() > 1)
    {
        delete bullet;
        bullet = new Bullet(textureManager, this->getPosition().x, this->getPosition().y, barrel_angle);
        reloading.restart();
    }
}

Bullet* Tank::getBullet()
{
    Bullet* bullet = this->bullet;
    this->bullet = nullptr;
    return bullet;
}
