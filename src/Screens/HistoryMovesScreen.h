#pragma once

#include "BackButton.h"

class HistoryMovesScreen
{
public:
    HistoryMovesScreen();

    int getBackground() const;

    float getBackButtonX() const;
    float getBackButtonY() const;
    float getBackButtonWidth() const;
    float getBackButtonHeight() const;

private:
    int m_background;

    BackButton m_backButton;
};