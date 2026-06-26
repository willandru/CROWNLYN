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

                b.x = m_oneVsAI.getButtonX();
                b.y = m_oneVsAI.getButtonY();
                b.width = m_oneVsAI.getButtonWidth();
                b.height = m_oneVsAI.getButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
                }
            }

            break;
        }

        case ScreenType::One:
        {
            if (input.leftMouseClicked())
            {
                Button b;

                b.x = m_one.getButtonX();
                b.y = m_one.getButtonY();
                b.width = m_one.getButtonWidth();
                b.height = m_one.getButtonHeight();

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

                b.x = m_match.getButtonX();
                b.y = m_match.getButtonY();
                b.width = m_match.getButtonWidth();
                b.height = m_match.getButtonHeight();

                if (b.contains(input.mouseX(), input.mouseY()))
                {
                    m_currentScreen = ScreenType::MainMenu;
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

            cmd.x = m_oneVsAI.getButtonX();
            cmd.y = m_oneVsAI.getButtonY();
            cmd.w = m_oneVsAI.getButtonWidth();
            cmd.h = m_oneVsAI.getButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::One:
        {
            DrawRectCommand cmd;

            cmd.x = m_one.getButtonX();
            cmd.y = m_one.getButtonY();
            cmd.w = m_one.getButtonWidth();
            cmd.h = m_one.getButtonHeight();

            cmd.r = 1.0f;
            cmd.g = 0.3f;
            cmd.b = 0.3f;

            renderer.drawRect(cmd, *m_uiShader);

            break;
        }

        case ScreenType::Match:
        {
            DrawRectCommand cmd;

            cmd.x = m_match.getButtonX();
            cmd.y = m_match.getButtonY();
            cmd.w = m_match.getButtonWidth();
            cmd.h = m_match.getButtonHeight();

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