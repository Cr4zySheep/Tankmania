#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "Bullet.hpp"
#include "HealthBar.hpp"

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
    HealthBar health;
    bool destroyed;

public:
    std::string const name;
    Tank(TextureManager& tM, float x, float y, std::string const _name);
    virtual ~Tank();

    void handleInput() = 0;
    void update(float dt) = 0;
    void draw(sf::RenderWindow& window);

    void change_direction(float const new_direction);
    void align_barrel(sf::Vector2f point);
    void fire();
    void damaged(Bullet* bullet);
    void respawn(sf::Vector2f pos);

    bool isDestroyed() const;
    Bullet* getBullet();
};

#endif // TANK_HPP_INCLUDED
