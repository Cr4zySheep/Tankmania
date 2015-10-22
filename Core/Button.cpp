#include "Button.hpp"

Button::Button(unsigned int align) : Label(align), defaultLabel({"", sf::Color::Black, 36}), hoveredLabel({"", sf::Color::Black, 36}) {
}

Button::~Button() {
}

void Button::setLabels(LabelData defaultLabel, LabelData hoveredLabel) {
    this->defaultLabel = defaultLabel;
    this->hoveredLabel = hoveredLabel;
}

void Button::update() {
    if(this->getState(HOVERED) && state != HOVERED) {
        this->setText(hoveredLabel);
        state = HOVERED;
    } else if(!this->getState(HOVERED) && state != NORMAL) {
        this->setText(defaultLabel);
        state = NORMAL;
    }
}
