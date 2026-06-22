#include "Rey.h"

// ======================================================
// MOVIMIENTOS DEL REY (SIN FILTRO DE JAQUE)
// ======================================================

std::vector<Posicion> Rey::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    const Posicion origen = pieza.getPosicion();

    const int dirs[8][2] =
    {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
        { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
    };

    for (const auto& d : dirs)
    {
        int x = origen.x + d[0];
        int y = origen.y + d[1];

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        // casilla vacía
        if (!f)
        {
            movimientos.push_back({ x, y });
            continue;
        }

        // captura solo si es enemigo
        if (f->getColor() != pieza.getColor())
        {
            movimientos.push_back({ x, y });
        }
    }

    return movimientos;
}

// ======================================================
// VALIDACIÓN TABLERO
// ======================================================

bool Rey::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

// ======================================================
// BUSCAR PIEZA EN CASILLA
// ======================================================

const Ficha* Rey::obtenerFichaEn(
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