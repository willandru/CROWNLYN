#include "ScreenManager.h"

ScreenManager::ScreenManager()
    : m_currentScreen(ScreenType::MainMenu),
      m_shouldExit(false),
      m_uiShader(nullptr)
{
}

void ScreenManager::setShader(Shader* shader)
{
    m_uiShader = shader;
}

void ScreenManager::update(const Input& input)
{
    if (m_shouldExit)
        return;

    switch (m_currentScreen)
    {
        case ScreenType::MainMenu:
        {
            m_mainMenu.clearAction();

            if (input.leftMouseClicked())
            {
                double mx = input.mouseX();
                double my = input.mouseY();

                int count = m_mainMenu.getButtonCount();

                for (int i = 0; i < count; i++)
                {
                    Button b;

                    b.x = m_mainMenu.getButtonX(i);
                    b.y = m_mainMenu.getButtonY(i);
                    b.width = m_mainMenu.getButtonWidth(i);
                    b.height = m_mainMenu.getButtonHeight(i);

                    if (b.contains(mx, my))
                    {
                        switch (i)
                        {
                            case 0:
                                m_mainMenu.setAction(MainMenuAction::OneVsAI);
                                break;

                            case 1:
                                m_mainMenu.setAction(MainMenuAction::One);
                                break;

                            case 2:
                                m_mainMenu.setAction(MainMenuAction::Match);
                                break;

                            case 3:
                                m_mainMenu.setAction(MainMenuAction::Moves);
                                break;

                            case 4:
                                m_mainMenu.setAction(MainMenuAction::Exit);
                                break;
                        }
                    }
                }
            }

            switch (m_mainMenu.getAction())
            {
                case MainMenuAction::OneVsAI:
                    m_currentScreen = ScreenType::OneVsAI;
                    break;

                case MainMenuAction::One:
                    m_currentScreen = ScreenType::One;
                    break;

                case MainMenuAction::Match:
                    m_currentScreen = ScreenType::Match;
                    break;

                case MainMenuAction::Moves:
                    m_currentScreen = ScreenType::Moves;
                    break;

                case MainMenuAction::Exit:
                    m_shouldExit = true;
                    break;

                default:
                    break;
            }

            break;
        }

        case ScreenType::OneVsAI:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_oneVsAI.getBackButtonX();
                b.y = m_oneVsAI.getBackButtonY();
                b.width = m_oneVsAI.getBackButtonWidth();
                b.height = m_oneVsAI.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
                    break;
                }

                b.x = m_oneVsAI.getHistoryButtonX();
                b.y = m_oneVsAI.getHistoryButtonY();
                b.width = m_oneVsAI.getHistoryButtonWidth();
                b.height = m_oneVsAI.getHistoryButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::HistoryEndings;
                }
            }

            break;
        }

        case ScreenType::One:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_one.getBackButtonX();
                b.y = m_one.getBackButtonY();
                b.width = m_one.getBackButtonWidth();
                b.height = m_one.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
                }
            }

            break;
        }

        case ScreenType::Match:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_match.getBackButtonX();
                b.y = m_match.getBackButtonY();
                b.width = m_match.getBackButtonWidth();
                b.height = m_match.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
                }
            }

            break;
        }

        case ScreenType::Moves:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_moves.getBackButtonX();
                b.y = m_moves.getBackButtonY();
                b.width = m_moves.getBackButtonWidth();
                b.height = m_moves.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
                    break;
                }

                b.x = m_moves.getHistoryButtonX();
                b.y = m_moves.getHistoryButtonY();
                b.width = m_moves.getHistoryButtonWidth();
                b.height = m_moves.getHistoryButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::HistoryMoves;
                }
            }

            break;
        }

        case ScreenType::HistoryEndings:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_historyEndings.getBackButtonX();
                b.y = m_historyEndings.getBackButtonY();
                b.width = m_historyEndings.getBackButtonWidth();
                b.height = m_historyEndings.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::OneVsAI;
                }
            }

            break;
        }

        case ScreenType::HistoryMoves:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_historyMoves.getBackButtonX();
                b.y = m_historyMoves.getBackButtonY();
                b.width = m_historyMoves.getBackButtonWidth();
                b.height = m_historyMoves.getBackButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::Moves;
                }
            }

            break;
        }
    }
}

void ScreenManager::render(Renderer& renderer)
{
    if (!m_uiShader)
        return;

    switch (m_currentScreen)
    {
        case ScreenType::MainMenu:
        {
            int count = m_mainMenu.getButtonCount();

            for (int i = 0; i < count; i++)
            {
                DrawRectCommand cmd;

                cmd.x = m_mainMenu.getButtonX(i);
                cmd.y = m_mainMenu.getButtonY(i);
                cmd.w = m_mainMenu.getButtonWidth(i);
                cmd.h = m_mainMenu.getButtonHeight(i);

                cmd.r = 0.2f;
                cmd.g = 0.7f;
                cmd.b = 1.0f;

                renderer.drawRect(cmd, *m_uiShader);
            }

            break;
        }

        case ScreenType::OneVsAI:
        {
            DrawRectCommand cmd;

            // Back
            cmd.x = m_oneVsAI.getBackButtonX();
            cmd.y = m_oneVsAI.getBackButtonY();
            cmd.w = m_oneVsAI.getBackButtonWidth();
            cmd.h = m_oneVsAI.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            // History
            cmd.x = m_oneVsAI.getHistoryButtonX();
            cmd.y = m_oneVsAI.getHistoryButtonY();
            cmd.w = m_oneVsAI.getHistoryButtonWidth();
            cmd.h = m_oneVsAI.getHistoryButtonHeight();

            cmd.r = 0.3f;
            cmd.g = 0.9f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::One:
        {
            DrawRectCommand cmd;

            cmd.x = m_one.getBackButtonX();
            cmd.y = m_one.getBackButtonY();
            cmd.w = m_one.getBackButtonWidth();
            cmd.h = m_one.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::Match:
        {
            DrawRectCommand cmd;

            cmd.x = m_match.getBackButtonX();
            cmd.y = m_match.getBackButtonY();
            cmd.w = m_match.getBackButtonWidth();
            cmd.h = m_match.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::Moves:
        {
            DrawRectCommand cmd;

            // Back
            cmd.x = m_moves.getBackButtonX();
            cmd.y = m_moves.getBackButtonY();
            cmd.w = m_moves.getBackButtonWidth();
            cmd.h = m_moves.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            // History
            cmd.x = m_moves.getHistoryButtonX();
            cmd.y = m_moves.getHistoryButtonY();
            cmd.w = m_moves.getHistoryButtonWidth();
            cmd.h = m_moves.getHistoryButtonHeight();

            cmd.r = 0.3f;
            cmd.g = 0.9f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::HistoryEndings:
        {
            DrawRectCommand cmd;

            cmd.x = m_historyEndings.getBackButtonX();
            cmd.y = m_historyEndings.getBackButtonY();
            cmd.w = m_historyEndings.getBackButtonWidth();
            cmd.h = m_historyEndings.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::HistoryMoves:
        {
            DrawRectCommand cmd;

            cmd.x = m_historyMoves.getBackButtonX();
            cmd.y = m_historyMoves.getBackButtonY();
            cmd.w = m_historyMoves.getBackButtonWidth();
            cmd.h = m_historyMoves.getBackButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }
    }
}

bool ScreenManager::shouldExit() const
{
    return m_shouldExit;
}