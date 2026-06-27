#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"
#include "DrawFichaEngine.h"
#include "Tablero.h"

#include "ImagenManager.h"
#include "Ficha.h"

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

    // ---------------------------------
    // SHADERS
    // ---------------------------------

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

    // ---------------------------------
    // TABLERO
    // ---------------------------------

    Tablero tablero(
        3,
        3
    );

    tablero.setArea(
        300.0f,
        30.0f,
        450.0f,
        450.0f
    );

    // ---------------------------------
    // ENGINES
    // ---------------------------------

    DrawTableroEngine drawTableroEngine;
    DrawFichaEngine drawFichaEngine;
    DrawGameEngine drawGameEngine;

    drawGameEngine.setTablero(
        &tablero
    );

    drawGameEngine.setTableroEngine(
        &drawTableroEngine
    );

    drawGameEngine.setFichaEngine(
        &drawFichaEngine
    );

    // ---------------------------------
    // TEXTURAS
    // ---------------------------------

    ImagenManager torre;

    torre.cargar(
        "Debug/torre.png"
    );

    // ---------------------------------
    // FICHAS
    // ---------------------------------

    FichaVisual ficha;

    ficha.tipo = TipoFicha::Torre;
    ficha.pos = { 0, 0 };
    ficha.textura = &torre;

    drawFichaEngine.addFicha(
        ficha
    );

    // ---------------------------------
    // LOOP
    // ---------------------------------

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

        renderer.begin();

        screenManager.render(
            renderer
        );

        if (
            screenManager.currentScreen() ==
            ScreenType::OneVsAI
        )
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