#include <iostream>

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
#include "DecisionTreeEngine.h"

#include "RandomAI.h"

//==================================================

int main()
{
    Window window(1280, 720, "CROWNLYN");
    glViewport(0, 0, 1280, 720);

    Renderer renderer;
    Input input;
    ScreenManager screenManager;

    Shader basicShader("Debug/basic.vert", "Debug/basic.frag");
    Shader textureShader("Debug/texture.vert", "Debug/texture.frag");

    screenManager.setShader(&basicShader);

    //==================================================
    // GAME STATE
    //==================================================

    Arbol arbol;
    TableroBuilder builder;
    NuevaPartidaEngine nuevaPartida;

    Nodo* nodoRaiz =
        nuevaPartida.crearPartida(arbol, builder);

    //==================================================
    // DEBUG TREE INIT
    //==================================================

    DecisionTreeEngine treeEngine;

    treeEngine.expandirNodo(nodoRaiz);
    treeEngine.imprimirRama(nodoRaiz);

    std::cout << "\n=====================================\n";
    std::cout << "NODO RAIZ\n";
    std::cout << "HIJOS GENERADOS: " << nodoRaiz->hijos.size() << "\n";
    std::cout << "=====================================\n\n";

    //==================================================
    // PLAY ENGINE (HUMAN)
    //==================================================

    PlayFichaEngine playFichaEngine;
    playFichaEngine.setBuilder(&builder);

    //==================================================
    // AI ENGINE
    //==================================================

    RandomAI ia;

    //==================================================
    // RENDER ENGINE
    //==================================================

    DrawTableroEngine drawTableroEngine;

    DrawGameEngine drawGameEngine;
    drawGameEngine.setBuilder(&builder);
    drawGameEngine.setTableroEngine(&drawTableroEngine);
    drawGameEngine.setPlayEngine(&playFichaEngine);

    //==================================================
    // LOOP
    //==================================================

    while (!window.shouldClose() && !screenManager.shouldExit())
    {
        window.pollEvents();
        input.update(window.getNativeWindow());
        screenManager.update(input);

        //==================================================
        // HUMAN + AI TURN SYSTEM
        //==================================================

        if (screenManager.currentScreen() == ScreenType::OneVsAI)
        {
            Nodo* actual = builder.getNodo();

            if (actual)
            {
                //==================================================
                // AI TURN
                //==================================================
                if (actual->turnoActual == Color::Negra)
                {
                    Nodo* siguiente = ia.jugar(actual);

                    if (siguiente)
                    {
                        actual->agregarHijo(siguiente);
                        builder.setNodo(siguiente);

                        std::cout << "[AI MOVE EXECUTED]\n";
                    }
                }
                else
                {
                    //==================================================
                    // HUMAN TURN
                    //==================================================
                    playFichaEngine.update(input);
                }
            }
        }

        //==================================================
        // RENDER
        //==================================================

        renderer.begin();

        screenManager.render(renderer);

        if (screenManager.currentScreen() == ScreenType::OneVsAI)
        {
            drawGameEngine.draw(renderer, basicShader, textureShader);
        }

        renderer.end();
        window.display();
    }

    return 0;
}