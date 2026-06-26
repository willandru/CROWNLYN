#pragma once

#include "BackButton.h"

class OneVsAIScreen
{
public:
    OneVsAIScreen();

    int getBackground() const;

    float getButtonX() const;
    float getButtonY() const;
    float getButtonWidth() const;
    float getButtonHeight() const;

private:
    int m_background;
    BackButton m_button;
};