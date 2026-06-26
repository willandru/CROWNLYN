#pragma once

#include "Tablero.h"

class Renderer;
class Shader;

class DrawTableroEngine
{
public:

    void draw(
        const Tablero& tablero,
        Renderer& renderer,
        const Shader& shader
    );
};