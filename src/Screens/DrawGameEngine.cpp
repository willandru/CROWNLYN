#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"
#include "Input.h"

#include "Tablero.h"
#include "DrawTableroEngine.h"

#include <iostream>

DrawGameEngine::DrawGameEngine()
{
    m_tablero = nullptr;
    m_tableroEngine = nullptr;
}

void DrawGameEngine::setTablero(const Tablero* tablero)
{
    m_tablero = tablero;
}

void DrawGameEngine::setTableroEngine(DrawTableroEngine* engine)
{
    m_tableroEngine = engine;
}

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& shader,
    const Input& input
)
{
    if (!m_tablero || !m_tableroEngine)
        return;

    // 1. RENDER TABLERO
    m_tableroEngine->draw(*m_tablero, renderer, shader);

    // 2. INPUT DEBUG
    if (input.leftMouseClicked())
        {
            float mx = static_cast<float>(input.mouseX());
            float my = static_cast<float>(input.mouseY());

            int id = m_tablero->getCasillaEn(mx, my);

            if (id == -1)
            {
                std::cout << "CLICK FUERA DEL TABLERO\n";
            }
            else
            {
                int x = id % m_tablero->getAncho();
                int y = id / m_tablero->getAncho();

                std::cout << "CLICK CASILLA -> ("
                        << x << ", " << y
                        << ") ID=" << id << "\n";
            }
        }
}