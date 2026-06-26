#pragma once

#include <glad/glad.h>

class Shader;
class Tablero;
class ImagenManager;

// =========================
// COMMANDS
// =========================

struct DrawRectCommand
{
    float x, y, w, h;
    float r, g, b;
};

struct DrawImageCommand
{
    float x, y, w, h;
    const ImagenManager* imagen;
};

struct DrawTableroCommand
{
    const Tablero* tablero;
};

struct DrawFichaCommand
{
    float x, y, w, h;
    const ImagenManager* textura;
};

// =========================
// RENDERER
// =========================

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

    void drawFicha(
        const DrawFichaCommand& cmd,
        const Shader& shader
    );

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};