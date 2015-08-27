#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"

class Bullet : public Object
{
public:
    uint const damage;
    std::string const shooter;

    Bullet(TextureManager& textureManager, float x, float y, float direction, std::string const _owner);
    ~Bullet();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
};

#endif // BULLET_HPP_INCLUDED
