#include "HUD.hpp"

HUD::HUD(sf::Vector2u const& windowSize, FontManager& _fontManager) : timer(ALIGN_CENTER), fontManager(_fontManager) {
    timer.setFont(fontManager.getRef("arial"));
    timer.setPosition(windowSize.x / 2, 10);
    timerClock.restart();

    for(unsigned int a(0); a < 5; a++) {
        tchat[a].setFont(fontManager.getRef("arial"));
        tchat[a].setPosition(10, windowSize.y - (a + 1) * 24 - 10);
    }
}

HUD::~HUD() {
}

void HUD::addMessage(std::string msg) {
    for(unsigned int a(4); a > 0; a--) {
        tchat[a].modifyText(tchat[a - 1].getString(), sf::Color::Black, 24);
    }
    tchat[0].modifyText(msg, sf::Color::Black, 24);
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
    for(unsigned int a(0); a < 5; a++) {
        tchat[a].draw(window);
    }
}

sf::Time HUD::getTime() const {
    return timerClock.getElapsedTime();
}

void HUD::restart() {
    timerClock.restart();
}
