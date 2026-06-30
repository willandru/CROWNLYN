#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"

#include "TableroBuilder.h"
#include "DrawTableroEngine.h"
#include "TextureFichasLoader.h"

#include "Nodo.h"
#include "Ficha.h"
#include "Tablero.h"

DrawGameEngine::DrawGameEngine()
{
    m_builder = nullptr;
    m_tableroEngine = nullptr;
}

void DrawGameEngine::setBuilder(TableroBuilder* builder)
{
    m_builder = builder;
}

void DrawGameEngine::setTableroEngine(DrawTableroEngine* engine)
{
    m_tableroEngine = engine;
}

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& basicShader,
    Shader& textureShader
)
{
    if (!m_builder || !m_tableroEngine)
        return;

    Nodo* nodo = m_builder->getNodo();
    if (!nodo || !nodo->tablero)
        return;

    // ============================
    // FIX: tablero es puntero
    // ============================
    Tablero* tablero = nodo->tablero;

    TextureFichasLoader& loader =
        m_builder->getTextureLoader();

    // =====================================================
    // TABLERO
    // =====================================================

    const int cantidadCasillas =
        m_tableroEngine->getCantidadCasillas(*tablero);

    for (int i = 0; i < cantidadCasillas; i++)
    {
        DrawRectCommand cmd =
            m_tableroEngine->getDrawCommand(*tablero, i);

        renderer.drawRect(cmd, basicShader);
    }

    // =====================================================
    // FICHAS
    // =====================================================

    const float cellW = tablero->getCellWidth();
    const float cellH = tablero->getCellHeight();

    const float tableroX = tablero->getX();
    const float tableroY = tablero->getY();

    for (const Ficha& ficha : nodo->piezas)
    {
        const ImagenManager* textura =
            loader.getTextura(
                ficha.getTipo(),
                ficha.getColor()
            );

        if (!textura)
            continue;

        DrawFichaCommand cmd;

        cmd.x = tableroX + ficha.getPosicion().x * cellW;
        cmd.y = tableroY + ficha.getPosicion().y * cellH;

        cmd.w = cellW;
        cmd.h = cellH;

        cmd.textura = textura;

        renderer.drawFicha(cmd, textureShader);
    }
}