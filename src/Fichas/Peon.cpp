#include "Peon.h"

#include "Tablero.h"
// ======================================================
// MOVIMIENTOS LEGALES (NO INCLUYE CONTROL DE CASILLAS VACÍAS COMO ATAQUE)
// ======================================================

std::vector<Posicion> Peon::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    const Posicion o = pieza.getPosicion();

    const int dir =
        (pieza.getColor() == Color::Blanca) ? -1 : 1;

    // =====================================================
    // AVANCE SIMPLE
    // =====================================================

    int xFront = o.x + dir;
    int yFront = o.y;

    if (esValida(estado, xFront, yFront) &&
        !obtenerFichaEn(estado, xFront, yFront))
    {
        movimientos.push_back({xFront, yFront});
    }

    // =====================================================
    // CAPTURAS DIAGONALES (SOLO SI HAY PIEZA ENEMIGA)
    // =====================================================

    const int dy[2] = {-1, 1};

    for (int d : dy)
    {
        int x = o.x + dir;
        int y = o.y + d;

        if (!esValida(estado, x, y))
            continue;

        const Ficha* f = obtenerFichaEn(estado, x, y);

        if (f && f->getColor() != pieza.getColor())
        {
            movimientos.push_back({x, y});
        }
    }

    return movimientos;
}

// ======================================================
// ATAQUES (CONTROL DE CASILLAS PARA JAQUE)
// ======================================================

std::vector<Posicion> Peon::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    const Posicion o = pieza.getPosicion();

    const int dir =
        (pieza.getColor() == Color::Blanca) ? -1 : 1;

    const int dy[2] = {-1, 1};

    for (int d : dy)
    {
        int x = o.x + dir;
        int y = o.y + d;

        if (esValida(estado, x, y))
        {
            // IMPORTANTE:
            // el peón controla diagonales aunque no haya pieza
            ataques.push_back({x, y});
        }
    }

    return ataques;
}

// ======================================================
// UTILIDADES
// ======================================================

bool Peon::esValida(const Nodo& estado, int x, int y) const
{
    if (!estado.tablero)
        return false;

    return estado.tablero->esValida(x, y);
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