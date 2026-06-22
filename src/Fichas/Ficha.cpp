#include "Ficha.h"

Ficha::Ficha()
{
    tipo = TipoFicha::Peon;
    color = Color::Blanca;
    posicion = {0, 0};
}

Ficha::Ficha(TipoFicha tipo, Color color, Posicion pos)
{
    this->tipo = tipo;
    this->color = color;
    this->posicion = pos;
}

TipoFicha Ficha::getTipo() const
{
    return tipo;
}

Color Ficha::getColor() const
{
    return color;
}

Posicion Ficha::getPosicion() const
{
    return posicion;
}

void Ficha::setPosicion(Posicion p)
{
    posicion = p;
}