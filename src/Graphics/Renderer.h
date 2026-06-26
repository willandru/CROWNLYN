#pragma once

#include <glad/glad.h>

class Shader;
class Tablero;
class ImagenManager;

struct DrawRectCommand
{
    float x, y, w, h;
    float r, g, b;
};

struct DrawImageCommand
{
    float x;
    float y;
    float w;
    float h;

    const ImagenManager* imagen;
};

struct DrawTableroCommand
{
    const Tablero* tablero;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void begin();
    void end();

    void drawRect(const DrawRectCommand& cmd, const Shader& shader);

    void drawImage(
        const DrawImageCommand& cmd,
        const Shader& shader
    );

    void drawTablero(
        const DrawTableroCommand& cmd,
        const Shader& shader
    );

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};