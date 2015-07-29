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
    Barrel(TextureManager& TextureManager, bool topdown, float x, float y, bool indestructible = false);
    ~Barrel();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isDestroyed() const;
    void destroy();
};

#endif // BARREL_HPP_INCLUDED
