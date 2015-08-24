#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include "Tank.hpp"

class IA : public Tank
{
private:
    Point point;

public:
    IA(TextureManager& textureManager, float x, float y);
    virtual ~IA();

    void handleInput();
    void update(float dt);
};

#endif // IA_HPP_INCLUDED
