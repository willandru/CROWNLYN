#include "Rey.h"
#include "Nodo.h"

Rey::Rey(Color color, Posicion pos)
    : Ficha(TipoFicha::Rey, color, pos)
{
}

Rey::~Rey()
{
}

bool Rey::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

bool Rey::esCasillaOcupada(const Nodo& estado, int x, int y) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return true;
    }
    return false;
}

bool Rey::esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return f->getColor() != piezaOrigen->getColor();
    }
    return false;
}

std::vector<Posicion> Rey::getMovimientos(const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = this->getPosicion();
    const Ficha* piezaOrigen = this;

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

        if (esCasillaOcupada(estado, x, y))
        {
            if (esCaptura(estado, x, y, piezaOrigen))
                movimientos.push_back({x, y});
        }
        else
        {
            movimientos.push_back({x, y});
        }
    }

    return movimientos;
}