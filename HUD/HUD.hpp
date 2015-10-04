#ifndef HUD_HPP_INCLUDED
#define HUD_HPP_INCLUDED

#include "../Core/Label.hpp"
#include "../Core/FontManager.hpp"
#include "../Core/Str.hpp"

class HUD {
protected:
    Label timer;
    sf::Clock timerClock;

    Label tchat[5];

    FontManager& fontManager;

    void updateTimer();

public:
    HUD(sf::Vector2u const& windowSize, FontManager& _fontManager);
    virtual ~HUD();

    sf::Time getTime() const;
    void restart();

    void addMessage(std::string msg);

    virtual void update();
    virtual void draw(sf::RenderWindow& window);
};

#endif // HUD_HPP_INCLUDED
