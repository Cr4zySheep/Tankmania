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
        sprite.rotate(-3);
        barrel.rotate(-3);
        direction += 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.rotate(3);
        barrel.rotate(3);
        direction += -3;
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
