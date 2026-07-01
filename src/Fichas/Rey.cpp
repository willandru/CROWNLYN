#include "Rey.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Rey::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> movimientos;

    const Posicion origen =
        pieza.getPosicion();

    const int direcciones[8][2] =
    {
        {  1,  0 },
        { -1,  0 },
        {  0,  1 },
        {  0, -1 },
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 }
    };

    for (const auto& dir : direcciones)
    {
        const int x =
            origen.x + dir[0];

        const int y =
            origen.y + dir[1];

        if (
            !estado.esValida(
                x,
                y
            )
        )
        {
            continue;
        }

        const Ficha* ficha =
            estado.obtenerFichaEn(
                x,
                y
            );

        if (
            ficha &&
            ficha->getColor() == pieza.getColor()
        )
        {
            continue;
        }

        // El filtrado de jaque se realiza
        // posteriormente por el motor de decisión.

        movimientos.push_back(
            {
                x,
                y
            }
        );
    }

    return movimientos;
}

// ======================================================
// ATAQUES
// ======================================================

std::vector<Posicion> Rey::getAtaques(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> ataques;

    const Posicion origen =
        pieza.getPosicion();

    const int direcciones[8][2] =
    {
        {  1,  0 },
        { -1,  0 },
        {  0,  1 },
        {  0, -1 },
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 }
    };

    for (const auto& dir : direcciones)
    {
        const int x =
            origen.x + dir[0];

        const int y =
            origen.y + dir[1];

        if (
            estado.esValida(
                x,
                y
            )
        )
        {
            ataques.push_back(
                {
                    x,
                    y
                }
            );
        }
    }

    return ataques;
}