#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

enum {
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_LEFT
};

enum {
    UNUPDATE,
    NORMAL,
    HOVERED,
    CLICKED
};

struct LabelData {
    sf::String text;
    sf::Color color;
    unsigned int charSize;
};

class Label : public sf::Text {
protected:
    unsigned int alignment;
    void adaptAlign();

    int state;
    std::map<int, bool> states;

public:
    Label(unsigned int const alignment = ALIGN_LEFT);
    virtual ~Label();

    void setText(LabelData lblData);
    void setAlign(unsigned int const align);

    bool getState(int const state);

    void handleInput(sf::Event& event);
};

#endif // LABEL_HPP_INCLUDED
