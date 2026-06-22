#pragma once

#include <vector>

class Nodo;

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

struct Posicion
{
    int x;
    int y;
};

class Ficha
{
public:
    Ficha(TipoFicha tipo, Color color, Posicion pos);
    virtual ~Ficha();

    TipoFicha getTipo() const;
    Color getColor() const;
    Posicion getPosicion() const;

    void setPosicion(Posicion p);

    // Contrato polimórfico
    virtual std::vector<Posicion> getMovimientos(const Nodo& estado) const = 0;

protected:
    TipoFicha tipo;
    Color color;
    Posicion posicion;
};