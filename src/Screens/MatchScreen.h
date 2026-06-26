#pragma once

#include "BackButton.h"

class MatchScreen
{
public:
    MatchScreen();

    int getBackground() const;

    float getButtonX() const;
    float getButtonY() const;
    float getButtonWidth() const;
    float getButtonHeight() const;

private:
    int m_background;
    BackButton m_button;
};  