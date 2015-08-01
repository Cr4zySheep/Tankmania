#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <SFML/System.hpp>
#include <math.h>

struct Point {
    float x;
    float y;
};

struct Circle {
    sf::Vector2f center;
    int radius;
};

class Object;

class CollisionManager
{
public:
    static bool circle_and_point(Circle circle, Point point);
    static bool circle_and_circle(Circle circle1, Circle circle2);
    //Collision entre deux rectangles
    static bool collision(float l1, float r1, float t1, float b1, float l2, float r2, float t2, float b2);
    static bool collide(Object& object1, Object& object2, float dt);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
