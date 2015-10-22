#include "Label.hpp"

Label::Label(unsigned int const align) : alignment(align), state(UNUPDATE) {
}

Label::~Label() {
}

void Label::setText(LabelData lblData) {
    this->setString(lblData.text);
    this->setColor(lblData.color);
    this->setCharacterSize(lblData.charSize);
    this->adaptAlign();
}

void Label::setAlign(unsigned int const align) {
    alignment = align;
    this->adaptAlign();
}

void Label::adaptAlign() {
    if(alignment == ALIGN_LEFT) {
        this->setOrigin(sf::Vector2f(0, 0));
    } else if(alignment == ALIGN_CENTER) {
        this->setOrigin(sf::Vector2f(this->getLocalBounds().width / 2, 0));
    } else if(alignment == ALIGN_RIGHT) {
        this->setOrigin(sf::Vector2f(this->getLocalBounds().width, 0));
    }
}

void Label::handleInput(sf::Event& event) {
    switch(event.type) {
        case sf::Event::MouseMoved: states[HOVERED] = this->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);
        case sf::Event::MouseButtonReleased: states[CLICKED] = (states[HOVERED] && event.mouseButton.button == sf::Mouse::Left);
    }
}

bool Label::getState(int const state) {
    return (states.find(state) != states.end()) ? states[state] : false;
}
