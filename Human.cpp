#include "Human.hpp"

Human::Human(TextureManager& textureManager, float x, float y) : Tank(textureManager, x, y)
{

}

Human::~Human()
{

}

void Human::handleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->change_direction(direction + 3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->change_direction(direction - 3);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocity += 10;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocity -= 10;
    }
    else
    {
        if(velocity < 0) velocity += 5;
        if(velocity > 0) velocity -= 5;
    }

    this->regulate_velocity();
}

void Human::update(float dt)
{
    this->calculate_MotionVector();
    this->move(dt);

    update_barrel();
}
