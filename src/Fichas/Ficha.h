#pragma once

#include <string>
#include "Posicion.h"

enum class Color
{
    Blanca,
    Negra
};

enum class TipoFicha
{
    Peon,
    Torre,
    Caballo,
    Alfil,
    Dama,
    Rey
};

class Ficha
{
public:
    Ficha();
    Ficha(int id, TipoFicha tipo, Color color, Posicion pos);
    Ficha(int id, TipoFicha tipo, Color color, int x, int y);

    int getId() const;

    TipoFicha getTipo() const;
    Color getColor() const;
    Posicion getPosicion() const;

    void setPosicion(Posicion p);
    std::string tipoToString() const;

private:
    int id;              
    TipoFicha tipo;
    Color color;
    Posicion posicion;
};