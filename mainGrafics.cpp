#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"
#include "PlayFichaEngine.h"
#include "TableroBuilder.h"

int main()
{
    Window window(
        1280,
        720,
        "RENDER_WINDOW"
    );

    glViewport(
        0,
        0,
        1280,
        720
    );

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    // ==========================================
    // SHADERS
    // ==========================================

    Shader basicShader(
        "Debug/basic.vert",
        "Debug/basic.frag"
    );

    Shader textureShader(
        "Debug/texture.vert",
        "Debug/texture.frag"
    );

    screenManager.setShader(
        &basicShader
    );

    // ==========================================
    // ENGINES
    // ==========================================

    DrawTableroEngine drawTableroEngine;

    DrawGameEngine drawGameEngine;

    PlayFichaEngine playFichaEngine;

    TableroBuilder builder;

    builder.crearTablero(
        8,
        8
    );

    builder.crearConfiguracionInicial();

    drawGameEngine.setBuilder(
        &builder
    );

    drawGameEngine.setTableroEngine(
        &drawTableroEngine
    );

    playFichaEngine.setBuilder(
        &builder
    );

    // ==========================================
    // LOOP
    // ==========================================

    while (
        !window.shouldClose() &&
        !screenManager.shouldExit()
    )
    {
        window.pollEvents();

        input.update(
            window.getNativeWindow()
        );

        screenManager.update(
            input
        );

        // ==========================================
        // GAMEPLAY
        // ==========================================

        if (
            screenManager.currentScreen()
            == ScreenType::OneVsAI
        )
        {
            playFichaEngine.update(
                input
            );
        }

        // ==========================================
        // RENDER
        // ==========================================

        renderer.begin();

        screenManager.render(
            renderer
        );

        if (
            screenManager.currentScreen()
            == ScreenType::OneVsAI
        )
        {
            drawGameEngine.draw(
                renderer,
                basicShader,
                textureShader
            );
        }

        renderer.end();

        window.display();
    }

    return 0;
}