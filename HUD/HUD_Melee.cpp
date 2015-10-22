#include "HUD_Melee.hpp"

HUD_Melee::HUD_Melee(sf::Vector2u const wS, Loader<sf::Font>& fontLoader) : HUD(wS, fontLoader) {
    for(unsigned int a(0); a < 3; a++) for(unsigned int b(0); b < 3; b++) {
        bests[a][b].setFont(fontLoader.getRef("thickhead"));
        bests[a][b].setAlign(ALIGN_RIGHT);
        bests[a][b].setPosition(0, a * 24 + 24);

        if(b == 0) {
            bests[a][b].setText({sf::String(Str::convert(a + 1) + ". "), sf::Color::Black, 24});
        }
    }
}

HUD_Melee::~HUD_Melee() {
}

void HUD_Melee::draw(sf::RenderWindow& window) {
    HUD::draw(window);
    for(unsigned int a(0); a < 3; a++) if(!bests[a][1].getString().isEmpty()) for(unsigned int b(0); b < 3; b++) {
        window.draw(bests[a][b]);
    }
}

void HUD_Melee::setBests(std::pair<std::pair<sf::String, sf::Color>, int> _bests[]) {
    for(unsigned int a(0); a < 3; a++) {
        sf::String const& name = _bests[a].first.first;
        sf::Color const& color = _bests[a].first.second;
        int const& score = _bests[a].second;

        if(!name.isEmpty()) {
            bests[a][1].setText({name, color, 24});
            sf::String text = " : " + Str::convert(score);
            bests[a][2].setText({text, sf::Color::Black, 24});

            float y = a * 24 + 24;
            bests[a][0].setPosition(windowSize.x - 28 - bests[a][2].getGlobalBounds().width - bests[a][1].getGlobalBounds().width, y);
            bests[a][1].setPosition(windowSize.x - 28 - bests[a][2].getGlobalBounds().width, y);
            bests[a][2].setPosition(windowSize.x - 28, y);
        }
    }
}
