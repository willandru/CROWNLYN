#pragma once

#include <vector>
#include "Nodo.h"
#include "Ficha.h"
#include "Torre.h"
#include "Rey.h"
#include "Peon.h"

class DecisionTreeEngine
{
public:
    DecisionTreeEngine();

    void expandirNodo(Nodo* nodo);

    // validación de reglas
    bool esMovimientoLegal(const Nodo& estado, const Ficha& ficha, const Posicion& destino) const;

    bool estaEnJaque(const Nodo& estado, Color color) const;
    bool esMate(const Nodo& estado, Color color) const;
    bool esAhogado(const Nodo& estado, Color color) const;

    bool tieneMovimientosLegales(const Nodo& estado, Color color) const;

private:

    // simulación
    Nodo simularMovimiento(const Nodo& estado, const Ficha& ficha, const Posicion& destino) const;

    // generación de movimientos base
    std::vector<Posicion> obtenerMovimientosFicha(const Ficha& f, const Nodo& estado) const;
    std::vector<Posicion> obtenerAtaquesFicha(const Ficha& f, const Nodo& estado) const;

    // utilidades
    const Ficha* encontrarRey(const Nodo& estado, Color color) const;
    bool casillaOcupadaPorColor(const Nodo& estado, int x, int y, Color color) const;

    bool casillaAtacada(const Nodo& estado, int x, int y, Color atacante) const;
};