#include "Torre.h"
#include "Nodo.h"

Torre::Torre(Color color, Posicion pos)
    : Ficha(TipoFicha::Torre, color, pos)
{
}

Torre::~Torre()
{
}

bool Torre::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

bool Torre::esCasillaOcupada(const Nodo& estado, int x, int y) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return true;
    }
    return false;
}

bool Torre::esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return f->getColor() != piezaOrigen->getColor();
    }
    return false;
}

std::vector<Posicion> Torre::getMovimientos(const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = this->getPosicion();

    const Ficha* piezaOrigen = this;

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
            if (esCasillaOcupada(estado, x, y))
            {
                if (esCaptura(estado, x, y, piezaOrigen))
                    movimientos.push_back({x, y});

                break;
            }

            movimientos.push_back({x, y});

            x += d[0];
            y += d[1];
        }
    }

    return movimientos;
}