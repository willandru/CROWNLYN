#pragma once

#include "Renderer.h"

class Tablero;

class DrawTableroEngine
{
public:

    int getCantidadCasillas(
        const Tablero& tablero
    ) const;

    DrawRectCommand getDrawCommand(
        const Tablero& tablero,
        int index
    ) const;
};