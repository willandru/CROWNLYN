#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Window::Window(int width, int height, const char* title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display()
{
    glfwSwapBuffers(m_window);
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_window;
}