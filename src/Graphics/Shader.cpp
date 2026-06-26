#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>

#include <filesystem>


Shader::Shader(
    const char* vertexPath,
    const char* fragmentPath
)
    : m_program(0)
{
    int vertexSize = 0;
    int fragmentSize = 0;

    char* vertexSource =
        loadFile(
            vertexPath,
            vertexSize
        );

    char* fragmentSource =
        loadFile(
            fragmentPath,
            fragmentSize
        );

    if (!vertexSource || !fragmentSource)
    {
        delete[] vertexSource;
        delete[] fragmentSource;
        return;
    }

    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        const_cast<const char**>(&vertexSource),
        &vertexSize
    );

    glCompileShader(vertexShader);

    GLint success = 0;

    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            vertexShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Vertex shader error:\n"
            << infoLog
            << '\n';
    }

    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        const_cast<const char**>(&fragmentSource),
        &fragmentSize
    );

    glCompileShader(fragmentShader);

    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            fragmentShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Fragment shader error:\n"
            << infoLog
            << '\n';
    }

    m_program = glCreateProgram();

    glAttachShader(
        m_program,
        vertexShader
    );

    glAttachShader(
        m_program,
        fragmentShader
    );

    glLinkProgram(m_program);

    glGetProgramiv(
        m_program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            m_program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Program link error:\n"
            << infoLog
            << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    delete[] vertexSource;
    delete[] fragmentSource;
}

Shader::~Shader()
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
    }
}

void Shader::use() const
{
    glUseProgram(m_program);
}

unsigned int Shader::getProgram() const
{
    return m_program;
}

char* Shader::loadFile(
    const char* path,
    int& size
)
{
    namespace fs = std::filesystem;

    std::cout << "Working directory: "
              << fs::current_path() << '\n';

    std::cout << "Trying: "
              << fs::absolute(path) << '\n';

    std::filesystem::path p(path);

   

    std::ifstream file(
        path,
        std::ios::binary
    );

    std::cout << "is_open(): "
              << file.is_open()
              << '\n';

    if (!file.is_open())
    {
        std::cerr
            << "Cannot open shader: "
            << path
            << '\n';

        size = 0;
        return nullptr;
    }

    file.seekg(0, std::ios::end);

    size = static_cast<int>(
        file.tellg()
    );

    file.seekg(0, std::ios::beg);

    char* buffer =
        new char[size];

    file.read(
        buffer,
        size
    );

    return buffer;
}