#ifndef IA_MOVING_HPP_INCLUDED
#define IA_MOVING_HPP_INCLUDED

#include "Pathfinding.hpp"
#include "../Tank.hpp"
class IA_Moving
{
public:
    Point destination;
    std::vector<Point> path;
    int state;

    enum {
        IA_WAIT,
        IA_SEARCH_PATH,
        IA_FOLLOW_PATH
    };

    IA_Moving();
    void update(Tank* tank);
    void go_to(Point point);
    void stop();
};

#endif // IA_MOVING_HPP_INCLUDED
