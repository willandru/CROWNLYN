#include "Tablero.h"
#include "Torre.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Torre::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    const Posicion o = pieza.getPosicion();

    const int dirs[4][2] =
    {
        { 1, 0 }, { -1, 0 },
        { 0, 1 }, { 0, -1 }
    };

    for (const auto& d : dirs)
    {
        int x = o.x + d[0];
        int y = o.y + d[1];

        while (esValida(estado, x, y))
        {
            const Ficha* f = obtenerFichaEn(estado, x, y);

            if (!f)
            {
                movimientos.push_back({ x, y });
            }
            else
            {
                if (f->getColor() != pieza.getColor())
                    movimientos.push_back({ x, y });

                break; // bloqueo absoluto del rayo
            }

            x += d[0];
            y += d[1];
        }
    }

    return movimientos;
}

// ======================================================
// ATAQUES (CONTROL REAL DE CASILLAS)
// ======================================================

std::vector<Posicion> Torre::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    const Posicion o = pieza.getPosicion();

    const int dirs[4][2] =
    {
        { 1, 0 }, { -1, 0 },
        { 0, 1 }, { 0, -1 }
    };

    for (const auto& d : dirs)
    {
        int x = o.x + d[0];
        int y = o.y + d[1];

        while (esValida(estado, x, y))
        {
            ataques.push_back({ x, y });

            // 🔴 punto crítico: el rayo se detiene en la primera pieza
            if (obtenerFichaEn(estado, x, y))
                break;

            x += d[0];
            y += d[1];
        }
    }

    return ataques;
}

// ======================================================
// UTILIDADES
// ======================================================

bool Torre::esValida(const Nodo& estado, int x, int y) const
{
    if (!estado.tablero)
        return false;

    return estado.tablero->esValida(x, y);
}

// ======================================================

const Ficha* Torre::obtenerFichaEn(
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