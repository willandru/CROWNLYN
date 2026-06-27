#include "TableroBuilder.h"

#include "Tablero.h"
#include "DrawFichaEngine.h"
#include "TextureFichasLoader.h"

TableroBuilder::TableroBuilder(
    Tablero& tablero,
    DrawFichaEngine& fichaEngine,
    TextureFichasLoader& loader
)
    : m_tablero(tablero)
    , m_fichaEngine(fichaEngine)
    , m_loader(loader)
{
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
    Posicion spawnPos{1, 1};

    if (!m_tablero.esValida(spawnPos.x, spawnPos.y))
        return;

    // CREACIÓN DIRECTA (SIN loader lógico)
    Ficha torre(
        0,                  // id debug
        TipoFicha::Torre,
        Color::Blanca,
        spawnPos
    );

    m_fichaEngine.addFicha(torre);
}