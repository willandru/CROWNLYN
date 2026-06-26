#include "OneVsAIScreen.h"

OneVsAIScreen::OneVsAIScreen()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};

    m_historyButton = {400.0f, 500.0f, 250.0f, 80.0f};
}

int OneVsAIScreen::getBackground() const
{
    return m_background;
}

float OneVsAIScreen::getBackButtonX() const
{
    return m_backButton.x;
}

float OneVsAIScreen::getBackButtonY() const
{
    return m_backButton.y;
}

float OneVsAIScreen::getBackButtonWidth() const
{
    return m_backButton.w;
}

float OneVsAIScreen::getBackButtonHeight() const
{
    return m_backButton.h;
}

float OneVsAIScreen::getHistoryButtonX() const
{
    return m_historyButton.x;
}

float OneVsAIScreen::getHistoryButtonY() const
{
    return m_historyButton.y;
}

float OneVsAIScreen::getHistoryButtonWidth() const
{
    return m_historyButton.w;
}

float OneVsAIScreen::getHistoryButtonHeight() const
{
    return m_historyButton.h;
}