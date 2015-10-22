#include "HUD.hpp"

HUD::HUD(sf::Vector2u const wS, Loader<sf::Font>& _fontLoader) : windowSize(wS), timer(ALIGN_CENTER), fontLoader(_fontLoader) {
    timer.setFont(fontLoader.getRef("thickhead"));
    timer.setPosition(windowSize.x / 2, 18);
    timerClock.restart();

    for(unsigned int a(0); a < 5; a++) for(unsigned int b(0); b < 3; b++) {
        tchat[a][b].setFont(fontLoader.getRef("thickhead"));
        tchat[a][b].setPosition(28, windowSize.y - (a + 1) * 24 - 28);
    }
}

HUD::~HUD() {
}

void HUD::upTchatMsg() {
    for(unsigned int a(4); a > 0; a--) for(unsigned int b(0); b < 3; b++) {
        float y = tchat[a][0].getGlobalBounds().top;
        tchat[a][b].setText({tchat[a - 1][b].getString(), tchat[a - 1][b].getColor(), 24});
        tchat[a][1].setPosition(28 + tchat[a][0].getGlobalBounds().width, y);
        tchat[a][2].setPosition(28 + tchat[a][0].getGlobalBounds().width + tchat[0][1].getGlobalBounds().width, y);
    }
}

void HUD::addMessage(sf::String msg) {
    this->upTchatMsg();

    tchat[0][0].setText({"", sf::Color::Black, 24});
    tchat[0][1].setText({msg, sf::Color::Black, 24});
    tchat[0][2].setText({"", sf::Color::Black, 24});

    float y = tchat[0][0].getGlobalBounds().top;
    tchat[0][1].setPosition(28 + tchat[0][0].getGlobalBounds().width, y);
    tchat[0][2].setPosition(28 + tchat[0][0].getGlobalBounds().width + tchat[0][1].getGlobalBounds().width, y);
}

void HUD::addMessage(sf::String msg, std::pair<sf::String, sf::Color> names[]) {
    this->upTchatMsg();

    tchat[0][0].setText({names[0].first, names[0].second, 24});
    tchat[0][1].setText({msg, sf::Color::Black, 24});
    tchat[0][2].setText({names[1].first, names[1].second, 24});

    float y = tchat[0][0].getGlobalBounds().top;
    tchat[0][1].setPosition(28 + tchat[0][0].getGlobalBounds().width, y);
    tchat[0][2].setPosition(28 + tchat[0][0].getGlobalBounds().width + tchat[0][1].getGlobalBounds().width, y);
}

void HUD::updateTimer() {
    int seconds = timerClock.getElapsedTime().asSeconds();
    int minutes = seconds / 60;
    seconds -= minutes * 60;

    sf::String time("");
    if(minutes < 10) {
        time += "0";
    }
    time += Str::convert(minutes) + " : ";
    if(seconds < 10) {
        time += "0";
    }
    time += Str::convert(seconds);

    timer.setText({time, sf::Color::Black, 36});
}

void HUD::update() {
    this->updateTimer();
}

void HUD::draw(sf::RenderWindow& window) {
    //Set view
    window.setView(window.getDefaultView());

    //Timer
    window.draw(timer);

    //Tchat messages
    for(unsigned int a(0); a < 5; a++) for(unsigned int b(0); b < 3; b++) {
        window.draw(tchat[a][b]);
    }
}

sf::Time HUD::getTime() const {
    return timerClock.getElapsedTime();
}

void HUD::restart() {
    timerClock.restart();
}
