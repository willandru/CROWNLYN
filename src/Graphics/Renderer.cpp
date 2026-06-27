#include "Renderer.h"
#include "Shader.h"
#include "Tablero.h"
#include "ImagenManager.h"

#include <glad/glad.h>

#include <iostream>

Renderer::Renderer()
{
    float vertices[] =
    {
        // Posición      // UV
        0.0f, 0.0f,      0.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 0.0f,
        0.0f, 1.0f,      0.0f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    // Posición
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Coordenadas UV
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer::begin()
{
    glClearColor(
        0.05f,
        0.05f,
        0.05f,
        1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::end()
{
}

void Renderer::drawRect(
    const DrawRectCommand& cmd,
    const Shader& shader
)
{
    shader.use();

    GLint rectLoc = glGetUniformLocation(
        shader.getProgram(),
        "uRect"
    );

    GLint colorLoc = glGetUniformLocation(
        shader.getProgram(),
        "uColor"
    );

    glUniform4f(
        rectLoc,
        cmd.x,
        cmd.y,
        cmd.w,
        cmd.h
    );

    glUniform3f(
        colorLoc,
        cmd.r,
        cmd.g,
        cmd.b
    );

    glBindVertexArray(m_vao);

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        nullptr
    );
}

void Renderer::drawImage(
    const DrawImageCommand& cmd,
    const Shader& shader
)
{
    if (cmd.imagen == nullptr)
    {
        return;
    }

    if (!cmd.imagen->cargada())
    {
        return;
    }

    shader.use();

    GLint rectLoc = glGetUniformLocation(
        shader.getProgram(),
        "uRect"
    );

    glUniform4f(
        rectLoc,
        cmd.x,
        cmd.y,
        cmd.w,
        cmd.h
    );

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(
        GL_TEXTURE_2D,
        cmd.imagen->textureID()
    );

    GLint texLoc = glGetUniformLocation(
        shader.getProgram(),
        "uTexture"
    );

    glUniform1i(
        texLoc,
        0
    );

    glBindVertexArray(m_vao);

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        nullptr
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );
}


void Renderer::drawTablero(
    const DrawTableroCommand& cmd,
    const Shader& shader
)
{
    const Tablero& t = *cmd.tablero;

    int ancho = t.getAncho();
    int alto  = t.getAlto();

    float cellW = t.getCellWidth();
    float cellH = t.getCellHeight();

    float startX = t.getX();
    float startY = t.getY();

    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {
            DrawRectCommand rect;

            rect.x = startX + x * cellW;
            rect.y = startY + y * cellH;
            rect.w = cellW;
            rect.h = cellH;

            // patrón ajedrez
            bool dark = ((x + y) & 1);

            if (dark)
            {
                rect.r = 0.2f;
                rect.g = 0.2f;
                rect.b = 0.2f;
            }
            else
            {
                rect.r = 0.8f;
                rect.g = 0.8f;
                rect.b = 0.8f;
            }

            drawRect(rect, shader);
        }
    }
}

void Renderer::drawFicha(
    const DrawFichaCommand& cmd,
    const Shader& shader
)
{
    std::cout << "drawFicha()" << std::endl;

    if (cmd.textura == nullptr)
    {
        std::cout << "textura nullptr" << std::endl;
        return;
    }

    if (!cmd.textura->cargada())
    {
        std::cout << "textura no cargada" << std::endl;
        return;
    }

    std::cout << "x = " << cmd.x
              << " y = " << cmd.y
              << " w = " << cmd.w
              << " h = " << cmd.h
              << std::endl;

    shader.use();

    GLint rectLoc = glGetUniformLocation(
        shader.getProgram(),
        "uRect"
    );

    GLint texLoc = glGetUniformLocation(
        shader.getProgram(),
        "uTexture"
    );

    std::cout << "uRect = " << rectLoc << std::endl;
    std::cout << "uTexture = " << texLoc << std::endl;
    std::cout << "Texture ID = " << cmd.textura->textureID() << std::endl;

    glUniform4f(
        rectLoc,
        cmd.x,
        cmd.y,
        cmd.w,
        cmd.h
    );

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(
        GL_TEXTURE_2D,
        cmd.textura->textureID()
    );

    glUniform1i(
        texLoc,
        0
    );

    glBindVertexArray(m_vao);

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        nullptr
    );

    GLenum err = glGetError();

    std::cout << "OpenGL Error = " << err << std::endl;

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );
}