#include "TableroBuilder.h"

#include "Tablero.h"
#include "Ficha.h"

//==================================================
// CONSTRUCTOR
//==================================================

TableroBuilder::TableroBuilder()
    :
    m_nodo(nullptr),
    m_nextId(0)
{
    m_loader.cargarBlancas();
    m_loader.cargarNegras();
}

//==================================================
// NODO
//==================================================

void TableroBuilder::setNodo(
    Nodo* nodo
)
{
    m_nodo = nodo;
}

Nodo* TableroBuilder::getNodo()
{
    return m_nodo;
}

const Nodo* TableroBuilder::getNodo() const
{
    return m_nodo;
}

//==================================================
// TABLERO
//==================================================

void TableroBuilder::crearTablero(
    int ancho,
    int alto,
    float x,
    float y,
    float w,
    float h
)
{
    if (!m_nodo)
        return;

    // destruir tablero anterior
    delete m_nodo->tablero;

    m_nodo->tablero =
        new Tablero(
            ancho,
            alto
        );

    m_nodo->tablero->setArea(
        x,
        y,
        w,
        h
    );

    m_nodo->piezas.clear();

    m_nextId = 0;
}

//==================================================
// LIMPIAR
//==================================================

void TableroBuilder::clear()
{
    if (!m_nodo)
        return;

    m_nodo->piezas.clear();

    m_nodo->hijos.clear();

    m_nextId = 0;
}

//==================================================
// AGREGAR FICHA
//==================================================

void TableroBuilder::agregarFicha(
    TipoFicha tipo,
    Color color,
    const Posicion& pos
)
{
    if (!m_nodo)
        return;

    if (!m_nodo->tablero)
        return;

    if (!m_nodo->tablero->esValida(
            pos.x,
            pos.y))
    {
        return;
    }

    m_nodo->piezas.emplace_back(
        m_nextId++,
        tipo,
        color,
        pos
    );
}

//==================================================
// PEONES
//==================================================

void TableroBuilder::agregarFilaPeones(
    Color color
)
{
    int fila =
        color == Color::Blanca
        ? 1
        : 6;

    for (int x = 0; x < 8; x++)
    {
        agregarFicha(
            TipoFicha::Peon,
            color,
            { x, fila }
        );
    }
}

//==================================================
// PIEZAS MAYORES
//==================================================

void TableroBuilder::agregarPiezasIniciales(
    Color color
)
{
    int fila =
        color == Color::Blanca
        ? 0
        : 7;

    TipoFicha piezas[8]
    {
        TipoFicha::Torre,
        TipoFicha::Caballo,
        TipoFicha::Alfil,
        TipoFicha::Dama,
        TipoFicha::Rey,
        TipoFicha::Alfil,
        TipoFicha::Caballo,
        TipoFicha::Torre
    };

    for (int x = 0; x < 8; x++)
    {
        agregarFicha(
            piezas[x],
            color,
            { x, fila }
        );
    }
}

//==================================================
// POSICIÓN INICIAL
//==================================================

void TableroBuilder::crearConfiguracionInicial()
{
    agregarPiezasIniciales(Color::Blanca);
    agregarFilaPeones(Color::Blanca);

    agregarPiezasIniciales(Color::Negra);
    agregarFilaPeones(Color::Negra);
}

//==================================================
// TEXTURAS
//==================================================

TextureFichasLoader&
TableroBuilder::getTextureLoader()
{
    return m_loader;
}

const TextureFichasLoader&
TableroBuilder::getTextureLoader() const
{
    return m_loader;
}

void TableroBuilder::avanzarNodo(
    Nodo* nodo
)
{
    if (!nodo)
        return;

    m_nodo = nodo;
}