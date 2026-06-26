#include "MatchScreen.h"

MatchScreen::MatchScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
}

int MatchScreen::getBackground() const
{
    return m_background;
}

float MatchScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float MatchScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float MatchScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float MatchScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}