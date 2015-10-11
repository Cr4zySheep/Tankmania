#include "HUD_Melee.hpp"

HUD_Melee::HUD_Melee(sf::Vector2u const wS, FontManager& fontManager) : HUD(wS, fontManager) {
    for(unsigned int a(0); a < 3; a++) for(unsigned int b(0); b < 3; b++) {
        bests[a][b].setFont(fontManager.getRef("thickhead"));
        bests[a][b].setAlign(ALIGN_RIGHT);
        bests[a][b].setPosition(0, a * 24 + 24);

        if(b == 0) {
            bests[a][b].modifyText(std::string(Str::convert(a + 1) + ". "), sf::Color::Black, 24);
        }
    }
}

HUD_Melee::~HUD_Melee() {
}

void HUD_Melee::draw(sf::RenderWindow& window) {
    HUD::draw(window);
    for(unsigned int a(0); a < 3; a++) if(!bests[a][1].getString().empty()) for(unsigned int b(0); b < 3; b++) {
        bests[a][b].draw(window);
    }
}

void HUD_Melee::setBests(std::pair<std::pair<std::string, sf::Color>, int> _bests[]) {
    for(unsigned int a(0); a < 3; a++) {
        std::string const& name = _bests[a].first.first;
        sf::Color const& color = _bests[a].first.second;
        int const& score = _bests[a].second;

        if(!name.empty()) {
            bests[a][1].modifyText(name, color, 24);
            std::string text = " : " + Str::convert(score);
            bests[a][2].modifyText(text, sf::Color::Black, 24);

            float y = a * 24 + 24;
            bests[a][0].setPosition(windowSize.x - 28 - bests[a][2].getSize().width - bests[a][1].getSize().width, y);
            bests[a][1].setPosition(windowSize.x - 28 - bests[a][2].getSize().width, y);
            bests[a][2].setPosition(windowSize.x - 28, y);
        }
    }
}
