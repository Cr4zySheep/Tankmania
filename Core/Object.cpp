#include "Object.hpp"
using namespace std;

Object::Object() : width(0), height(0), collision(false), velocity(0), direction(0)
{
}

Object::Object(sf::Texture const& texture, float x, float y, unsigned int width, unsigned int height) : collision(false), velocity(0), direction(0)
{
    this->setTexture(texture, width, height);
    this->setPosition(x, y);
}

Object::~Object()
{

}

void Object::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Object::setOrigin(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    sprite.setOrigin((float)width / 2, (float)height / 2);
}

void Object::setTexture(sf::Texture const& texture, unsigned int w, unsigned int h)
{
    this->setOrigin(w, h);

    sprite.setTexture(texture);

    float x((float)width / (float)texture.getSize().x),
          y((float)height / (float)texture.getSize().y);

    sprite.scale(x ,y);
}

float Object::left() const
{
    return sprite.getGlobalBounds().left;
}

float Object::top() const
{
    return sprite.getGlobalBounds().top;
}

float Object::getVelocity() const
{
    return velocity;
}

float Object::getWidth() const
{
    return sprite.getGlobalBounds().width;
}

float Object::getHeight() const
{
    return sprite.getGlobalBounds().height;
}

void Object::activeCollision()
{
    collision = true;
}

sf::Vector2f Object::getOrigin() const
{
    return sprite.getOrigin();
}

sf::Vector2f Object::getPosition() const
{
    return sprite.getPosition();
}

sf::Vector2f Object::getMotionVector() const
{
    return motion_vector;
}

bool Object::already_collided() const
{
    return collision;
}

void Object::calculate_MotionVector()
{
    float x(cos(direction * PI / 180) * velocity),
          y(sin(direction * PI / 180) * velocity * -1);

    motion_vector.x = x;
    motion_vector.y = y;
}

void Object::change_direction(float const new_direction)
{
    direction = new_direction;

    //Recalcule du vecteur de déplacement
    this->calculate_MotionVector();
}

void Object::change_velocity(float const new_velocity)
{
    velocity = new_velocity;

    //Recalcule du vecteur de déplacement
    this->calculate_MotionVector();
}

void Object::change_movement(float const new_direction, float const new_velocity)
{
    direction = new_direction;
    velocity = new_velocity;

    //Recalcule du vecteur de déplacement
    this->calculate_MotionVector();
}

void Object::move(float dt)
{
    sprite.move(motion_vector.x * dt, motion_vector.y * dt);
}

bool Object::isMovingToLeft() const
{
    if(cos(direction * PI / 180) <= 0) return true;
    else return false;
}
bool Object::isMovingToRight() const
{
    if(cos(direction * PI / 180) >= 0) return true;
    else return false;
}

bool Object::isMovingToTop() const
{
    if(sin(direction * PI / 180) >= 0) return true;
    else return false;
}

bool Object::isMovingToBottom() const
{
    if(sin(direction * PI / 180) <= 0) return true;
    else return false;
}

CollisionData Object::getCollisionData(float dt)
{
    //AABB
    collisionData.aabb.w = this->getWidth();
    collisionData.aabb.h = this->getHeight();
    collisionData.aabb.x = this->left() + this->getMotionVector().x * dt;
    collisionData.aabb.y = this->top() + this->getMotionVector().y * dt;

    //Circle
    collisionData.circle.center.x = this->getPosition().x + this->getMotionVector().x * dt;
    collisionData.circle.center.y = this->getPosition().y + this->getMotionVector().y * dt;
    return collisionData;
}
