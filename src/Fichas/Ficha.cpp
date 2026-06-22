#include "Ficha.h"

// ======================================================
// CONSTRUCTORES
// ======================================================

Ficha::Ficha()
{
    id = -1;
    tipo = TipoFicha::Peon;
    color = Color::Blanca;
    posicion = {0, 0};
}

Ficha::Ficha(int id, TipoFicha tipo, Color color, Posicion pos)
{
    this->id = id;
    this->tipo = tipo;
    this->color = color;
    this->posicion = pos;
}

Ficha::Ficha(int id, TipoFicha tipo, Color color, int x, int y)
{
    this->id = id;
    this->tipo = tipo;
    this->color = color;
    this->posicion = {x, y};
}

// ======================================================
// GETTERS
// ======================================================

int Ficha::getId() const
{
    return id;
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

// ======================================================
// SETTER
// ======================================================

void Ficha::setPosicion(Posicion p)
{
    posicion = p;
}

std::string Ficha::tipoToString() const
{
    switch (tipo)
    {
        case TipoFicha::Peon:    return "Peon";
        case TipoFicha::Torre:   return "Torre";
        case TipoFicha::Caballo: return "Caballo";
        case TipoFicha::Alfil:   return "Alfil";
        case TipoFicha::Dama:    return "Dama";
        case TipoFicha::Rey:     return "Rey";
        default:                 return "Desconocido";
    }
}