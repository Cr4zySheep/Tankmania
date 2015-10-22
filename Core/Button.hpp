#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Label.hpp"

class Button : public Label {
private:
    LabelData defaultLabel;
    LabelData hoveredLabel;

public:
    Button(unsigned int alignment = ALIGN_LEFT);
    ~Button();

    void setLabels(LabelData defaultLabel, LabelData hoveredLabel);

    void update();
};

#endif // BUTTON_HPP_INCLUDED
