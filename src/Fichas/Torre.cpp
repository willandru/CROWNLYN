#include "Torre.h"
#include "Nodo.h"

Torre::Torre()
{
}

Torre::~Torre()
{
}

bool Torre::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

std::vector<Posicion> Torre::getMovimientos(const Nodo& estado, Posicion origen) const
{
    std::vector<Posicion> movimientos;

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
            // TODO: lógica de colisión con piezas en Nodo
            // - si hay pieza propia: detener
            // - si hay enemiga: agregar y detener

            movimientos.push_back({x, y});

            x += d[0];
            y += d[1];
        }
    }

    return movimientos;
}