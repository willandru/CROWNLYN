#include "DrawGameEngine.h"

#include "Renderer.h"
#include "Shader.h"

#include "TableroBuilder.h"

#include "Tablero.h"
#include "DrawFichaEngine.h"
#include "DrawTableroEngine.h"
#include "TextureFichasLoader.h"

DrawGameEngine::DrawGameEngine()
{
    m_builder = nullptr;
    m_tableroEngine = nullptr;
}

void DrawGameEngine::setBuilder(
    TableroBuilder* builder
)
{
    m_builder = builder;
}

void DrawGameEngine::setTableroEngine(
    DrawTableroEngine* engine
)
{
    m_tableroEngine = engine;
}

void DrawGameEngine::draw(
    Renderer& renderer,
    Shader& basicShader,
    Shader& textureShader
)
{
    if (!m_builder)
        return;

    if (!m_tableroEngine)
        return;

    const Tablero& tablero =
        m_builder->getTablero();

    DrawFichaEngine& fichaEngine =
        m_builder->getFichaEngine();

    TextureFichasLoader& loader =
        m_builder->getTextureLoader();

    // ==========================================
    // TABLERO
    // ==========================================

    for (
        int i = 0;
        i < m_tableroEngine->getCantidadCasillas(tablero);
        i++
    )
    {
        DrawRectCommand cmd =
            m_tableroEngine->getDrawCommand(
                tablero,
                i
            );

        renderer.drawRect(
            cmd,
            basicShader
        );
    }

    // ==========================================
    // FICHAS
    // ==========================================

    float cellW =
        tablero.getCellWidth();

    float cellH =
        tablero.getCellHeight();

    for (
        int i = 0;
        i < fichaEngine.getCantidadFichas();
        i++
    )
    {
        const Ficha& ficha =
            fichaEngine.getFicha(i);

        const ImagenManager* textura =
            loader.getTextura(
                ficha.getTipo(),
                ficha.getColor()
            );

        if (!textura)
            continue;

        DrawFichaCommand cmd;

        cmd.x =
            tablero.getX()
            + ficha.getPosicion().x * cellW;

        cmd.y =
            tablero.getY()
            + ficha.getPosicion().y * cellH;

        cmd.w = cellW;
        cmd.h = cellH;

        cmd.textura = textura;

        renderer.drawFicha(
            cmd,
            textureShader
        );
    }
}