#include "Button.hpp"

Button::Button(unsigned int align) : Label(align), isClicked(false), isHovered(false), hasChanged(false), defaultText(""), hoveredText(""), size(36), color(sf::Color::Black) {
}

Button::~Button() {
}

void Button::setTexts(sf::String defaultText, sf::String hoveredText, unsigned int size, sf::Color color) {
    this->defaultText = defaultText;
    this->hoveredText = hoveredText;
    this->size = size;
    this->color = color;
    hasChanged = true;
}

void Button::handleInput(sf::RenderWindow& window) {
    if(text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        if(!isHovered) {
            hasChanged = true;
            isHovered = true;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isClicked) {
            hasChanged = true;
            isClicked = true;
        } else {
            isClicked = false;
        }
    } else if(isHovered) {
        hasChanged = true;
        isHovered = false;
    }
}

void Button::update() {
    if(hasChanged) {
        if(isHovered) {
            this->modifyText(hoveredText, color, size);
        } else {
            this->modifyText(defaultText, color, size);
        }
        hasChanged = false;
    }
}

bool Button::getClicked() const {
    return isClicked;
}

bool Button::getHovered() const {
    return isHovered;
}
