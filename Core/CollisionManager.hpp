#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>

struct Point {
    float x;
    float y;
};

struct Circle {
    sf::Vector2f center;
    int radius;
};

struct AABB {
    sf::FloatRect box;
};

struct CollisionData {
    Circle circle;
    AABB aabb;
};

class Object;

class CollisionManager
{
public:
    static bool AABB_and_AABB(AABB box1, AABB box2);
    static bool circle_and_point(Circle circle, Point point);
    static bool circle_and_circle(Circle circle1, Circle circle2);

    static bool collide(Object& object1, Object& object2, float dt);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
