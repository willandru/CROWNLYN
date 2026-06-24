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
    Ficha blanca;
    Ficha negra;

    bool foundB = false;
    bool foundN = false;

    for (const Ficha& f : estado.piezas)
    {
        if (f.getColor() == Color::Blanca)
        {
            if (foundB) return false; // más de 1 pieza blanca
            blanca = f;
            foundB = true;
        }
        else
        {
            if (foundN) return false; // más de 1 pieza negra
            negra = f;
            foundN = true;
        }
    }

    // deben existir exactamente 1 y 1
    if (!foundB || !foundN)
        return false;

    // mismo tipo = tablas en Crownlyn
    return blanca.getTipo() == negra.getTipo();
}

// ======================================================

bool StateEvaluator::estadoTerminal(const Nodo& estado, Color color) const
{
    return esDerrota(estado)
        || esTablas(estado)
        || esMate(estado, color)
        || sinMovimientos(estado, color);
}