#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"

class Bullet : public Object
{
private:

public:
    Bullet(TextureManager& textureManager, float x, float y, float direction);
    ~Bullet();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
};

#endif // BULLET_HPP_INCLUDED
