#include "IA.hpp"

IA::IA(TextureManager &textureManager, float x, float y) : Tank(textureManager, x, y), point({rand() % 128 * 28 + 128, rand() % 128 * 28 + 128})
{

}

IA::~IA()
{

}

void IA::handleInput()
{
    float angle = atan2(point.y - this->getPosition().y, point.x - this->getPosition().x) * 180 / PI * -1;

    float diff(abs(angle - direction)), move;
    if(diff > 3) move = 3;
    else         move = diff;

    if(angle < direction) this->change_direction(direction + move * -1);
    else                  this->change_direction(direction + move);

    if(Point::distance(Point(this->getPosition()), point) > 300)
    {
        velocity += 10;
    }
    else if(Point::distance(Point(this->getPosition()), point) >= 16)
    {
        velocity = 0;
        point.x = rand() % 128 * 28 + 128;
        point.y = rand() % 128 * 28 + 128;
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
