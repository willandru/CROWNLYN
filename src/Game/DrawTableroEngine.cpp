#include "DrawTableroEngine.h"

#include "Tablero.h"

int DrawTableroEngine::getCantidadCasillas(
    const Tablero& tablero
) const
{
    return
        tablero.getAncho()
        * tablero.getAlto();
}

DrawRectCommand DrawTableroEngine::getDrawCommand(
    const Tablero& tablero,
    int index
) const
{
    DrawRectCommand cmd;

    int ancho = tablero.getAncho();

    int x = index % ancho;
    int y = index / ancho;

    float cellW =
        tablero.getCellWidth();

    float cellH =
        tablero.getCellHeight();

    cmd.x =
        tablero.getX()
        + x * cellW;

    cmd.y =
        tablero.getY()
        + y * cellH;

    cmd.w = cellW;
    cmd.h = cellH;

    bool dark =
        ((x + y) % 2 == 0);

    cmd.r =
        dark ? 0.2f : 0.8f;

    cmd.g =
        dark ? 0.2f : 0.8f;

    cmd.b =
        dark ? 0.2f : 0.8f;

    return cmd;
}