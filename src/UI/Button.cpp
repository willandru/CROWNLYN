// Button.cpp

#include "Button.h"

bool Button::contains(
    double mouseX,
    double mouseY) const
{
    return
        mouseX >= x &&
        mouseX <= x + width &&
        mouseY >= y &&
        mouseY <= y + height;
}