#include "Tablero.h"

Tablero::Tablero()
{
    this->ancho = 0;
    this->alto = 0;
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

bool Tablero::esValida(int x, int y) const
{
    return x >= 0 && x < ancho && y >= 0 && y < alto;
}