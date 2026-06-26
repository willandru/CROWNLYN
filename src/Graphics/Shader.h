#pragma once

class Shader
{
public:
    Shader(
        const char* vertexPath,
        const char* fragmentPath
    );

    ~Shader();

    void use() const;

    unsigned int getProgram() const;

private:
    unsigned int m_program;

    char* loadFile(
        const char* path,
        int& size
    );
};