#pragma once

class Renderer;
class Shader;
class Input;

class Tablero;
class DrawTableroEngine;

class DrawGameEngine
{
public:

    DrawGameEngine();

    void setTablero(const Tablero* tablero);
    void setTableroEngine(DrawTableroEngine* engine);

    void draw(
        Renderer& renderer,
        Shader& shader,
        const Input& input
    );

private:

    const Tablero* m_tablero;
    DrawTableroEngine* m_tableroEngine;
};