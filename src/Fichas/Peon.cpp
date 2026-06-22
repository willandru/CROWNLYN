#include "Peon.h"
#include "Nodo.h"

Peon::Peon(Color color, Posicion pos)
    : Ficha(TipoFicha::Peon, color, pos)
{
}

Peon::~Peon()
{
}

bool Peon::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

bool Peon::esCasillaOcupada(const Nodo& estado, int x, int y) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return true;
    }
    return false;
}

bool Peon::esCaptura(const Nodo& estado, int x, int y, const Ficha* piezaOrigen) const
{
    for (const Ficha* f : estado.piezas)
    {
        if (f->getPosicion().x == x && f->getPosicion().y == y)
            return f->getColor() != piezaOrigen->getColor();
    }
    return false;
}

std::vector<Posicion> Peon::getMovimientos(const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = this->getPosicion();
    const Ficha* piezaOrigen = this;

    int dir = (this->getColor() == Color::Blanca) ? -1 : 1;

    // Movimiento hacia adelante
    int xFwd = origen.x;
    int yFwd = origen.y + dir;

    if (esValida(estado, xFwd, yFwd) && !esCasillaOcupada(estado, xFwd, yFwd))
    {
        movimientos.push_back({xFwd, yFwd});
    }

    // Capturas diagonales
    int xLeft = origen.x - 1;
    int xRight = origen.x + 1;
    int yDiag = origen.y + dir;

    if (esValida(estado, xLeft, yDiag) &&
        esCaptura(estado, xLeft, yDiag, piezaOrigen))
    {
        movimientos.push_back({xLeft, yDiag});
    }

    if (esValida(estado, xRight, yDiag) &&
        esCaptura(estado, xRight, yDiag, piezaOrigen))
    {
        movimientos.push_back({xRight, yDiag});
    }

    return movimientos;
}