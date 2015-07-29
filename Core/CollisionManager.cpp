#include "CollisionManager.hpp"
#include <iostream>
using namespace std;

bool CollisionManager::collision(float l1, float r1, float t1, float b1, float l2, float r2, float t2, float b2)
{
    if(l1 > r2 ||
       r1 < l2 ||
       t1 > b2 ||
       b1 < t2 ) return false;
    else return true;
}

bool CollisionManager::collide(Object& object1, Object& object2, float dt)
{
    float x1(object1.getMotionVector().x * dt),
          y1(object1.getMotionVector().y * dt),
          x2(object2.getMotionVector().x * dt),
          y2(object2.getMotionVector().y * dt);

    if(collision(object1.left() + x1, object1.right() + x1, object1.top() + y1, object1.bottom() + y1,
                       object2.left() + x2, object2.right() + x2, object2.top() + y2, object2.bottom() + y2))
    {
        object1.change_velocity(0);
        object2.change_velocity(0);
    }
}
