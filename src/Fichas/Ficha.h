#pragma once

#include <vector>

struct Posicion
{
    int x;
    int y;
};

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
    Ficha(TipoFicha tipo, Color color, Posicion pos);

    TipoFicha getTipo() const;
    Color getColor() const;
    Posicion getPosicion() const;

    void setPosicion(Posicion p);

    // En MODELO B: la lógica NO está en la ficha
    // se calcula externamente (ej: Motor / Sistema de reglas)

private:
    TipoFicha tipo;
    Color color;
    Posicion posicion;
};