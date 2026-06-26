#pragma once

#include "BackButton.h"

class RewardsMainMenu
{
public:
    RewardsMainMenu();

    int getBackground() const;

    float getBackButtonX() const;
    float getBackButtonY() const;
    float getBackButtonWidth() const;
    float getBackButtonHeight() const;

private:
    int m_background;

    BackButton m_backButton;
};