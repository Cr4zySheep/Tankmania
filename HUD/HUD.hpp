#ifndef HUD_HPP_INCLUDED
#define HUD_HPP_INCLUDED

#include "../Core/Label.hpp"
#include "../Core/FontManager.hpp"
#include "../Core/Str.hpp"
#include <iostream>

class HUD {
protected:
    sf::Vector2u const windowSize;

    Label timer;
    sf::Clock timerClock;

    Label tchat[5][3];

    FontManager& fontManager;

    void updateTimer();

public:
    HUD(sf::Vector2u const wS, FontManager& _fontManager);
    virtual ~HUD();

    sf::Time getTime() const;
    void restart();

    void addMessage(sf::String msg);
    void addMessage(sf::String msg, std::pair<sf::String, sf::Color> names[]);

    virtual void update();
    virtual void draw(sf::RenderWindow& window);
};

#endif // HUD_HPP_INCLUDED
