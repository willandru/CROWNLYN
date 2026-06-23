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

    bool esMovimientoLegal(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    bool estaEnJaque(
        const Nodo& estado,
        Color color) const;

    bool esMate(
        const Nodo& estado,
        Color color) const;

    bool esDerrota(
        const Nodo& estado) const;

    bool sinMovimientos(
        const Nodo& estado,
        Color color) const;
        
    bool tieneMovimientosFisicos(
    const Nodo& estado,
    Color color) const;

    bool tieneMovimientosLegales(
        const Nodo& estado,
        Color color) const;

private:

    Nodo simularMovimiento(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    std::vector<Posicion> obtenerMovimientosFicha(
        const Ficha& f,
        const Nodo& estado) const;

    std::vector<Posicion> obtenerAtaquesFicha(
        const Ficha& f,
        const Nodo& estado) const;

    const Ficha* encontrarRey(
        const Nodo& estado,
        Color color) const;

    bool casillaOcupadaPorColor(
        const Nodo& estado,
        int x,
        int y,
        Color color) const;

    bool casillaAtacada(
        const Nodo& estado,
        int x,
        int y,
        Color atacante) const;
};