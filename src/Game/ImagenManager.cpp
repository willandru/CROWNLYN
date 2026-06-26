#include "ImagenManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

ImagenManager::ImagenManager()
    : m_ruta(""),
      m_textureID(0),
      m_width(0),
      m_height(0),
      m_channels(0),
      m_cargada(false)
{
}

ImagenManager::ImagenManager(const std::string& ruta)
    : m_ruta(""),
      m_textureID(0),
      m_width(0),
      m_height(0),
      m_channels(0),
      m_cargada(false)
{
    cargar(ruta);
}

ImagenManager::~ImagenManager()
{
    liberar();
}

bool ImagenManager::cargar(const std::string& ruta)
{
    liberar();

    m_ruta = ruta;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        ruta.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        0
    );

    if (!data)
    {
        std::cout << "[ImagenManager] No se pudo cargar: "
                  << ruta << std::endl;

        return false;
    }

    GLenum format = GL_RGB;

    if (m_channels == 1)
    {
        format = GL_RED;
    }
    else if (m_channels == 3)
    {
        format = GL_RGB;
    }
    else if (m_channels == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        m_width,
        m_height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    m_cargada = true;

    return true;
}

void ImagenManager::liberar()
{
    if (m_textureID != 0)
    {
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;
    }

    m_width = 0;
    m_height = 0;
    m_channels = 0;

    m_cargada = false;
}

bool ImagenManager::cargada() const
{
    return m_cargada;
}

unsigned int ImagenManager::textureID() const
{
    return m_textureID;
}

int ImagenManager::width() const
{
    return m_width;
}

int ImagenManager::height() const
{
    return m_height;
}

int ImagenManager::channels() const
{
    return m_channels;
}

const std::string& ImagenManager::ruta() const
{
    return m_ruta;
}