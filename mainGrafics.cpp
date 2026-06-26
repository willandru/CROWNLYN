#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

int main()
{
    Window window(
        1280,
        720,
        "RENDER_WINDOW"
    );

    glViewport(0, 0, 1280, 720); 

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    Shader shader(
        "Debug/basic.vert",
        "Debug/basic.frag"
    );

    screenManager.setShader(&shader);

    while (!window.shouldClose() && !screenManager.shouldExit())
    {
        window.pollEvents();

        input.update(window.getNativeWindow());
        screenManager.update(input);

        renderer.begin();

        screenManager.render(renderer);

        renderer.end();

        window.display();
    }

    return 0;
}