#include "Peon.h"

std::vector<Posicion> Peon::getMovimientos(const Ficha& pieza, const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = pieza.getPosicion();

    int direccion = (pieza.getColor() == Color::Blanca) ? -1 : 1;

    // Movimiento hacia adelante
    int xFront = origen.x + direccion;
    int yFront = origen.y;

    if (esValida(estado, xFront, yFront) &&
        !esCasillaOcupada(estado, xFront, yFront))
    {
        movimientos.push_back({ xFront, yFront });
    }

    // Captura diagonal izquierda
    int xLeft = origen.x + direccion;
    int yLeft = origen.y - 1;

    if (esValida(estado, xLeft, yLeft) &&
        esCasillaOcupada(estado, xLeft, yLeft) &&
        esCaptura(estado, xLeft, yLeft, pieza))
    {
        movimientos.push_back({ xLeft, yLeft });
    }

    // Captura diagonal derecha
    int xRight = origen.x + direccion;
    int yRight = origen.y + 1;

    if (esValida(estado, xRight, yRight) &&
        esCasillaOcupada(estado, xRight, yRight) &&
        esCaptura(estado, xRight, yRight, pieza))
    {
        movimientos.push_back({ xRight, yRight });
    }

    return movimientos;
}

std::vector<Posicion> Peon::getAtaques(const Ficha& pieza, const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    Posicion origen = pieza.getPosicion();

    int direccion = (pieza.getColor() == Color::Blanca) ? -1 : 1;

    int xLeft = origen.x + direccion;
    int yLeft = origen.y - 1;

    if (esValida(estado, xLeft, yLeft) &&
        esCasillaOcupada(estado, xLeft, yLeft) &&
        esCaptura(estado, xLeft, yLeft, pieza))
    {
        ataques.push_back({ xLeft, yLeft });
    }

    int xRight = origen.x + direccion;
    int yRight = origen.y + 1;

    if (esValida(estado, xRight, yRight) &&
        esCasillaOcupada(estado, xRight, yRight) &&
        esCaptura(estado, xRight, yRight, pieza))
    {
        ataques.push_back({ xRight, yRight });
    }

    return ataques;
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