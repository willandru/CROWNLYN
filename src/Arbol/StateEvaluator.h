#pragma once

#include "Nodo.h"
#include "GameAnalyzer.h"

class StateEvaluator
{
public:
    StateEvaluator();

    bool esJaque(const Nodo& estado, Color color) const;
    bool esMate(const Nodo& estado, Color color) const;
    bool esTablas(const Nodo& estado) const;
    bool esDerrota(const Nodo& estado) const;
    bool sinMovimientos(const Nodo& estado, Color color) const;
    bool estadoTerminal(const Nodo& estado, Color color) const;

private:
    GameAnalyzer analyzer;
};