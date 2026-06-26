#include "HistoryEndingsScreen.h"

HistoryEndingsScreen::HistoryEndingsScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
}

int HistoryEndingsScreen::getBackground() const
{
    return m_background;
}

float HistoryEndingsScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float HistoryEndingsScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float HistoryEndingsScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float HistoryEndingsScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}