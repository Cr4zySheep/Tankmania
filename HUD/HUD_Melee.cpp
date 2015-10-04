#include "HUD_Melee.hpp"

HUD_Melee::HUD_Melee(sf::Vector2u const& windowSize, FontManager& fontManager) : HUD(windowSize, fontManager) {
    for(unsigned int a(0); a < 3; a++) {
        bests[a].setFont(fontManager.getRef("thickhead"));
        bests[a].setAlign(ALIGN_RIGHT);
        bests[a].setPosition(windowSize.x - 28, a * 24 + 24);
    }
}

HUD_Melee::~HUD_Melee() {
}

void HUD_Melee::draw(sf::RenderWindow& window) {
    HUD::draw(window);
    for(unsigned int a(0); a < 3; a++) {
        bests[a].draw(window);
    }
}

void HUD_Melee::setBests(std::pair<std::string, int> _bests[]) {
    for(unsigned int a(0); a < 3; a++) if(!_bests[a].first.empty()) {
        std::string text = Str::convert(a + 1) + ". " + _bests[a].first + " : " + Str::convert(_bests[a].second);
        bests[a].modifyText(text, sf::Color::Black, 24);
    }
}
