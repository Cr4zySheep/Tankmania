#ifndef BARREL_HPP_INCLUDED
#define BARREL_HPP_INCLUDED

#include "Core/Object.hpp"
#include "Core/Loader.hpp"

class Barrel : public Object
{
private:
    bool indestructible;
    bool destroyed;

public:
    Barrel();
    Barrel(Loader<sf::Texture>& textureLoader, bool topdown, float x, float y, bool indestructible = false);
    ~Barrel();

    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void setTexture(Loader<sf::Texture>& textureLoader, bool topdown);

    bool isDestroyed() const;
    void destroy();

    void change_direction(float const new_direction);
};

#endif // BARREL_HPP_INCLUDED
