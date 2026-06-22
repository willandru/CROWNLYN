#include "Rey.h"

std::vector<Posicion> Rey::getMovimientos(const Ficha& pieza, const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = pieza.getPosicion();

    const int dirs[8][2] =
    {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
        { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
    };

    for (auto& d : dirs)
    {
        int x = origen.x + d[0];
        int y = origen.y + d[1];

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        // casilla vacía → movimiento válido
        if (!f)
        {
            movimientos.push_back({x, y});
        }
        else
        {
            // casilla ocupada → solo si es enemigo
            if (f->getColor() != pieza.getColor())
            {
                movimientos.push_back({x, y});
            }
        }
    }

    return movimientos;
}

bool Rey::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

const Ficha* Rey::obtenerFichaEn(const Nodo& estado, int x, int y) const
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