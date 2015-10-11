#ifndef HUD_MELEE_HPP_INCLUDED
#define HUD_MELEE_HPP_INCLUDED

#include "HUD.hpp"

class HUD_Melee : public HUD {
private:
    Label bests[3][3];

public:
    HUD_Melee(sf::Vector2u const wS, FontManager& _fontManager);
    virtual ~HUD_Melee();

    void setBests(std::pair<std::pair<std::string, sf::Color>, int> _bests[]);

    virtual void draw(sf::RenderWindow& window);
};

#endif // HUD_MELEE_HPP_INCLUDED
