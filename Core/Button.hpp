#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Label.hpp"
#include <iostream>

class Button : public Label {
private:
    bool isClicked;
    bool isHovered;
    bool hasChanged;

    sf::String defaultText;
    sf::String hoveredText;
    unsigned int size;
    sf::Color color;

public:
    Button(unsigned int alignment = ALIGN_LEFT);
    ~Button();

    void setTexts(sf::String defaultText, sf::String hoveredText, unsigned int size = 36, sf::Color color = sf::Color::Black);
    bool getClicked() const;
    bool getHovered() const;

    void handleInput(sf::RenderWindow& window);
    void update();
};

#endif // BUTTON_HPP_INCLUDED
