#include "HistoryMovesScreen.h"

HistoryMovesScreen::HistoryMovesScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
}

int HistoryMovesScreen::getBackground() const
{
    return m_background;
}

float HistoryMovesScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float HistoryMovesScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float HistoryMovesScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float HistoryMovesScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}