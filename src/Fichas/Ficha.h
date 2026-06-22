#pragma once

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
    Ficha(TipoFicha tipo, Color color);
    ~Ficha();

    TipoFicha getTipo() const;
    Color getColor() const;

private:
    TipoFicha tipo;
    Color color;
};