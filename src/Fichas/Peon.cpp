#include "Peon.h"

#include "Tablero.h"

// ======================================================
// MOVIMIENTOS LEGALES
// ======================================================

std::vector<Posicion> Peon::getMovimientos(
    const Ficha& pieza,
    const Nodo& estado
) const
{
    std::vector<Posicion> movimientos;

    const Posicion o =
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

    int xFront =
        o.x;

    int yFront =
        o.y + dir;

    if (
        esValida(
            estado,
            xFront,
            yFront
        ) &&
        !obtenerFichaEn(
            estado,
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
        int x =
            o.x + d;

        int y =
            o.y + dir;

        if (!esValida(
                estado,
                x,
                y))
        {
            continue;
        }

        const Ficha* ficha =
            obtenerFichaEn(
                estado,
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

    const Posicion o =
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
        int x =
            o.x + d;

        int y =
            o.y + dir;

        if (
            esValida(
                estado,
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

// ======================================================
// UTILIDADES
// ======================================================

bool Peon::esValida(
    const Nodo& estado,
    int x,
    int y
) const
{
    if (!estado.tablero)
        return false;

    return estado.tablero->esValida(
        x,
        y
    );
}

const Ficha* Peon::obtenerFichaEn(
    const Nodo& estado,
    int x,
    int y
) const
{
    for (const Ficha& ficha : estado.piezas)
    {
        if (
            ficha.getPosicion().x == x &&
            ficha.getPosicion().y == y
        )
        {
            return &ficha;
        }
    }

    return nullptr;
}