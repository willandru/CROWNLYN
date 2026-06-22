#include "Tablero.h"

Tablero::Tablero()
{
    ancho = 3;
    alto = 3;
}

Tablero::Tablero(int ancho, int alto)
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

void Tablero::setDimensiones(int ancho, int alto)
{
    this->ancho = ancho;
    this->alto = alto;
}

bool Tablero::esValida(int x, int y) const
{
    return x >= 0 && x < ancho && y >= 0 && y < alto;
}