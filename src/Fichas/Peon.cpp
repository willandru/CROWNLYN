#include "Peon.h"

std::vector<Posicion> Peon::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion o = pieza.getPosicion();
    int dir = (pieza.getColor() == Color::Blanca) ? -1 : 1;

    int xFront = o.x + dir;
    int yFront = o.y;

    if (esValida(estado, xFront, yFront) &&
        !obtenerFichaEn(estado, xFront, yFront))
    {
        movimientos.push_back({xFront, yFront});
    }

    return movimientos;
}

std::vector<Posicion> Peon::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    Posicion o = pieza.getPosicion();
    int dir = (pieza.getColor() == Color::Blanca) ? -1 : 1;

    const int diag[2][2] =
    {
        {dir, -1},
        {dir,  1}
    };

    for (auto& d : diag)
    {
        int x = o.x + d[0];
        int y = o.y + d[1];

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        if (f && f->getColor() != pieza.getColor())
        {
            ataques.push_back({x, y});
        }
    }

    return ataques;
}

bool Peon::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

const Ficha* Peon::obtenerFichaEn(const Nodo& estado, int x, int y) const
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