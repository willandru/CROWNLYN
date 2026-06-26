#pragma once

#include <glad/glad.h>
#include "ImagenManager.h"

class Shader;

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

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};