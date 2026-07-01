#pragma once

#include <vector>

#include "Ficha.h"
#include "Nodo.h"

class Dama
{
public:
    std::vector<Posicion> getMovimientos(
        const Ficha& pieza,
        const Nodo& estado
    ) const;

    std::vector<Posicion> getAtaques(
        const Ficha& pieza,
        const Nodo& estado
    ) const;
};