#pragma once

#include "Ficha.h"
#include <vector>

class Nodo;

class Torre
{
public:
    Torre();
    ~Torre();

    std::vector<Posicion> getMovimientos(const Nodo& estado, Posicion origen) const;

private:
    bool esValida(const Nodo& estado, int x, int y) const;
};