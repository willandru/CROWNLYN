#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"

#include "TableroBuilder.h"
#include "DrawTableroEngine.h"
#include "PlayFichaEngine.h"

#include "TextureFichasLoader.h"

#include "Nodo.h"
#include "Ficha.h"
#include "Tablero.h"
#include "Posicion.h"

#include <vector>

//==================================================
// CONSTRUCTOR
//==================================================

DrawGameEngine::DrawGameEngine()
{
    m_builder = nullptr;
    m_tableroEngine = nullptr;
    m_playEngine = nullptr;
}

//==================================================

void DrawGameEngine::setBuilder(
    TableroBuilder* builder
)
{
    m_builder = builder;
}

//==================================================

void DrawGameEngine::setTableroEngine(
    DrawTableroEngine* engine
)
{
    m_tableroEngine = engine;
}

//==================================================

void DrawGameEngine::setPlayEngine(
    PlayFichaEngine* engine
)
{
    m_playEngine = engine;
}

//==================================================

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& basicShader,
    Shader& textureShader
)
{
    //--------------------------------------------------
    // VALIDACIONES
    //--------------------------------------------------

    if (!m_builder)
        return;

    if (!m_tableroEngine)
        return;

    Nodo* nodo =
        m_builder->getNodo();

    if (!nodo)
        return;

    if (!nodo->tablero)
        return;

    Tablero* tablero =
        nodo->tablero;

    TextureFichasLoader& loader =
        m_builder->getTextureLoader();

    //--------------------------------------------------
    // DATOS DEL TABLERO
    //--------------------------------------------------

    const float cellW =
        tablero->getCellWidth();

    const float cellH =
        tablero->getCellHeight();

    const float tableroX =
        tablero->getX();

    const float tableroY =
        tablero->getY();

    //--------------------------------------------------
    // TABLERO
    //--------------------------------------------------

    const int cantidadCasillas =
        m_tableroEngine->getCantidadCasillas(
            *tablero
        );

    for (int i = 0; i < cantidadCasillas; i++)
    {
        DrawRectCommand cmd =
            m_tableroEngine->getDrawCommand(
                *tablero,
                i
            );

        renderer.drawRect(
            cmd,
            basicShader
        );
    }

    //--------------------------------------------------
    // MOVIMIENTOS POSIBLES
    //--------------------------------------------------

    if (m_playEngine)
    {
        const std::vector<Posicion>& movimientos =
            m_playEngine->getMovimientosPosibles();

        for (const Posicion& pos : movimientos)
        {
            DrawRectCommand cmd;

            cmd.x =
                tableroX +
                pos.x * cellW;

            cmd.y =
                tableroY +
                pos.y * cellH;

            cmd.w = cellW;
            cmd.h = cellH;

            // Verde para indicar movimiento válido
            cmd.r = 0.20f;
            cmd.g = 0.80f;
            cmd.b = 0.20f;

            renderer.drawRect(
                cmd,
                basicShader
            );
        }
    }

    //--------------------------------------------------
    // FICHAS
    //--------------------------------------------------

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

        cmd.x =
            tableroX +
            ficha.getPosicion().x * cellW;

        cmd.y =
            tableroY +
            ficha.getPosicion().y * cellH;

        cmd.w = cellW;
        cmd.h = cellH;

        cmd.textura = textura;

        renderer.drawFicha(
            cmd,
            textureShader
        );
    }
}