#include "HUD.hpp"

HUD::HUD(sf::Vector2u const wS, FontManager& _fontManager) : windowSize(wS), timer(ALIGN_CENTER), fontManager(_fontManager) {
    timer.setFont(fontManager.getRef("thickhead"));
    timer.setPosition(windowSize.x / 2, 18);
    timerClock.restart();

    for(unsigned int a(0); a < 5; a++) for(unsigned int b(0); b < 3; b++) {
        tchat[a][b].setFont(fontManager.getRef("thickhead"));
        tchat[a][b].setPosition(28, windowSize.y - (a + 1) * 24 - 28);
    }
}

HUD::~HUD() {
}

void HUD::addMessage(std::string msg) {
    for(unsigned int a(4); a > 0; a--) for(unsigned int b(0); b < 3; b++) {
        tchat[a][b].modifyText(tchat[a - 1][b].getString(), tchat[a - 1][b].getColor(), 24);
    }

    tchat[0][0].modifyText("", sf::Color::Black, 24);
    tchat[0][1].modifyText(msg, sf::Color::Black, 24);
    tchat[0][2].modifyText("", sf::Color::Black, 24);

    float y = tchat[0][0].getSize().top;
    tchat[0][1].setPosition(28 + tchat[0][0].getSize().width, y);
    tchat[0][2].setPosition(28 + tchat[0][0].getSize().width + tchat[0][1].getSize().width, y);
}

void HUD::addMessage(std::string msg, std::pair<std::string, sf::Color> names[]) {
    for(unsigned int a(4); a > 0; a--) for(unsigned int b(0); b < 3; b++) {
        float y = tchat[a][0].getSize().top;
        tchat[a][b].modifyText(tchat[a - 1][b].getString(), tchat[a - 1][b].getColor(), 24);
        tchat[a][1].setPosition(28 + tchat[0][0].getSize().width, y);
        tchat[a][2].setPosition(28 + tchat[0][0].getSize().width + tchat[0][1].getSize().width, y);
    }

    tchat[0][0].modifyText(names[0].first, names[0].second, 24);
    tchat[0][1].modifyText(msg, sf::Color::Black, 24);
    tchat[0][2].modifyText(names[1].first, names[1].second, 24);

    float y = tchat[0][0].getSize().top;
    tchat[0][1].setPosition(28 + tchat[0][0].getSize().width, y);
    tchat[0][2].setPosition(28 + tchat[0][0].getSize().width + tchat[0][1].getSize().width, y);
}

void HUD::updateTimer() {
    int seconds = timerClock.getElapsedTime().asSeconds();
    int minutes = seconds / 60;
    seconds -= minutes * 60;

    std::string time("");
    if(minutes < 10) {
        time += "0";
    }
    time += Str::convert(minutes) + " : ";
    if(seconds < 10) {
        time += "0";
    }
    time += Str::convert(seconds);

    timer.modifyText(time);
}

void HUD::update() {
    this->updateTimer();
}

void HUD::draw(sf::RenderWindow& window) {
    //Set view
    window.setView(window.getDefaultView());

    //Timer
    timer.draw(window);

    //Tchat messages
    for(unsigned int a(0); a < 5; a++) for(unsigned int b(0); b < 3; b++) {
        tchat[a][b].draw(window);
    }
}

sf::Time HUD::getTime() const {
    return timerClock.getElapsedTime();
}

void HUD::restart() {
    timerClock.restart();
}
