#pragma once

#include "BackButton.h"

class OneVsAIScreen
{
public:
    OneVsAIScreen();

    int getBackground() const;

    float getBackButtonX() const;
    float getBackButtonY() const;
    float getBackButtonWidth() const;
    float getBackButtonHeight() const;

    float getHistoryButtonX() const;
    float getHistoryButtonY() const;
    float getHistoryButtonWidth() const;
    float getHistoryButtonHeight() const;

private:
    int m_background;

    BackButton m_backButton;
    BackButton m_historyButton;
};