#include "Peon.h"

std::vector<Posicion> Peon::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    Posicion origen = pieza.getPosicion();

    int dir =
        (pieza.getColor() == Color::Blanca)
        ? -1
        : 1;

    // =====================================================
    // MOVIMIENTO FRONTAL
    // =====================================================

    int xFront = origen.x + dir;
    int yFront = origen.y;

    if (esValida(estado, xFront, yFront) &&
        !obtenerFichaEn(estado, xFront, yFront))
    {
        movimientos.push_back({ xFront, yFront });
    }

    // =====================================================
    // CAPTURAS DIAGONALES
    // =====================================================

    const int diagonales[2] = { -1, 1 };

    for (int dy : diagonales)
    {
        int x = origen.x + dir;
        int y = origen.y + dy;

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        if (f && f->getColor() != pieza.getColor())
        {
            movimientos.push_back({ x, y });
        }
    }

    return movimientos;
}

std::vector<Posicion> Peon::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    Posicion origen = pieza.getPosicion();

    int dir =
        (pieza.getColor() == Color::Blanca)
        ? -1
        : 1;

    const int diagonales[2] = { -1, 1 };

    for (int dy : diagonales)
    {
        int x = origen.x + dir;
        int y = origen.y + dy;

        if (esValida(estado, x, y))
        {
            ataques.push_back({ x, y });
        }
    }

    return ataques;
}

bool Peon::esValida(
    const Nodo& estado,
    int x,
    int y) const
{
    return estado.tablero.esValida(x, y);
}

const Ficha* Peon::obtenerFichaEn(
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