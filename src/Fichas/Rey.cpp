#include "Rey.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Rey::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> movimientos;

    const Posicion o = pieza.getPosicion();

    const Color enemigo =
        (pieza.getColor() == Color::Blanca)
        ? Color::Negra
        : Color::Blanca;

    const int dirs[8][2] =
    {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for (const auto& d : dirs)
    {
        int x = o.x + d[0];
        int y = o.y + d[1];

        if (!esValida(estado, x, y))
            continue;

        // REGLA: no moverse a casillas ocupadas por piezas propias
        const Ficha* f = obtenerFichaEn(estado, x, y);
        if (f && f->getColor() == pieza.getColor())
            continue;

        // IMPORTANTE:
        // el control de jaque NO se calcula aquí
        // lo filtra el DecisionTreeEngine

        movimientos.push_back({x, y});
    }

    return movimientos;
}

// ======================================================
// ATAQUES (CONTROL REAL DE CASILLAS)
// ======================================================

std::vector<Posicion> Rey::getAtaques(
    const Ficha& pieza,
    const Nodo& estado) const
{
    std::vector<Posicion> ataques;

    const Posicion o = pieza.getPosicion();

    const int dirs[8][2] =
    {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for (const auto& d : dirs)
    {
        int x = o.x + d[0];
        int y = o.y + d[1];

        if (esValida(estado, x, y))
            ataques.push_back({x, y});
    }

    return ataques;
}

// ======================================================

bool Rey::esValida(const Nodo& estado, int x, int y) const
{
    return estado.tablero.esValida(x, y);
}

const Ficha* Rey::obtenerFichaEn(const Nodo& estado, int x, int y) const
{
    return estado.obtenerFichaEn(x, y);
}