#include "Human.hpp"

Human::Human(TextureManager& textureManager, sf::Font& _font, float x, float y, std::string const name, int const _team) : Tank(textureManager, _font, x, y, name, _team)
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
    this->calculate_MotionVector();

    //Tir
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) this->fire();
}

void Human::update(float dt)
{
    Tank::update(dt);
}
