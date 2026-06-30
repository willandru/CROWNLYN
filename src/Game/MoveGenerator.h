#pragma once

#include <vector>
#include "Posicion.h"

class Nodo;
class Ficha;

class MoveGenerator
{
public:
    static std::vector<Posicion> getMovimientos(
        const Ficha& ficha,
        const Nodo& nodo
    );

    static std::vector<Posicion> getAtaques(
        const Ficha& ficha,
        const Nodo& nodo
    );
};