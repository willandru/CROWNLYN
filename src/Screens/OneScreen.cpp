#include "OneScreen.h"

OneScreen::OneScreen()
    : m_background(0)
{
    m_button = {100.0f, 500.0f, 250.0f, 80.0f};
}

int OneScreen::getBackground() const
{
    return m_background;
}

float OneScreen::getButtonX() const
{
    return m_button.x;
}

float OneScreen::getButtonY() const
{
    return m_button.y;
}

float OneScreen::getButtonWidth() const
{
    return m_button.w;
}

float OneScreen::getButtonHeight() const
{
    return m_button.h;
}