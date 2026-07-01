#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Input.h"
#include "ScreenManager.h"

#include "Nodo.h"
#include "Arbol.h"

#include "TableroBuilder.h"
#include "NuevaPartidaEngine.h"

#include "DrawGameEngine.h"
#include "DrawTableroEngine.h"

#include "PlayFichaEngine.h"

int main()
{
    //--------------------------------------------------
    // WINDOW
    //--------------------------------------------------

    Window window(
        1280,
        720,
        "CROWNLYN"
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

    //--------------------------------------------------
    // SHADERS
    //--------------------------------------------------

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

    //--------------------------------------------------
    // GAME STATE
    //--------------------------------------------------

    Arbol arbol;

    TableroBuilder builder;

    NuevaPartidaEngine nuevaPartida;

    Nodo* nodoRaiz =
        nuevaPartida.crearPartida(
            arbol,
            builder
        );

    //--------------------------------------------------
    // PLAY ENGINE
    //--------------------------------------------------

    PlayFichaEngine playFichaEngine;

    playFichaEngine.setBuilder(
        &builder
    );

    //--------------------------------------------------
    // DRAW ENGINES
    //--------------------------------------------------

    DrawTableroEngine drawTableroEngine;

    DrawGameEngine drawGameEngine;

    drawGameEngine.setBuilder(
        &builder
    );

    drawGameEngine.setTableroEngine(
        &drawTableroEngine
    );

    drawGameEngine.setPlayEngine(
        &playFichaEngine
    );

    //--------------------------------------------------
    // GAME LOOP
    //--------------------------------------------------

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

        //--------------------------------------------------
        // GAMEPLAY
        //--------------------------------------------------

        if (
            screenManager.currentScreen() ==
            ScreenType::OneVsAI
        )
        {
            playFichaEngine.update(
                input
            );
        }

        //--------------------------------------------------
        // RENDER
        //--------------------------------------------------

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
                textureShader
            );
        }

        renderer.end();

        window.display();
    }

    return 0;
}