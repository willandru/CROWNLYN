#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"
#include "Tablero.h"

#include "PlayFichaEngine.h"
#include "ImagenManager.h"
#include "Ficha.h"

int main()
{
    Window window(1280, 720, "RENDER_WINDOW");

    glViewport(0, 0, 1280, 720);

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    // ---------------------------------
    // SHADER PARA GEOMETRÍA
    // ---------------------------------
    Shader basicShader(
        "Debug/basic.vert",
        "Debug/basic.frag"
    );

    // ---------------------------------
    // SHADER PARA TEXTURAS
    // ---------------------------------
    Shader textureShader(
        "Debug/texture.vert",
        "Debug/texture.frag"
    );

    screenManager.setShader(&basicShader);

    // ---------------------------------
    // GAME SYSTEM
    // ---------------------------------
    DrawTableroEngine drawTableroEngine;
    DrawGameEngine drawGameEngine;
    Tablero tablero(3, 3);

    tablero.setArea(300.0f, 30.0f, 450.0f, 450.0f);

    drawGameEngine.setTablero(&tablero);
    drawGameEngine.setTableroEngine(&drawTableroEngine);

    // ---------------------------------
    // TEXTURAS
    // ---------------------------------
    ImagenManager torre;

    torre.cargar("Debug/torre.png");

    // ---------------------------------
    // FICHAS
    // ---------------------------------
    PlayFichaEngine fichaEngine;

    fichaEngine.setTablero(&tablero);

    FichaVisual ficha;

    ficha.tipo = TipoFicha::Torre;
    ficha.pos = {0, 0};
    ficha.textura = &torre;

    fichaEngine.addFicha(ficha);

    // ---------------------------------
    // LOOP
    // ---------------------------------
    while (!window.shouldClose() &&
           !screenManager.shouldExit())
    {
        window.pollEvents();

        input.update(window.getNativeWindow());

        if (input.leftMouseClicked())
        {
            fichaEngine.seleccionarFicha(
                static_cast<float>(input.mouseX()),
                static_cast<float>(input.mouseY())
            );
        }
        screenManager.update(input);

        renderer.begin();

        screenManager.render(renderer);

        if (screenManager.currentScreen() == ScreenType::OneVsAI)
        {
            // Tablero
            drawGameEngine.draw(
                renderer,
                basicShader,
                input
            );

            // Fichas
            fichaEngine.render(
                renderer,
                textureShader
            );
        }

        renderer.end();

        window.display();
    }

    return 0;
}