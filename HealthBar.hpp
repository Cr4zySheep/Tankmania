#ifndef HEALTHBAR_HPP_INCLUDED
#define HEALTHBAR_HPP_INCLUDED

#include <SFML/Graphics.hpp>
typedef unsigned int uint;

class HealthBar
{
private:
    uint max_health;
    uint current_health;

    sf::RectangleShape border;

    void check();
    void init();
public:
    HealthBar(uint max);
    HealthBar(uint max, uint current);
    ~HealthBar();

    uint get_health() const;
    uint get_max() const;
    void add(uint x);
    void remove(uint x);

    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f pos);
    void set_max(uint max);
    void set_health(uint health);
};

#endif // HEALTHBAR_HPP_INCLUDED
