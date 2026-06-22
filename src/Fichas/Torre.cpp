#include "Torre.h"

std::vector<Posicion> Torre::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = pieza.getPosicion();

    const int dirs[4][2] =
    {
        { 1, 0 },
        { -1, 0 },
        { 0, 1 },
        { 0, -1 }
    };

    for (auto& d : dirs)
    {
        int x = origen.x + d[0];
        int y = origen.y + d[1];

        while (esValida(estado, x, y))
        {
            const Ficha* f = obtenerFichaEn(estado, x, y);

            if (!f)
            {
                // casilla vacía
                movimientos.push_back({x, y});
            }
            else
            {
                // ocupada → solo si enemigo
                if (f->getColor() != pieza.getColor())
                {
                    movimientos.push_back({x, y});
                }

                break; // siempre bloquea el rayo
            }

            x += d[0];
            y += d[1];
        }
    }

    return movimientos;
}

bool Torre::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

const Ficha* Torre::obtenerFichaEn(const Nodo& estado, int x, int y) const
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