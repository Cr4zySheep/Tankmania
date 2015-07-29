#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include "Object.hpp"

class CollisionManager
{
private:
    //Collision entre deux rectangles
    static bool collision(float l1, float r1, float t1, float b1, float l2, float r2, float t2, float b2);

public:
    static bool collide(Object& object1, Object& object2, float dt);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
