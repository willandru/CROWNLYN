#include "MatchScreen.h"

MatchScreen::MatchScreen()
    : m_background(0)
{
    m_button = {100.0f, 500.0f, 250.0f, 80.0f};
}

int MatchScreen::getBackground() const
{
    return m_background;
}

float MatchScreen::getButtonX() const
{
    return m_button.x;
}

float MatchScreen::getButtonY() const
{
    return m_button.y;
}

float MatchScreen::getButtonWidth() const
{
    return m_button.w;
}

float MatchScreen::getButtonHeight() const
{
    return m_button.h;
}