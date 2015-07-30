#ifndef BARREL_HPP_INCLUDED
#define BARREL_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/TextureManager.hpp"

class Barrel : public Object
{
private:
    bool indestructible;
    bool destroyed;

public:
    Barrel();
    Barrel(TextureManager& TextureManager, bool topdown, float x, float y, bool indestructible = false);
    ~Barrel();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void setTexture(TextureManager& textureManager, bool topdown);

    bool isDestroyed() const;
    void destroy();

    void change_direction(float const new_direction);
};

#endif // BARREL_HPP_INCLUDED
