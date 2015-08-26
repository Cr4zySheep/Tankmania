#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include "Tank.hpp"
#include "Pathfinding.hpp"

class IA : public Tank
{
private:
    std::vector<Point> path;

public:
    IA(TextureManager& textureManager, float x, float y);
    virtual ~IA();

    void handleInput();
    void update(float dt);
};

#endif // IA_HPP_INCLUDED
