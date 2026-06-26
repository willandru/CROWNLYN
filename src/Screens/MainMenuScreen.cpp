#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
    : m_action(MainMenuAction::None)
{
    m_buttons[0] = {100, 100, 300, 80};
    m_buttons[1] = {100, 200, 300, 80};
    m_buttons[2] = {100, 300, 300, 80};
    m_buttons[3] = {100, 400, 300, 80};
    m_buttons[4] = {100, 500, 300, 80};
}

MainMenuAction MainMenuScreen::getAction() const
{
    return m_action;
}

void MainMenuScreen::setAction(MainMenuAction action)
{
    m_action = action;
}

void MainMenuScreen::clearAction()
{
    m_action = MainMenuAction::None;
}

int MainMenuScreen::getButtonCount() const
{
    return m_buttonCount;
}

float MainMenuScreen::getButtonX(int i) const { return m_buttons[i].x; }
float MainMenuScreen::getButtonY(int i) const { return m_buttons[i].y; }
float MainMenuScreen::getButtonWidth(int i) const { return m_buttons[i].w; }
float MainMenuScreen::getButtonHeight(int i) const { return m_buttons[i].h; }