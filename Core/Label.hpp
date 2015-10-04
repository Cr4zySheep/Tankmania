#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

enum {
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_LEFT
};

class Label {
private:
    sf::Text text;
    unsigned int alignment;

    void adaptAlign();

public:
    Label(unsigned int alignment = ALIGN_LEFT);
    ~Label();

    void modifyText(std::string const& _text, sf::Color const& color = sf::Color::Black, unsigned int charSize = 36);
    void setAlign(unsigned int const align);
    void setPosition(float x, float y);
    void setFont(sf::Font const& font);

    std::string getString() const;

    void draw(sf::RenderWindow& window);
};

#endif // LABEL_HPP_INCLUDED
