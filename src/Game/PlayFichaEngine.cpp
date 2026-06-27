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

        renderer.drawFicha(
            cmd,
            shader
        );
    }
}

int PlayFichaEngine::seleccionarFicha(
    float mouseX,
    float mouseY
)
{
    if (m_tablero == nullptr)
    {
        m_selectedIndex = -1;
        return -1;
    }

    float cellW = m_tablero->getCellWidth();
    float cellH = m_tablero->getCellHeight();

    for (size_t i = 0; i < m_fichas.size(); i++)
    {
        const FichaVisual& ficha = m_fichas[i];

        float x = m_tablero->getX()
                + ficha.pos.x * cellW;

        float y = m_tablero->getY()
                + ficha.pos.y * cellH;

        if (mouseX >= x &&
            mouseX < x + cellW &&
            mouseY >= y &&
            mouseY < y + cellH)
        {
            m_selectedIndex = static_cast<int>(i);

            std::cout
                << "FICHA SELECCIONADA -> "
                << "ID=" << m_selectedIndex
                << " POS=("
                << ficha.pos.x
                << ", "
                << ficha.pos.y
                << ")"
                << std::endl;

            return m_selectedIndex;
        }
    }

    m_selectedIndex = -1;

    std::cout
        << "NINGUNA FICHA SELECCIONADA"
        << std::endl;

    return -1;
}