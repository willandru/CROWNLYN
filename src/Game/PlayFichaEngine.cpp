#include "PlayFichaEngine.h"

#include "Renderer.h"
#include "Shader.h"
#include "Tablero.h"
#include "ImagenManager.h"

#include <iostream>

PlayFichaEngine::PlayFichaEngine()
{
    m_tablero = nullptr;
    m_selectedIndex = -1;
}

void PlayFichaEngine::setTablero(Tablero* tablero)
{
    m_tablero = tablero;
}

void PlayFichaEngine::addFicha(const FichaVisual& ficha)
{
    m_fichas.push_back(ficha);
}

void PlayFichaEngine::update(const Input&)
{
}
void PlayFichaEngine::render(
    Renderer& renderer,
    Shader& shader
)
{
    std::cout << "PlayFichaEngine::render()" << std::endl;

    if (!m_tablero)
    {
        return;
    }

    for (const auto& ficha : m_fichas)
    {
        if (!ficha.textura)
        {
            continue;
        }

        DrawFichaCommand cmd;

        float cellW = m_tablero->getCellWidth();
        float cellH = m_tablero->getCellHeight();

        cmd.x = m_tablero->getX()
              + ficha.pos.x * cellW;

        cmd.y = m_tablero->getY()
              + ficha.pos.y * cellH;

        cmd.w = cellW;
        cmd.h = cellH;

        cmd.textura = ficha.textura;

        std::cout
            << "Ficha en ("
            << ficha.pos.x
            << ", "
            << ficha.pos.y
            << ") -> x="
            << cmd.x
            << " y="
            << cmd.y
            << std::endl;

        renderer.drawFicha(
            cmd,
            shader
        );
    }
}