#include "HealthBar.hpp"
#include <iostream>
using namespace std;

HealthBar::HealthBar(uint max) : max_health(max), current_health(max)
{
    this->init();
}

HealthBar::HealthBar(uint max, uint current) : max_health(max), current_health(current)
{
    this->init();
}

HealthBar::~HealthBar()
{

}

void HealthBar::init()
{
    float w(100), h(5);
    border.setOrigin(w / 2, h / 2);
    border.setSize({w, h});
    //border.setOutlineThickness(2);
    border.setOutlineColor(sf::Color::Blue);

    this->check();
}

void HealthBar::set_max(uint max)
{
    max_health = max;
    this->check();
}

void HealthBar::set_health(uint health)
{
    current_health = health;
    this->check();
}

void HealthBar::update(sf::Vector2f pos)
{
    border.setPosition(pos);
}

void HealthBar::check()
{
    if(current_health > max_health) current_health = max_health;
    double coeff = (double)current_health / (double)max_health;
    int green(255 * coeff),
        red(255 - green);
    border.setFillColor({red, green, 0});
}

uint HealthBar::get_health() const
{
    return current_health;
}

uint HealthBar::get_max() const
{
    return max_health;
}

void HealthBar::add(uint x)
{
    current_health += x;
    this->check();
}

void HealthBar::remove(uint x)
{
    if(x >= current_health) current_health = 0;
    else current_health -= x;
    this->check();
}

void HealthBar::draw(sf::RenderWindow& window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))this->remove(1);
    window.draw(border);
}
