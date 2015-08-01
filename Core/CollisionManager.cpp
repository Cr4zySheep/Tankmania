#include "CollisionManager.hpp"
#include "Object.hpp"
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
        if(circle_and_circle(object1.getCollisionData(dt), object2.getCollisionData(dt)))
        {
            object1.change_velocity(-100);
            object2.change_velocity(-100);
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

     long x(circle2.center.x - circle1.center.x),
          y(circle2.center.y - circle1.center.y);

     int OI(x*x + y*y);

     if(OI <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius)) return true;
     else                                                                            return false;
}
