#include "Caballo.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Caballo::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> movimientos;

    const Posicion origen =
        pieza.getPosicion();

    const int saltos[8][2] =
    {
        {  2,  1 },
        {  2, -1 },
        { -2,  1 },
        { -2, -1 },
        {  1,  2 },
        {  1, -2 },
        { -1,  2 },
        { -1, -2 }
    };

    for (const auto& salto : saltos)
    {
        const int x =
            origen.x + salto[0];

        const int y =
            origen.y + salto[1];

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

        if (!ficha)
        {
            movimientos.push_back(
                {
                    x,
                    y
                }
            );
        }
        else if (
            ficha->getColor() != pieza.getColor()
        )
        {
            movimientos.push_back(
                {
                    x,
                    y
                }
            );
        }
    }

    return movimientos;
}

// ======================================================
// ATAQUES
// ======================================================

std::vector<Posicion> Caballo::getAtaques(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> ataques;

    const Posicion origen =
        pieza.getPosicion();

    const int saltos[8][2] =
    {
        {  2,  1 },
        {  2, -1 },
        { -2,  1 },
        { -2, -1 },
        {  1,  2 },
        {  1, -2 },
        { -1,  2 },
        { -1, -2 }
    };

    for (const auto& salto : saltos)
    {
        const int x =
            origen.x + salto[0];

        const int y =
            origen.y + salto[1];

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