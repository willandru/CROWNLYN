#include "Input.h"
#include <GLFW/glfw3.h>

Input::Input()
    : m_mouseX(0.0),
      m_mouseY(0.0),
      m_mousePressed(false),
      m_previousMousePressed(false)
{
}

void Input::update(GLFWwindow* window)
{
    m_previousMousePressed = m_mousePressed;

    glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    m_mousePressed = (state == GLFW_PRESS);
}

double Input::mouseX() const
{
    return m_mouseX;
}

double Input::mouseY() const
{
    return m_mouseY;
}

bool Input::leftMousePressed() const
{
    return m_mousePressed;
}

bool Input::leftMouseClicked() const
{
    return m_mousePressed && !m_previousMousePressed;
}