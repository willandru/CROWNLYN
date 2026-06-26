#pragma once

struct GLFWwindow;

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;

    void pollEvents();
    void clear();
    void display();

    GLFWwindow* getNativeWindow() const;

private:
    GLFWwindow* m_window;
};