#include "Label.hpp"

Label::Label(unsigned int align) : alignment(align) {
}

Label::~Label() {
}

void Label::modifyText(sf::String const& _text, sf::Color const& color, unsigned int charSize) {
    text.setString(_text);
    text.setColor(color);
    text.setCharacterSize(charSize);
    this->adaptAlign();
}

void Label::draw(sf::RenderWindow& window) {
    window.draw(text);
}

void Label::setAlign(unsigned int const align) {
    alignment = align;
    this->adaptAlign();
}

void Label::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void Label::adaptAlign() {
    if(alignment == ALIGN_LEFT) {
        text.setOrigin(sf::Vector2f(0, 0));
    } else if(alignment == ALIGN_CENTER) {
        text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, 0));
    } else if(alignment == ALIGN_RIGHT) {
        text.setOrigin(sf::Vector2f(text.getLocalBounds().width, 0));
    }
}

void Label::setFont(sf::Font const& font) {
    text.setFont(font);
}

sf::String Label::getString() const {
    return text.getString();
}

const sf::Color Label::getColor() const {
    return text.getColor();
}

sf::FloatRect Label::getSize() const {
    return text.getGlobalBounds();
}

const sf::Vector2f Label::getOrigin() const {
    return text.getOrigin();
}

const sf::Vector2f Label::getPosition() const {
    return text.getPosition();
}
