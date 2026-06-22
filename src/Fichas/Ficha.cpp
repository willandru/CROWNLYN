#include "Ficha.h"

Ficha::Ficha(TipoFicha tipo, Color color)
{
    this->tipo = tipo;
    this->color = color;
}

Ficha::~Ficha()
{
}

TipoFicha Ficha::getTipo() const
{
    return tipo;
}

Color Ficha::getColor() const
{
    return color;
}