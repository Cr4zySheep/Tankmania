#include "Human.hpp"

Human::Human(App& app, float x, float y, sf::String const name, int const _team) : Tank(app, x, y, name, _team)
{

}

Human::~Human()
{

}

void Human::handleInput()
{
    collision = false;
    if(this->isDestroyed()) return;

    //Déplacement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->change_direction(direction + 1.5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->change_direction(direction - 1.5);
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
    this->calculate_MotionVector();

    //Tir
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) this->fire();
}

void Human::update(float dt)
{
    Tank::update(dt);
}
