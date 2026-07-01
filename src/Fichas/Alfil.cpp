#include "Alfil.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Alfil::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> movimientos;

    const Posicion origen =
        pieza.getPosicion();

    const int direcciones[4][2] =
    {
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 }
    };

    for (const auto& dir : direcciones)
    {
        int x =
            origen.x + dir[0];

        int y =
            origen.y + dir[1];

        while (
            estado.esValida(
                x,
                y
            )
        )
        {
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
            else
            {
                if (
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

                break;
            }

            x += dir[0];
            y += dir[1];
        }
    }

    return movimientos;
}

// ======================================================
// ATAQUES
// ======================================================

std::vector<Posicion> Alfil::getAtaques(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> ataques;

    const Posicion origen =
        pieza.getPosicion();

    const int direcciones[4][2] =
    {
        {  1,  1 },
        {  1, -1 },
        { -1,  1 },
        { -1, -1 }
    };

    for (const auto& dir : direcciones)
    {
        int x =
            origen.x + dir[0];

        int y =
            origen.y + dir[1];

        while (
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

            if (
                estado.obtenerFichaEn(
                    x,
                    y
                )
            )
            {
                break;
            }

            x += dir[0];
            y += dir[1];
        }
    }

    return ataques;
}