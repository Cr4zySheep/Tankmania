#include "CollisionManager.hpp"
#include "Object.hpp"
#include <iostream>
using namespace std;

bool CollisionManager::collide(Object& object1, Object& object2, float dt, bool react)
{
    CollisionData obj1 = object1.getCollisionData(dt);
    CollisionData obj2 = object2.getCollisionData(dt);

    if(AABB_and_AABB(obj1.aabb, obj2.aabb))
    {
        if(circle_and_circle(obj1.circle, obj2.circle))
        {
            if(react)
            {
                if(!object1.already_collided())
                {
                    object1.activeCollision();
                    if(object1.getVelocity() < 0) object1.change_velocity(100);
                    else                          object1.change_velocity(-100);
                }

                if(!object2.already_collided())
                {
                    object2.activeCollision();
                    if(object2.getVelocity() < 0) object2.change_velocity(100);
                    else                          object2.change_velocity(-100);
                }
            }
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

    return OI <= circle.radius * circle.radius;
}

bool CollisionManager::circle_and_circle(Circle circle1, Circle circle2)
{
    /*
     * Soit un cercle de centre O et de rayon A, et un cercle de centre I et de rayon B
     * On souhaite savoir s'il y a une collision entre ses 2 cercles
     * Donc si [OI] < A + B
     */

     auto OI(Point::distance(circle1.center, circle2.center));

     return OI <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}

bool CollisionManager::AABB_and_AABB(AABB box1, AABB box2)
{
    return !(box1.x > box2.x + box2.w ||
             box1.x + box1.w < box2.x ||
             box1.y > box2.y + box2.h ||
             box1.y + box1.h < box2.y);
}

bool CollisionManager::isVisible(sf::FloatRect s, sf::View const& v) {
    sf::FloatRect viewport(v.getViewport());
    viewport.left = v.getCenter().x - v.getSize().x / 2;
    viewport.top = v.getCenter().y - v.getSize().y / 2;
    viewport.width = v.getSize().x;
    viewport.height = v.getSize().y;
    return viewport.intersects(s);
}
