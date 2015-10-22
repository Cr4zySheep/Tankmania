#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>

typedef unsigned int uint;

struct Point {
    float x;
    float y;

    Point()
    {}

    Point(sf::Vector2f pos) : x(pos.x), y(pos.y)
    {}

    //Distance euclidienne
    static float distance(Point p1, Point p2) {
        return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    }
};

struct Circle {
    Point center;
    int radius;
};

struct AABB {
    AABB() : x(0), y(0), w(0), h(0)
    {

    }

    float x, y, w, h;
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

    static bool collide(Object& object1, Object& object2, float dt, bool react = true);
    static bool isVisible(sf::FloatRect s, sf::View const& v);
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
