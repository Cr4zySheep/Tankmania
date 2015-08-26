#include "IA.hpp"

IA::IA(TextureManager &textureManager, float x, float y) : Tank(textureManager, x, y)
{

}

IA::~IA()
{

}

void IA::handleInput()
{
    if(!path.empty())
    {
        Point& point = path.back();
        float angle = atan2(point.y - this->getPosition().y, point.x - this->getPosition().x) * 180 / PI * -1;
/*
        float diff(abs(angle - direction)), move;
        if(diff > 3) move = 3;
        else         move = diff;

        if(angle < direction) this->change_direction(direction + move * -1);
        else                  this->change_direction(direction + move);*/

        this->change_direction(angle);

        if(Point::distance(Point(this->getPosition()), point) > 300)
        {
            velocity += 10;
        }
        else if(Point::distance(Point(this->getPosition()), point) >= 16)
        {
            velocity -= 10;
            path.pop_back();
        }
    }
    else
    {
        if(velocity > 0)
        {
            velocity -= 10;
            if(velocity < 0) velocity = 0;
        }

        path = Pathfinding::find_path(Pathfinding::convert_pos(this->getPosition()), Pathfinding::convert_pos({rand() % 128 * 30, rand() % 128 * 30}));
    }

    this->regulate_velocity();
    this->calculate_MotionVector();
}

void IA::update(float dt)
{
    this->move(dt);

    update_barrel();
    if(bullet != 0) bullet->update(dt);
}
