#include "StateEvaluator.h"

// ======================================================

StateEvaluator::StateEvaluator() {}

// ======================================================

bool StateEvaluator::esJaque(const Nodo& estado, Color color) const
{
    return analyzer.estaEnJaque(estado, color);
}

// ======================================================

bool StateEvaluator::esMate(const Nodo& estado, Color color) const
{
    return analyzer.estaEnJaque(estado, color)
        && !analyzer.tieneMovimientosLegales(estado, color);
}

// ======================================================

bool StateEvaluator::sinMovimientos(const Nodo& estado, Color color) const
{
    return !analyzer.tieneMovimientosLegales(estado, color);
}

// ======================================================

bool StateEvaluator::esDerrota(const Nodo& estado) const
{
    int b = 0, n = 0;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() == Color::Blanca) b++;
        else n++;
    }

    return (b == 0 && n > 0);
}

// ======================================================

bool StateEvaluator::esTablas(const Nodo& estado) const
{
    int b = 0, n = 0;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() == Color::Blanca) b++;
        else n++;
    }

    return (b == 1 && n == 1);
}

// ======================================================

bool StateEvaluator::estadoTerminal(const Nodo& estado, Color color) const
{
    return esDerrota(estado)
        || esTablas(estado)
        || esMate(estado, color)
        || sinMovimientos(estado, color);
}