#pragma once

#include "Posicion.h"

class Renderer;
class Shader;
class Input;

class Tablero;
class DrawTableroEngine;
class DrawFichaEngine;
class TextureFichasLoader;

class DrawGameEngine
{
public:

    DrawGameEngine();

    void setTablero(const Tablero* tablero);
    void setTableroEngine(DrawTableroEngine* engine);
    void setFichaEngine(DrawFichaEngine* engine);
    void setTextureLoader(TextureFichasLoader* loader);

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

    const Tablero* m_tablero;
    DrawTableroEngine* m_tableroEngine;
    DrawFichaEngine* m_fichaEngine;
    TextureFichasLoader* m_loader;
};