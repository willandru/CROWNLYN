#pragma once

#include "Input.h"
#include "Renderer.h"
#include "Button.h"
#include "Shader.h"

#include "MainMenuScreen.h"
#include "OneVsAIScreen.h"
#include "OneScreen.h"
#include "MatchScreen.h"
#include "SpecialMovesScreen.h"
#include "HistoryEndingsScreen.h"
#include "HistoryMovesScreen.h"

enum class ScreenType
{
    MainMenu,
    OneVsAI,
    One,
    Match,
    Moves,
    HistoryEndings,
    HistoryMoves
};

class ScreenManager
{
public:
    ScreenManager();

    void setShader(Shader* shader);

    void update(const Input& input);
    void render(Renderer& renderer);

    bool shouldExit() const;

private:
    ScreenType m_currentScreen;
    bool m_shouldExit;

    Shader* m_uiShader;

    MainMenuScreen m_mainMenu;

    OneVsAIScreen m_oneVsAI;
    OneScreen m_one;
    MatchScreen m_match;
    SpecialMovesScreen m_moves;

    HistoryEndingsScreen m_historyEndings;
    HistoryMovesScreen m_historyMoves;
};