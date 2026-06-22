#pragma once

#include <vector>

#include "Ficha.h"
#include "Nodo.h"

class Torre
{
public:
    std::vector<Posicion> getMovimientos(const Ficha& pieza, const Nodo& estado) const;

private:
    bool esValida(const Nodo& estado, int x, int y) const;
    const Ficha* obtenerFichaEn(const Nodo& estado, int x, int y) const;
};