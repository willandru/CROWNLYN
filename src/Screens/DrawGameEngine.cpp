#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"
#include "Input.h"

#include "Tablero.h"
#include "DrawTableroEngine.h"
#include "DrawFichaEngine.h"
#include "TextureFichasLoader.h"

#include "Ficha.h"

#include <iostream>

DrawGameEngine::DrawGameEngine()
{
    m_tablero = nullptr;
    m_tableroEngine = nullptr;
    m_fichaEngine = nullptr;
    m_loader = nullptr;
}

void DrawGameEngine::setTablero(const Tablero* tablero)
{
    m_tablero = tablero;
}

void DrawGameEngine::setTableroEngine(DrawTableroEngine* engine)
{
    m_tableroEngine = engine;
}

void DrawGameEngine::setFichaEngine(DrawFichaEngine* engine)
{
    m_fichaEngine = engine;
}

void DrawGameEngine::setTextureLoader(TextureFichasLoader* loader)
{
    m_loader = loader;
}

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& basicShader,
    Shader& textureShader,
    const Input& input
)
{
    if (!m_tablero || !m_tableroEngine || !m_fichaEngine || !m_loader)
        return;

    // ==========================================
    // TABLERO
    // ==========================================
    for (int i = 0; i < m_tableroEngine->getCantidadCasillas(*m_tablero); i++)
    {
        DrawRectCommand cmd =
            m_tableroEngine->getDrawCommand(*m_tablero, i);

        renderer.drawRect(cmd, basicShader);
    }

    float cellW = m_tablero->getCellWidth();
    float cellH = m_tablero->getCellHeight();

    // ==========================================
    // FICHAS
    // ==========================================
    for (int i = 0; i < m_fichaEngine->getCantidadFichas(); i++)
    {
        const Ficha& ficha = m_fichaEngine->getFicha(i);

        const ImagenManager* tex =
            m_loader->getTextura(ficha.getTipo(), ficha.getColor());

        if (!tex)
            continue;

        DrawFichaCommand cmd;

        cmd.x = m_tablero->getX() + ficha.getPosicion().x * cellW;
        cmd.y = m_tablero->getY() + ficha.getPosicion().y * cellH;
        cmd.w = cellW;
        cmd.h = cellH;
        cmd.textura = tex;

        renderer.drawFicha(cmd, textureShader);
    }

    // ==========================================
    // INPUT
    // ==========================================
    if (!input.leftMouseClicked())
        return;

    float mx = (float)input.mouseX();
    float my = (float)input.mouseY();

    Posicion pos;
    int fichaId = seleccionarFicha(mx, my, pos);

    if (fichaId != -1)
    {
        std::cout << "CLICK FICHA ID=" << fichaId
                  << " POS=(" << pos.x << "," << pos.y << ")\n";
        return;
    }

    int id = m_tablero->getCasillaEn(mx, my);

    if (id == -1)
    {
        std::cout << "CLICK FUERA TABLERO\n";
    }
    else
    {
        int x = id % m_tablero->getAncho();
        int y = id / m_tablero->getAncho();

        std::cout << "CLICK CASILLA (" << x << "," << y << ")\n";
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
        const Ficha& ficha = m_fichaEngine->getFicha(i);

        float x = m_tablero->getX() + ficha.getPosicion().x * cellW;
        float y = m_tablero->getY() + ficha.getPosicion().y * cellH;

        if (mouseX >= x && mouseX < x + cellW &&
            mouseY >= y && mouseY < y + cellH)
        {
            outPos = ficha.getPosicion();
            return i;
        }
    }

    return -1;
}