#include "OneVsAIScreen.h"

OneVsAIScreen::OneVsAIScreen()
    : m_background(0)
{
    m_button = {100.0f, 500.0f, 250.0f, 80.0f};
}

int OneVsAIScreen::getBackground() const
{
    return m_background;
}

float OneVsAIScreen::getButtonX() const
{
    return m_button.x;
}

float OneVsAIScreen::getButtonY() const
{
    return m_button.y;
}

float OneVsAIScreen::getButtonWidth() const
{
    return m_button.w;
}

float OneVsAIScreen::getButtonHeight() const
{
    return m_button.h;
}