#pragma once

class Renderer;
class Shader;
class Input;

class Tablero;
class DrawTableroEngine;
class DrawFichaEngine;

class DrawGameEngine
{
public:

    DrawGameEngine();

    void setTablero(
        const Tablero* tablero
    );

    void setTableroEngine(
        DrawTableroEngine* engine
    );

    void setFichaEngine(
        DrawFichaEngine* engine
    );

    void draw(
        Renderer& renderer,
        Shader& basicShader,
        Shader& textureShader,
        const Input& input
    );

private:

    const Tablero* m_tablero;

    DrawTableroEngine* m_tableroEngine;
    DrawFichaEngine* m_fichaEngine;
};