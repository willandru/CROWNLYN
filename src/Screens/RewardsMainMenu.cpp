#include "RewardsMainMenu.h"

RewardsMainMenu::RewardsMainMenu()
    : m_background(0)
{
    m_backButton = {100.0f, 500.0f, 250.0f, 80.0f};
}

int RewardsMainMenu::getBackground() const
{
    return m_background;
}

float RewardsMainMenu::getBackButtonX() const
{
    return m_backButton.x;
}

float RewardsMainMenu::getBackButtonY() const
{
    return m_backButton.y;
}

float RewardsMainMenu::getBackButtonWidth() const
{
    return m_backButton.w;
}

float RewardsMainMenu::getBackButtonHeight() const
{
    return m_backButton.h;
}