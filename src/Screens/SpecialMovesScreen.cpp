#include "SpecialMovesScreen.h"

SpecialMovesScreen::SpecialMovesScreen()
    : m_background(0)
{
    m_button = {100.0f, 500.0f, 250.0f, 80.0f};
}

int SpecialMovesScreen::getBackground() const
{
    return m_background;
}

float SpecialMovesScreen::getButtonX() const
{
    return m_button.x;
}

float SpecialMovesScreen::getButtonY() const
{
    return m_button.y;
}

float SpecialMovesScreen::getButtonWidth() const
{
    return m_button.w;
}

float SpecialMovesScreen::getButtonHeight() const
{
    return m_button.h;
}

