#include "TableroBuilder.h"

TableroBuilder::TableroBuilder()
    :
    m_tablero(1,1),
    m_nextId(0)
{
    m_loader.cargarBlancas();
    m_loader.cargarNegras();
}

void TableroBuilder::crearTablero(
    int ancho,
    int alto,
    float x,
    float y,
    float w,
    float h
)
{
    m_tablero = Tablero(
        ancho,
        alto
    );

    m_tablero.setArea(
        x,
        y,
        w,
        h
    );

    m_fichaEngine.clear();

    m_nextId = 0;
}

void TableroBuilder::agregarFicha(
    TipoFicha tipo,
    Color color,
    const Posicion& pos
)
{
    if (!m_tablero.esValida(
            pos.x,
            pos.y))
    {
        return;
    }

    m_fichaEngine.addFicha(

        Ficha(

            m_nextId++,

            tipo,

            color,

            pos
        )
    );
}

void TableroBuilder::clear()
{
    m_fichaEngine.clear();

    m_nextId = 0;
}

const Tablero& TableroBuilder::getTablero() const
{
    return m_tablero;
}

DrawFichaEngine&
TableroBuilder::getFichaEngine()
{
    return m_fichaEngine;
}

TextureFichasLoader&
TableroBuilder::getTextureLoader()
{
    return m_loader;
}

void TableroBuilder::agregarTorre()
{
    agregarFicha(
        TipoFicha::Dama,
        Color::Negra,
        Posicion{1, 1}
    );
}