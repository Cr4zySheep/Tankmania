#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"

constexpr float tank_velocity_max(400);

class Tank : public Object
{
protected:
    sf::Sprite barrel;
    float barrel_angle;
    void init_barrel(TextureManager& textureManager);
    void update_barrel();

    void regulate_velocity();

public:
    Tank(TextureManager& textureManager, float x, float y);
    virtual ~Tank();

    void handleInput() = 0;
    void update(float dt) = 0;
    void draw(sf::RenderWindow& window);

    void change_direction(float const new_direction);
    void align_barrel(sf::Vector2f point);
};

#endif // TANK_HPP_INCLUDED
