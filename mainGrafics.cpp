#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"
#include "DrawFichaEngine.h"

#include "Tablero.h"
#include "TableroBuilder.h"
#include "TextureFichasLoader.h"

int main()
{
    Window window(1280, 720, "RENDER_WINDOW");
    glViewport(0, 0, 1280, 720);

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

    screenManager.setShader(&basicShader);

    // ==========================================
    // TABLERO + ENGINES
    // ==========================================

    Tablero tablero(3, 3);

    DrawTableroEngine drawTableroEngine;
    DrawFichaEngine drawFichaEngine;
    DrawGameEngine drawGameEngine;

    drawGameEngine.setTablero(&tablero);
    drawGameEngine.setTableroEngine(&drawTableroEngine);
    drawGameEngine.setFichaEngine(&drawFichaEngine);

    // ==========================================
    // LOADER (IMPORTANTE: INICIALIZACIÓN)
    // ==========================================

    TextureFichasLoader loader;
    loader.cargarBlancas();
    loader.cargarNegras();

    // ==========================================
    // BUILD DEL TABLERO
    // ==========================================

    TableroBuilder builder(
        tablero,
        drawFichaEngine,
        loader
    );

    builder.agregarTorre();

    // ==========================================
    // LOOP
    // ==========================================

    while (!window.shouldClose() &&
           !screenManager.shouldExit())
    {
        window.pollEvents();

        input.update(window.getNativeWindow());
        screenManager.update(input);

        renderer.begin();
        screenManager.render(renderer);

        if (screenManager.currentScreen() == ScreenType::OneVsAI)
        {
            drawGameEngine.draw(
                renderer,
                basicShader,
                textureShader,
                input
            );
        }

        renderer.end();
        window.display();
    }

    return 0;
}