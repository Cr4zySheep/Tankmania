#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include "Tank.hpp"

class Human : public Tank
{
private:

public:
    Human(TextureManager& textureManager, float x, float y, std::string const name);
    virtual ~Human();

    void handleInput();
    void update(float dt);
};

#endif // HUMAN_HPP_INCLUDED
