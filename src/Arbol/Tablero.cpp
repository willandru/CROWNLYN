#include "Tablero.h"

Tablero::Tablero()
{
    m_ancho = 0;
    m_alto = 0;

    m_x = 0.0f;
    m_y = 0.0f;

    m_width = 1.0f;
    m_height = 1.0f;
}

Tablero::Tablero(
    int ancho,
    int alto
)
{
    m_ancho = ancho;
    m_alto = alto;

    m_x = 0.0f;
    m_y = 0.0f;

    m_width = 1.0f;
    m_height = 1.0f;
}

int Tablero::getAncho() const
{
    return m_ancho;
}

int Tablero::getAlto() const
{
    return m_alto;
}

bool Tablero::esValida(
    int x,
    int y
) const
{
    return
        x >= 0 &&
        x < m_ancho &&
        y >= 0 &&
        y < m_alto;
}

void Tablero::setRutaImagen(
    const std::string& ruta
)
{
    m_rutaImagen = ruta;
}

const std::string& Tablero::getRutaImagen() const
{
    return m_rutaImagen;
}

void Tablero::setArea(
    float x,
    float y,
    float width,
    float height
)
{
    m_x = x;
    m_y = y;

    m_width = width;
    m_height = height;
}

float Tablero::getX() const
{
    return m_x;
}

float Tablero::getY() const
{
    return m_y;
}

float Tablero::getWidth() const
{
    return m_width;
}

float Tablero::getHeight() const
{
    return m_height;
}

float Tablero::getCellWidth() const
{
    if (m_ancho == 0)
    {
        return 0.0f;
    }

    return m_width / static_cast<float>(m_ancho);
}

float Tablero::getCellHeight() const
{
    if (m_alto == 0)
    {
        return 0.0f;
    }

    return m_height / static_cast<float>(m_alto);
}


int Tablero::getCasillaEn(
    float x,
    float y
) const
{
    if (x < m_x)
    {
        return -1;
    }

    if (x >= m_x + m_width)
    {
        return -1;
    }

    if (y < m_y)
    {
        return -1;
    }

    if (y >= m_y + m_height)
    {
        return -1;
    }

    int columna = static_cast<int>(
        (x - m_x) / getCellWidth()
    );

    int fila = static_cast<int>(
        (y - m_y) / getCellHeight()
    );

    if (!esValida(columna, fila))
    {
        return -1;
    }

    return fila * m_ancho + columna;
}