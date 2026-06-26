#pragma once

struct GLFWwindow;

class Input
{
public:

    Input();

    void update(
        GLFWwindow* window
    );

    double mouseX() const;

    double mouseY() const;

    bool leftMousePressed() const;

    bool leftMouseClicked() const;

private:

    double m_mouseX;
    double m_mouseY;

    bool m_mousePressed;
    bool m_previousMousePressed;
};