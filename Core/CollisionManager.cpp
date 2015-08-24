#include "CollisionManager.hpp"
#include "Object.hpp"
#include <iostream>
using namespace std;

bool CollisionManager::collide(Object& object1, Object& object2, float dt)
{
    CollisionData obj1 = object1.getCollisionData(dt);
    CollisionData obj2 = object2.getCollisionData(dt);

    if(AABB_and_AABB(obj1.aabb, obj2.aabb))
    {
        if(circle_and_circle(obj1.circle, obj2.circle))
        {
            if(object1.getVelocity() < 0) object1.change_velocity(100);
            else                          object1.change_velocity(-100);

            if(object2.getVelocity() < 0) object2.change_velocity(100);
            else                          object2.change_velocity(-100);

            return true;
        }
    }

    return false;
}

bool CollisionManager::circle_and_point(Circle circle, Point point)
{
    /*
     * Soit O, le centre du cercle de rayon R et un point I
     * On souhaite savoir si le point I est à l'intérieur du cercle
     * Donc si [OI] < R
     */

    long x(point.x - circle.center.x),
         y(point.y - circle.center.y);

    double OI(x*x + y*y);

    if(OI <= circle.radius * circle.radius) return true;
    else                                   return false;
}

bool CollisionManager::circle_and_circle(Circle circle1, Circle circle2)
{
    /*
     * Soit un cercle de centre O et de rayon A, et un cercle de centre I et de rayon B
     * On souhaite savoir s'il y a une collision entre ses 2 cercles
     * Donc si [OI] < A + B
     */

     int OI(Point::distance(circle1.center, circle2.center));

     if(OI <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius)) return true;
     else                                                                            return false;
}

bool CollisionManager::AABB_and_AABB(AABB box1, AABB box2)
{
    if(box1.box.left > box2.box.left + box2.box.width ||
       box1.box.left + box1.box.width < box2.box.left ||
       box1.box.top > box2.box.top + box2.box.height  ||
       box1.box.top + box1.box.height < box2.box.top) return false;
    else return true;
}
