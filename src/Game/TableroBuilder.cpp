#include "TableroBuilder.h"

#include "Tablero.h"
#include "DrawFichaEngine.h"
#include "ImagenManager.h"
#include "Ficha.h"

TableroBuilder::TableroBuilder(
    Tablero& tablero,
    DrawFichaEngine& fichaEngine
)
    : m_tablero(tablero)
    , m_fichaEngine(fichaEngine)
    , m_torreTexture(nullptr)
{
    // tablero base fijo por ahora
    m_tablero = Tablero(3, 3);

    m_tablero.setArea(
        300.0f,
        30.0f,
        450.0f,
        450.0f
    );
}

void TableroBuilder::agregarTorre()
{
    if (!m_torreTexture)
    {
        m_torreTexture = new ImagenManager();
        m_torreTexture->cargar("Debug/torre.png");
    }

    FichaVisual torre;

    torre.tipo = TipoFicha::Torre;

    // posición lógica en tablero
    torre.pos = { 0, 2 };

    torre.textura = m_torreTexture;

    m_fichaEngine.addFicha(torre);
}