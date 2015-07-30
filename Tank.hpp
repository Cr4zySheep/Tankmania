#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "Bullet.hpp"

constexpr float tank_velocity_max(400);

class Tank : public Object
{
protected:
    sf::Sprite barrel;
    float barrel_angle;
    Bullet* bullet;
    sf::Clock reloading;
    void init_barrel();
    void update_barrel();

    void regulate_velocity();

    TextureManager& textureManager;

public:
    Tank(TextureManager& tM, float x, float y);
    virtual ~Tank();

    void handleInput() = 0;
    void update(float dt) = 0;
    void draw(sf::RenderWindow& window);

    void change_direction(float const new_direction);
    void align_barrel(sf::Vector2f point);
    void fire();

    Bullet* getBullet();
};

#endif // TANK_HPP_INCLUDED
