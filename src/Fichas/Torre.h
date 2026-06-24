#pragma once

#include <vector>
#include "Nodo.h"
#include "Ficha.h"

class Torre
{
public:
    std::vector<Posicion> getMovimientos(
        const Ficha& pieza,
        const Nodo& estado) const;

    std::vector<Posicion> getAtaques(
        const Ficha& pieza,
        const Nodo& estado) const;

private:
    bool esValida(const Nodo& estado, int x, int y) const;

    const Ficha* obtenerFichaEn(
        const Nodo& estado,
        int x,
        int y) const;
};