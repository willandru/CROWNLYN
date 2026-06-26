#pragma once

enum class MainMenuAction
{
    None,
    OneVsAI,
    One,
    Match,
    Moves,
    Rewards,
    Exit
};

struct MenuButton
{
    float x, y, w, h;
};

class MainMenuScreen
{
public:
    MainMenuScreen();

    MainMenuAction getAction() const;
    void setAction(MainMenuAction action);
    void clearAction();

    int getButtonCount() const;

    float getButtonX(int index) const;
    float getButtonY(int index) const;
    float getButtonWidth(int index) const;
    float getButtonHeight(int index) const;

private:
    MainMenuAction m_action;

    static constexpr int m_buttonCount = 6;
    MenuButton m_buttons[m_buttonCount];
};