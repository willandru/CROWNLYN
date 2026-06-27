#pragma once

#include <string>
#include <glad/glad.h>

class ImagenManager
{
public:

    ImagenManager();

    explicit ImagenManager(
        const std::string& ruta
    );

    ~ImagenManager();

    bool cargar(
        const std::string& ruta
    );

    void liberar();

    bool cargada() const;

    unsigned int textureID() const;

    int width() const;

    int height() const;

    int channels() const;

    const std::string& ruta() const;

private:

    std::string m_ruta;

    unsigned int m_textureID;

    int m_width;

    int m_height;

    int m_channels;

    bool m_cargada;
};