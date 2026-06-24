#pragma once

#include <vector>

#include "Nodo.h"
#include "Ficha.h"
#include "StateEvaluator.h"
#include "GameAnalyzer.h"

class DecisionTreeEngine
{
public:
    DecisionTreeEngine();

    void expandirNodo(Nodo* nodo);

    const std::vector<Nodo*>& getNodos() const;

private:
    StateEvaluator evaluator;
    GameAnalyzer analyzer;

    std::vector<Nodo*> nodos;
};