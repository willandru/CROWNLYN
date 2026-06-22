#pragma once

#include <vector>

#include "Nodo.h"
#include "Ficha.h"

class DecisionTreeEngine
{
public:
    DecisionTreeEngine();

    void expandirNodo(Nodo* nodo);

    std::vector<Posicion> obtenerMovimientosFicha(
        const Ficha& f,
        const Nodo& estado) const;

    bool esMovimientoLegal(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    bool estaEnJaque(
        const Nodo& estado,
        Color color) const;

    bool casillaAtacada(
        const Nodo& estado,
        int x,
        int y,
        Color porQuien) const;

private:
    Nodo simularMovimiento(
        const Nodo& estado,
        const Ficha& ficha,
        const Posicion& destino) const;

    const Ficha* encontrarRey(
        const Nodo& estado,
        Color color) const;
};