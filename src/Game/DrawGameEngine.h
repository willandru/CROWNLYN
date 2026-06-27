#pragma once

#include "Posicion.h"

class Renderer;
class Shader;
class Input;

class TableroBuilder;
class DrawTableroEngine;

class DrawGameEngine
{
public:

    DrawGameEngine();

    void setBuilder(
        TableroBuilder* builder
    );

    void setTableroEngine(
        DrawTableroEngine* engine
    );

    void draw(
        Renderer& renderer,
        Shader& basicShader,
        Shader& textureShader,
        const Input& input
    );

    int seleccionarFicha(
        float mouseX,
        float mouseY,
        Posicion& outPos
    );

private:

    TableroBuilder* m_builder;

    DrawTableroEngine* m_tableroEngine;
};