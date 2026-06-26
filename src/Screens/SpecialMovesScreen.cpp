#include "SpecialMovesScreen.h"

SpecialMovesScreen::SpecialMovesScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
    m_historyButton = {400.0f, 500.0f, 250.0f, 80.0f};
}

int SpecialMovesScreen::getBackground() const
{
    return m_background;
}

float SpecialMovesScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float SpecialMovesScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float SpecialMovesScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float SpecialMovesScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}

float SpecialMovesScreen::getHistoryButtonX() const
{
    return m_historyButton.x;
}

float SpecialMovesScreen::getHistoryButtonY() const
{
    return m_historyButton.y;
}

float SpecialMovesScreen::getHistoryButtonWidth() const
{
    return m_historyButton.w;
}

float SpecialMovesScreen::getHistoryButtonHeight() const
{
    return m_historyButton.h;
}