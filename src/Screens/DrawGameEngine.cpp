#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"
#include "Input.h"

#include "Tablero.h"
#include "DrawTableroEngine.h"
#include "DrawFichaEngine.h"

#include <iostream>

DrawGameEngine::DrawGameEngine()
{
    m_tablero = nullptr;
    m_tableroEngine = nullptr;
    m_fichaEngine = nullptr;
}

void DrawGameEngine::setTablero(
    const Tablero* tablero
)
{
    m_tablero = tablero;
}

void DrawGameEngine::setTableroEngine(
    DrawTableroEngine* engine
)
{
    m_tableroEngine = engine;
}

void DrawGameEngine::setFichaEngine(
    DrawFichaEngine* engine
)
{
    m_fichaEngine = engine;
}

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& basicShader,
    Shader& textureShader,
    const Input& input
)
{
    if (m_tablero == nullptr)
    {
        return;
    }

    if (m_tableroEngine == nullptr)
    {
        return;
    }

    if (m_fichaEngine == nullptr)
    {
        return;
    }

    // ==========================================
    // DIBUJAR TABLERO
    // ==========================================

    for (
        int i = 0;
        i < m_tableroEngine->getCantidadCasillas(
                *m_tablero
            );
        i++
    )
    {
        DrawRectCommand cmd =
            m_tableroEngine->getDrawCommand(
                *m_tablero,
                i
            );

        renderer.drawRect(
            cmd,
            basicShader
        );
    }

    // ==========================================
    // DIBUJAR FICHAS
    // ==========================================

    float cellW =
        m_tablero->getCellWidth();

    float cellH =
        m_tablero->getCellHeight();

    for (
        int i = 0;
        i < m_fichaEngine->getCantidadFichas();
        i++
    )
    {
        const FichaVisual& ficha =
            m_fichaEngine->getFicha(i);

        if (ficha.textura == nullptr)
        {
            continue;
        }

        DrawFichaCommand cmd;

        cmd.x =
            m_tablero->getX()
            + ficha.pos.x * cellW;

        cmd.y =
            m_tablero->getY()
            + ficha.pos.y * cellH;

        cmd.w = cellW;
        cmd.h = cellH;

        cmd.textura =
            ficha.textura;

        renderer.drawFicha(
            cmd,
            textureShader
        );
    }

        // ==========================================
    // INPUT
    // ==========================================

    if (input.leftMouseClicked())
    {
        float mx =
            static_cast<float>(
                input.mouseX()
            );

        float my =
            static_cast<float>(
                input.mouseY()
            );

        // ======================================
        // 1. CHECK FICHA
        // ======================================
        Posicion posFicha;
        int fichaId =
            seleccionarFicha(mx, my, posFicha);

        if (fichaId != -1)
        {
            std::cout
                << "CLICK FICHA -> ID="
                << fichaId
                << " POS=("
                << posFicha.x
                << ", "
                << posFicha.y
                << ")"
                << std::endl;

            return; // prioridad ficha sobre tablero
        }

        // ======================================
        // 2. CHECK TABLERO
        // ======================================
        int id =
            m_tablero->getCasillaEn(
                mx,
                my
            );

        if (id == -1)
        {
            std::cout
                << "CLICK FUERA DEL TABLERO"
                << std::endl;
        }
        else
        {
            int x =
                id %
                m_tablero->getAncho();

            int y =
                id /
                m_tablero->getAncho();

            std::cout
                << "CLICK CASILLA -> ("
                << x
                << ", "
                << y
                << ") ID="
                << id
                << std::endl;
        }
    }
}


int DrawGameEngine::seleccionarFicha(
    float mouseX,
    float mouseY,
    Posicion& outPos
)
{
    if (!m_tablero || !m_fichaEngine)
        return -1;

    float cellW = m_tablero->getCellWidth();
    float cellH = m_tablero->getCellHeight();

    int count = m_fichaEngine->getCantidadFichas();

    for (int i = 0; i < count; i++)
    {
        const FichaVisual& ficha = m_fichaEngine->getFicha(i);

        float x = m_tablero->getX() + ficha.pos.x * cellW;
        float y = m_tablero->getY() + ficha.pos.y * cellH;

        if (mouseX >= x && mouseX < x + cellW &&
            mouseY >= y && mouseY < y + cellH)
        {
            outPos = ficha.pos;
            return i;
        }
    }

    return -1;
}