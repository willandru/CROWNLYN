#include "Peon.h"

std::vector<Posicion> Peon::getMovimientos(const Ficha& pieza, const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = pieza.getPosicion();

    int direccion = (pieza.getColor() == Color::Blanca) ? -1 : 1;

    // movimiento hacia adelante
    int xFront = origen.x + direccion;
    int y = origen.y;

    if (esValida(estado, xFront, y) && !esCasillaOcupada(estado, xFront, y))
    {
        movimientos.push_back({xFront, y});
    }

    // capturas diagonales
    int xLeft = origen.x + direccion;
    int yLeft = origen.y - 1;

    int xRight = origen.x + direccion;
    int yRight = origen.y + 1;

    if (esValida(estado, xLeft, yLeft) &&
        esCasillaOcupada(estado, xLeft, yLeft) &&
        esCaptura(estado, xLeft, yLeft, pieza))
    {
        movimientos.push_back({xLeft, yLeft});
    }

    if (esValida(estado, xRight, yRight) &&
        esCasillaOcupada(estado, xRight, yRight) &&
        esCaptura(estado, xRight, yRight, pieza))
    {
        movimientos.push_back({xRight, yRight});
    }

    return movimientos;
}

bool Peon::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

bool Peon::esCasillaOcupada(const Nodo& estado, int x, int y) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getPosicion().x == x && f.getPosicion().y == y)
            return true;
    }
    return false;
}

bool Peon::esCaptura(const Nodo& estado, int x, int y, const Ficha& piezaOrigen) const
{
    for (const Ficha& f : estado.piezas)
    {
        if (f.getPosicion().x == x && f.getPosicion().y == y)
            return f.getColor() != piezaOrigen.getColor();
    }
    return false;
}