#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include "Tank.hpp"

class Human : public Tank
{
private:

public:
    Human(TextureManager& textureManager, sf::Font& _font, float x, float y, sf::String const name, int const team);
    virtual ~Human();

    void handleInput();
    void update(float dt);
};

#endif // HUMAN_HPP_INCLUDED
