#include "Caballo.h"
#include "Tablero.h"
// ======================================================
// MOVIMIENTOS LEGALES (SALTOS)
// ======================================================

std::vector<Posicion> Caballo::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    const Posicion o = pieza.getPosicion();

    const int jumps[8][2] =
    {
        { 2, 1 }, { 2, -1 },
        { -2, 1 }, { -2, -1 },
        { 1, 2 }, { 1, -2 },
        { -1, 2 }, { -1, -2 }
    };

    for (const auto& j : jumps)
    {
        int x = o.x + j[0];
        int y = o.y + j[1];

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        if (!f)
        {
            movimientos.push_back({x, y});
        }
        else if (f->getColor() != pieza.getColor())
        {
            movimientos.push_back({x, y});
        }
    }

    return movimientos;
}

// ======================================================
// ATAQUES (CONTROL DE CASILLAS - SIN DEPENDENCIAS)
// ======================================================

std::vector<Posicion> Caballo::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    const Posicion o = pieza.getPosicion();

    const int jumps[8][2] =
    {
        { 2, 1 }, { 2, -1 },
        { -2, 1 }, { -2, -1 },
        { 1, 2 }, { 1, -2 },
        { -1, 2 }, { -1, -2 }
    };

    for (const auto& j : jumps)
    {
        int x = o.x + j[0];
        int y = o.y + j[1];

        if (esValida(estado, x, y))
        {
            // el caballo controla la casilla aunque esté vacía
            ataques.push_back({x, y});
        }
    }

    return ataques;
}

// ======================================================
// UTILIDADES
// ======================================================

bool Caballo::esValida(const Nodo& estado, int x, int y) const
{
    if (!estado.tablero)
        return false;

    return estado.tablero->esValida(x, y);
}

const Ficha* Caballo::obtenerFichaEn(
    const Nodo& estado,
    int x,
    int y) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getPosicion().x == x &&
            f.getPosicion().y == y)
        {
            return &f;
        }
    }

    return nullptr;
}