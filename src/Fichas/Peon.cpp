#include "Peon.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Peon::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> movimientos;

    const Posicion origen =
        pieza.getPosicion();

    // Blancas avanzan hacia abajo (+Y)
    // Negras avanzan hacia arriba (-Y)
    const int dir =
        (pieza.getColor() == Color::Blanca)
        ? 1
        : -1;

    //--------------------------------------------------
    // AVANCE SIMPLE
    //--------------------------------------------------

    const int xFront =
        origen.x;

    const int yFront =
        origen.y + dir;

    if (
        estado.esValida(
            xFront,
            yFront
        ) &&
        !estado.obtenerFichaEn(
            xFront,
            yFront
        )
    )
    {
        movimientos.push_back(
            {
                xFront,
                yFront
            }
        );
    }

    //--------------------------------------------------
    // CAPTURAS
    //--------------------------------------------------

    const int dx[2] =
    {
        -1,
         1
    };

    for (int d : dx)
    {
        const int x =
            origen.x + d;

        const int y =
            origen.y + dir;

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

std::vector<Posicion> Peon::getAtaques(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> ataques;

    const Posicion origen =
        pieza.getPosicion();

    const int dir =
        (pieza.getColor() == Color::Blanca)
        ? 1
        : -1;

    const int dx[2] =
    {
        -1,
         1
    };

    for (int d : dx)
    {
        const int x =
            origen.x + d;

        const int y =
            origen.y + dir;

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