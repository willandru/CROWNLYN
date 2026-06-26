#include "Tablero.h"

Tablero::Tablero()
{
    ancho = 0;
    alto = 0;
}

Tablero::Tablero(
    int ancho,
    int alto
)
{
    this->ancho = ancho;
    this->alto = alto;
}

int Tablero::getAncho() const
{
    return ancho;
}

int Tablero::getAlto() const
{
    return alto;
}

bool Tablero::esValida(
    int x,
    int y
) const
{
    return x >= 0 &&
           x < ancho &&
           y >= 0 &&
           y < alto;
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