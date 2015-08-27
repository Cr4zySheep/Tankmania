#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include "Tank.hpp"
#include "Pathfinding.hpp"

struct Path
{
    Point destination;
    std::vector<Point> path;
};

union Data
{
    Data()  {};
    ~Data() {};

    Path path;
};

struct IA_STATE
{
    IA_STATE() {
    }

    Data data;
    int type;
};

enum
{
    IA_WAIT,
    IA_SEARCH_PATH,
    IA_FOLLOW_PATH
};

class IA : public Tank
{
private:
    IA_STATE state;

public:
    IA(TextureManager& textureManager, float x, float y);
    virtual ~IA();

    void handleInput();
    void update(float dt);
};

#endif // IA_HPP_INCLUDED
