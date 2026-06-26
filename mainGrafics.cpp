#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"
#include "Tablero.h"

int main()
{
    Window window(1280, 720, "RENDER_WINDOW");

    glViewport(0, 0, 1280, 720);

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    Shader shader(
        "Debug/basic.vert",
        "Debug/basic.frag"
    );

    screenManager.setShader(&shader);

    // ---------------------------
    // GAME SYSTEM
    // ---------------------------
    DrawTableroEngine drawTableroEngine;
    DrawGameEngine drawGameEngine;
    Tablero tablero(3, 3);

    tablero.setArea(300.0f, 30.0f, 450.0f, 450.0f);

    drawGameEngine.setTablero(&tablero);
    drawGameEngine.setTableroEngine(&drawTableroEngine);

    while (!window.shouldClose() && !screenManager.shouldExit())
    {
        window.pollEvents();

        input.update(window.getNativeWindow());
        screenManager.update(input);

        renderer.begin();

        screenManager.render(renderer);

        // ---------------------------
        // TABLERO REAL
        // ---------------------------
        if (screenManager.currentScreen() == ScreenType::OneVsAI)
        {
            drawGameEngine.draw(renderer, shader, input);
        }

        renderer.end();

        window.display();
    }

    return 0;
}