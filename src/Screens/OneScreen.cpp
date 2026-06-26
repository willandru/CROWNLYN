#include "OneScreen.h"

OneScreen::OneScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
}

int OneScreen::getBackground() const
{
    return m_background;
}

float OneScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float OneScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float OneScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float OneScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}