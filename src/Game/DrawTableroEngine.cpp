#include "DrawTableroEngine.h"

#include "Tablero.h"

//==================================================
// CANTIDAD DE CASILLAS
//==================================================

int DrawTableroEngine::getCantidadCasillas(
    const Tablero& tablero
) const
{
    return
        tablero.getAncho()
        * tablero.getAlto();
}

//==================================================
// COMANDO DE DIBUJO
//==================================================

DrawRectCommand DrawTableroEngine::getDrawCommand(
    const Tablero& tablero,
    int index
) const
{
    DrawRectCommand cmd;

    const int ancho =
        tablero.getAncho();

    const int columna =
        index % ancho;

    const int fila =
        index / ancho;

    const float cellW =
        tablero.getCellWidth();

    const float cellH =
        tablero.getCellHeight();

    cmd.x =
        tablero.getX()
        + columna * cellW;

    cmd.y =
        tablero.getY()
        + fila * cellH;

    cmd.w = cellW;
    cmd.h = cellH;

    const bool casillaOscura =
        (columna + fila) % 2 == 0;

    if (casillaOscura)
    {
        cmd.r = 0.20f;
        cmd.g = 0.20f;
        cmd.b = 0.20f;
    }
    else
    {
        cmd.r = 0.80f;
        cmd.g = 0.80f;
        cmd.b = 0.80f;
    }

    return cmd;
}